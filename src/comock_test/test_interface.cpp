#include <comock/comock.h>
#include <doctest/doctest.h>

namespace {

class Interface {
 public:
  virtual ~Interface() = default;

  virtual void voidArgTest() = 0;
  virtual void oneArgTest(int a) = 0;
  virtual void twoArgTest(int a, std::string b) = 0;

  virtual int returnTest() = 0;

  virtual void overrideTest(int a) = 0;
  virtual void overrideTest(std::string b) = 0;

  virtual void constTest() = 0;
  virtual void constTest() const = 0;
};

// clang-format off
COMOCK_DEFINE_BEGIN(Mock, Interface)
  COMOCK_METHOD( voidArgTest  , void ,                    ,        (override) )
  COMOCK_METHOD( oneArgTest   , void , (int)              ,        (override) )
  COMOCK_METHOD( twoArgTest   , void , (int)(std::string) ,        (override) )
  COMOCK_METHOD( returnTest   , int  ,                    ,        (override) )
  COMOCK_METHOD( overrideTest , void , (int)              ,        (override) )
  COMOCK_METHOD( overrideTest , void , (std::string)      ,        (override) )
  COMOCK_METHOD( constTest    , void ,                    ,        (override) )
  COMOCK_METHOD( constTest    , void ,                    , (const)(override) )
COMOCK_DEFINE_END
// clang-format on

class CallTracker {
 public:
  ~CallTracker() { REQUIRE(called_); }

  void called() { called_ = true; }

 private:
  bool called_ = false;
};

struct Fixture {
  comock::Repo repo = {};
  std::unique_ptr<Mock> mock = repo.create<Mock>();

  Fixture() {
    repo.setUnexpectedCallHandler([](std::optional<std::string> const&) {
      REQUIRE_MESSAGE(false, "Unexpected call");
    });
    repo.setMissingCallHandler(
        [](std::string const&) { REQUIRE_MESSAGE(false, "Missing call"); });
  }

  void allowUnexpectedCalls() {
    repo.setUnexpectedCallHandler([](std::optional<std::string> const&) {});
  }
};

}  // namespace

TEST_CASE_FIXTURE(Fixture, "Unexpected call") {
  auto call_tracker = CallTracker{};
  repo.setUnexpectedCallHandler([&call_tracker](auto const& expected_call) {
    call_tracker.called();
    REQUIRE(!expected_call);
  });
  mock->voidArgTest();
}

TEST_CASE("Missing call") {
  auto call_tracker = CallTracker{};

  {
    auto repo = comock::Repo{};
    repo.setMissingCallHandler(
        [&call_tracker](std::string const& missing_call) {
          call_tracker.called();
          REQUIRE(missing_call == "missing call");
        });

    auto const mock = repo.create<Mock>();
    repo.expectCall("missing call", *mock, &Interface::voidArgTest, []() {});
  }
}

TEST_CASE_FIXTURE(Fixture, "Default call") {
  allowUnexpectedCalls();
  REQUIRE_NOTHROW(mock->voidArgTest());
  REQUIRE(mock->returnTest() == int());
}

TEST_CASE_FIXTURE(Fixture, "On call") {
  SUBCASE("Just on call") {
    repo.onCall(*mock, &Interface::returnTest, []() { return 123; });
    REQUIRE(mock->returnTest() == 123);
  }

  SUBCASE("With expected call") {
    repo.expectCall("returnTest", *mock, &Interface::returnTest,
                    []() { return 123; });
    repo.onCall(*mock, &Interface::returnTest, []() { return 321; });
    REQUIRE(mock->returnTest() == 123);
    REQUIRE(mock->returnTest() == 321);
  }
}

TEST_CASE_FIXTURE(Fixture, "Expected call") {
  SUBCASE("No arguments") {
    auto call_tracker = CallTracker{};
    repo.expectCall("void voidArgTest()", *mock, &Interface::voidArgTest,
                    [&call_tracker]() { call_tracker.called(); });
    mock->voidArgTest();
  }

  SUBCASE("One argument") {
    auto call_tracker = CallTracker{};
    repo.expectCall("void oneArgTest(int)", *mock, &Interface::oneArgTest,
                    [&call_tracker](int const a) {
                      REQUIRE(a == 123);
                      call_tracker.called();
                    });
    mock->oneArgTest(123);
  }

  SUBCASE("Two arguments") {
    auto call_tracker = CallTracker{};
    repo.expectCall("void twoArgTest(int, std::string)", *mock,
                    &Interface::twoArgTest,
                    [&call_tracker](int const a, std::string const b) {
                      REQUIRE(a == 123);
                      REQUIRE(b == "test");
                      call_tracker.called();
                    });
    mock->twoArgTest(123, "test");
  }

  SUBCASE("Return") {
    auto call_tracker = CallTracker{};
    repo.expectCall("int returnTest()", *mock, &Interface::returnTest,
                    [&call_tracker]() {
                      call_tracker.called();
                      return 123;
                    });
    REQUIRE(mock->returnTest() == 123);
  }

  SUBCASE("Override int") {
    auto call_tracker = CallTracker{};
    repo.expectCall(
        "void overrideTest(int)", *mock,
        static_cast<void (Interface::*)(int)>(&Interface::overrideTest),
        [&call_tracker](int const a) {
          REQUIRE(a == 123);
          call_tracker.called();
        });
    mock->overrideTest(123);
  }

  SUBCASE("Override string") {
    auto call_tracker = CallTracker{};
    repo.expectCall(
        "void overrideTest(std::string)", *mock,
        static_cast<void (Interface::*)(std::string)>(&Interface::overrideTest),
        [&call_tracker](std::string const a) {
          REQUIRE(a == "test");
          call_tracker.called();
        });
    mock->overrideTest("test");
  }

  SUBCASE("Non-const") {
    auto call_tracker = CallTracker{};
    repo.expectCall("void constTest()", *mock,
                    static_cast<void (Interface::*)()>(&Interface::constTest),
                    [&call_tracker]() { call_tracker.called(); });
    mock->constTest();
  }

  SUBCASE("Const") {
    auto call_tracker = CallTracker{};
    repo.expectCall(
        "void constTest() const", *mock,
        static_cast<void (Interface::*)() const>(&Interface::constTest),
        [&call_tracker]() { call_tracker.called(); });
    static_cast<Mock const*>(mock.get())->constTest();
  }
}

TEST_CASE_FIXTURE(Fixture, "Expectations order") {
  SUBCASE("Correct order") {
    repo.expectCall("call 1", *mock, &Interface::voidArgTest, []() {});
    repo.expectCall("call 2", *mock, &Interface::oneArgTest, [](int) {});

    mock->voidArgTest();
    mock->oneArgTest(123);
  }

  SUBCASE("Incorrect order") {
    repo.expectCall("call 1", *mock, &Interface::voidArgTest, []() {});
    repo.expectCall("call 2", *mock, &Interface::oneArgTest, [](int) {});

    auto call_1_tracker = CallTracker{};
    repo.setUnexpectedCallHandler(
        [&call_1_tracker](std::optional<std::string> const& expected_call) {
          call_1_tracker.called();
          REQUIRE(expected_call == "call 1");
        });
    mock->oneArgTest(1);

    auto call_2_tracker = CallTracker{};
    repo.setUnexpectedCallHandler(
        [&call_2_tracker](std::optional<std::string> const& expected_call) {
          call_2_tracker.called();
          REQUIRE(expected_call == "call 2");
        });
    mock->voidArgTest();
  }
}

#include <comock/comock.h>
#include <doctest/doctest.h>

namespace {

class Class {
 public:
  Class(int const a, int const b) : a_{a}, b_{b} {}

  virtual void incrementA() { ++a_; }

  virtual void incrementB() { ++b_; }

  virtual void incrementBoth() {
    incrementA();
    incrementB();
  }

  int getA() const { return a_; }
  int getB() const { return b_; }

 private:
  int a_ = 0;
  int b_ = 0;
};

// clang-format off
COMOCK_DEFINE_BEGIN(Mock, Class)
  COMOCK_METHOD( incrementA    , void , , (override) )
  COMOCK_METHOD( incrementB    , void , , (override) )
  COMOCK_METHOD( incrementBoth , void , , (override) )
COMOCK_DEFINE_END
// clang-format on

struct Fixture {
  comock::Repo repo = {};
  std::unique_ptr<Mock> mock = repo.create<Mock>(1, 10);

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

TEST_CASE_FIXTURE(Fixture, "Call base class") {
  allowUnexpectedCalls();

  REQUIRE(mock->getA() == 1);
  mock->incrementA();
  REQUIRE(mock->getA() == 2);
}

TEST_CASE_FIXTURE(Fixture, "Call base class from callback") {
  repo.expectCall("incrementA", *mock, &Class::incrementA, [this]() {
    mock->Class::incrementA();
    mock->Class::incrementA();
  });

  REQUIRE(mock->getA() == 1);
  mock->incrementA();
  REQUIRE(mock->getA() == 3);
}

TEST_CASE_FIXTURE(Fixture, "Pause expectations") {
  repo.expectCall("incrementBoth", *mock, &Class::incrementBoth, [this]() {
    repo.pauseExpectations();
    mock->Class::incrementBoth();
    repo.resumeExpectations();
  });

  mock->incrementBoth();
}

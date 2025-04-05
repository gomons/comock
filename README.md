# comock - **C**++ **O**bject **MOCK** library

Header only library for mocking C++ classes and interfaces. It is designed to be
simple and easy to use, while providing powerful features for mocking and
testing.

| Branch | Status |
|--------|--------|
|Main    | [![comock](https://github.com/gomons/comock/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/gomons/comock/actions/workflows/cmake-multi-platform.yml)|

## Thread Safety

This library is **not thread-safe**.

- `Repo` and created mocks are intended to be used from a single thread.
- Concurrent calls to mocks from multiple threads may cause race conditions or
  unexpected behavior.

## Requirements

- C++17 or later
- [boost.preprocessor](https://github.com/boostorg/preprocessor)

## Test requirements

- [CMake](https://cmake.org/download/) 3.10 or later
- [doctest](https://github.com/doctest/doctest)

## Simple example

```cpp
#include <comock/comock.h>
#include <iostream>

class Interface {
 public:
  virtual ~Interface() = default;

  virtual int foo(int a, std::string b) = 0;
};

COMOCK_DEFINE_BEGIN(Mock, Interface)
// COMOCK_METHOD(method-name, return type, argument types, specifiers)
   COMOCK_METHOD(foo, int, (int)(std::string), (override))
COMOCK_DEFINE_END

int main() {
  auto repo = comock::Repo{};
  auto const mock = repo.create<Mock>();

  repo.expectCall("foo", *mock, &Interface::foo, [](int a, std::string b) {
    std::cout << "foo called with " << a << " and " << b << "\n";
    return 0;
  });

  return mock->foo(42, "test");
}
```

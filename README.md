[![comock](https://github.com/gomons/comock/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/gomons/comock/actions/workflows/cmake-multi-platform.yml)

# comock - **C**++ **O**bject **MOCK** library

A lightweight, header-only library for mocking (mocks) and spying (spies) on
virtual methods in C++ classes and interfaces. Its main focus is simplicity.

Documentation: [https://gomons.github.io/comock](https://gomons.github.io/comock)

## Features

- Header-only and minimalistic (but depends on [boost.preprocessor](https://github.com/boostorg/preprocessor))
- Mock and spy on C++ virtual methods
- Easy call sequence verification

## Requirements

- C++17 or later (C++11 support can be easily added by using [boost](https://www.boost.org/))
- [boost.preprocessor](https://github.com/boostorg/preprocessor)

### Test requirements

- [CMake](https://cmake.org/download/) 3.10 or later
- [doctest](https://github.com/doctest/doctest)

## Thread Safety

**comock** is **not thread-safe**.

- `Repo` and created mocks are intended to be used from a single thread.
- Concurrent calls to mocks from multiple threads can lead to race conditions
  and undefined behavior.

## Simple example

```cpp
#include <comock/comock.h>

#include <cassert>
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
  repo.setUnexpectedCallHandler([](std::optional<std::string> const&) {
    assert(false && "Unexpected call");
  });
  repo.setMissingCallHandler(
      [](std::string const&) { assert(false && "Missing call"); });

  auto const mock = repo.create<Mock>();

  repo.expectCall("foo", *mock, &Interface::foo, [](int a, std::string b) {
    std::cout << "foo called with " << a << " and " << b << "\n";
    return a;
  });

  auto const value = mock->foo(42, "test");
  assert(value == 42);

  return 0;
}
```

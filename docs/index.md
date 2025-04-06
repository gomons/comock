---
layout: home
title: Home
---

# comock - **C**++ **O**bject **MOCK** library

A lightweight, header-only library for mocking (mocks) and spying (spies) on
virtual methods in C++ classes and interfaces. Its main focus is simplicity.

## Features

- Header-only and minimalistic (but depends on [boost.preprocessor](https://github.com/boostorg/preprocessor))
- Mock and spy on C++ virtual methods
- Easy call sequence verification

## Why was this library created?

I was working on a project that didn't have a mocking library. Instead of adding
a third-party dependency, I quickly hacked together a simple solution. Later, we
switched to **gMock**, but I liked the result and decided to share it on GitHub.

## Limitations

**comock** is **not thread-safe**.

- `Repo` and created mocks are intended to be used from a single thread.
- Concurrent calls to mocks from multiple threads can lead to race conditions
  and undefined behavior.

## Requirements and dependencies

**comock** requires C++17 or later. It uses `std::any` and `std::optional` from
the C++ standard library. If you are using an older C++ version, you can switch
to the `boost` library by replacing all occurrences of `std::any` and
`std::optional` with `boost::any` and `boost::optional` in the `comock.h` file.

**comock** also depends on the `boost.preprocessor` library. Since
`boost.preprocessor` is header-only, the entire **comock** library remains
header-only as well.

## Simple example

Here’s a minimal example of mocking a method and verifying a call.

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

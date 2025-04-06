---
layout: default
title: Quick start
---

# Simple example

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

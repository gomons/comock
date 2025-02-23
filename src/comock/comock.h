// MIT License
//
// Copyright (c) 2025 Siarhei Homan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <any>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include <boost/preprocessor/comparison.hpp>
#include <boost/preprocessor/control.hpp>
#include <boost/preprocessor/punctuation.hpp>
#include <boost/preprocessor/seq.hpp>

namespace comock {

namespace internal {

class ExpectedCallbackQueue {
 public:
  template <typename ReturnType, typename Mock, typename... Args>
  void push(std::string description,
            Mock const& mock,
            ReturnType (Mock::MockedType::*method)(Args...),
            std::function<ReturnType(Args...)> callback) {
    callbacks_.push_back(std::make_tuple(std::move(description),
                                         reinterpret_cast<uintptr_t>(&mock),
                                         method, std::move(callback)));
  }

  template <typename ReturnType, typename Mock, typename... Args>
  void push(std::string description,
            Mock const& mock,
            ReturnType (Mock::MockedType::*method)(Args...) const,
            std::function<ReturnType(Args...)> callback) {
    callbacks_.push_back(std::make_tuple(std::move(description),
                                         reinterpret_cast<uintptr_t>(&mock),
                                         method, std::move(callback)));
  }

  void pop() { callbacks_.pop_front(); }

  bool isEmpty() const { return callbacks_.empty(); }

  template <typename ReturnType, typename Mock, typename... Args>
  bool peekMatch(Mock const& mock,
                 ReturnType (Mock::MockedType::*method)(Args...)) const {
    return matchInternal(reinterpret_cast<uintptr_t>(&mock), method);
  }

  template <typename ReturnType, typename Mock, typename... Args>
  bool peekMatch(Mock const& mock,
                 ReturnType (Mock::MockedType::*method)(Args...) const) const {
    return matchInternal(reinterpret_cast<uintptr_t>(&mock), method);
  }

  std::string peekDescription() const {
    return std::get<0>(callbacks_.front());
  }

  template <typename ReturnType, typename... Args>
  std::function<ReturnType(Args...)> peekCallback() const {
    return std::any_cast<std::function<ReturnType(Args...)>>(
        std::get<3>(callbacks_.front()));
  }

 private:
  template <typename Method>
  bool matchInternal(uintptr_t const mock, Method method) const {
    auto const& front = callbacks_.front();

    auto const expected_mock = std::get<1>(front);
    if (expected_mock != mock) {
      return false;
    }

    auto const expected_method = std::any_cast<Method>(&std::get<2>(front));
    if (!expected_method || *expected_method != method) {
      return false;
    }

    return true;
  }

 private:
  using DescriptionMockMethodCallbackTuple =
      std::tuple<std::string, uintptr_t, std::any, std::any>;
  std::deque<DescriptionMockMethodCallbackTuple> callbacks_;
};

class FallbackCallbacks {
 public:
  template <typename ReturnType, typename Mock, typename... Args>
  void add(Mock const& mock,
           ReturnType (Mock::MockedType::*method)(Args...),
           std::function<ReturnType(Args...)> callback) {
    callbacks_[reinterpret_cast<uintptr_t>(&mock)].emplace_back(method,
                                                                callback);
  }

  template <typename ReturnType, typename Mock, typename... Args>
  void add(Mock const& mock,
           ReturnType (Mock::MockedType::*method)(Args...) const,
           std::function<ReturnType(Args...)> callback) {
    callbacks_[reinterpret_cast<uintptr_t>(&mock)].emplace_back(method,
                                                                callback);
  }

  template <typename ReturnType, typename Mock, typename... Args>
  std::function<ReturnType(Args...)> get(
      Mock const& mock,
      ReturnType (Mock::MockedType::*method)(Args...)) const {
    return getInternal<std::function<ReturnType(Args...)>>(
        reinterpret_cast<uintptr_t>(&mock), method);
  }

  template <typename ReturnType, typename Mock, typename... Args>
  std::function<ReturnType(Args...)> get(
      Mock const& mock,
      ReturnType (Mock::MockedType::*method)(Args...) const) const {
    return getInternal<std::function<ReturnType(Args...)>>(
        reinterpret_cast<uintptr_t>(&mock), method);
  }

 private:
  template <typename Callback, typename Method>
  Callback getInternal(uintptr_t const mock, Method method) const {
    auto const mock_callbacks_it = callbacks_.find(mock);

    if (mock_callbacks_it == callbacks_.end()) {
      return {};
    }

    auto const& mock_callbacks = mock_callbacks_it->second;

    for (auto callback_it = mock_callbacks.rbegin();
         callback_it != mock_callbacks.rend(); ++callback_it) {
      auto const method_ptr = std::any_cast<Method>(&std::get<0>(*callback_it));

      if (method_ptr && *method_ptr == method) {
        return std::any_cast<Callback>(std::get<1>(*callback_it));
      }
    }

    return {};
  }

 private:
  std::unordered_map<uintptr_t, std::vector<std::tuple<std::any, std::any>>>
      callbacks_;
};

struct RepoState {
  bool expectations_paused = false;
  ExpectedCallbackQueue expected_callback_queue = {};
  FallbackCallbacks fallback_callbacks = {};
  std::function<void(std::optional<std::string> const&)>
      unexpected_call_handler = {};
  std::function<void(std::string const&)> missing_call_handler = {};
};

template <class T>
class MockBase : public T {
 public:
  friend class Repo;

  using MockedType = T;

  template <typename... Args>
  MockBase(RepoState& repo_state, Args... args)
      : T(std::forward<Args>(args)...), repo_state_(repo_state) {}

 protected:
  template <typename ReturnType, typename... Args>
  ReturnType call(std::function<ReturnType(Args...)> const& default_callback,
                  ReturnType (T::*this_method)(Args...),
                  Args... args) {
    return callInternal(default_callback, this_method, std::move(args)...);
  }

  template <typename ReturnType, typename... Args>
  ReturnType call(std::function<ReturnType(Args...)> const& default_callback,
                  ReturnType (T::*this_method)(Args...) const,
                  Args... args) const {
    return callInternal(default_callback, this_method, std::move(args)...);
  }

 private:
  template <typename Method, typename ReturnType, typename... Args>
  ReturnType callInternal(
      std::function<ReturnType(Args...)> const& default_callback,
      Method this_method,
      Args... args) const {
    auto expectation_description = std::optional<std::string>{};

    if (!repo_state_.expectations_paused &&
        !repo_state_.expected_callback_queue.isEmpty()) {
      if (repo_state_.expected_callback_queue.peekMatch(*this, this_method)) {
        auto const expected_callback = repo_state_.expected_callback_queue
                                           .peekCallback<ReturnType, Args...>();
        repo_state_.expected_callback_queue.pop();
        return expected_callback(std::move(args)...);
      }

      expectation_description =
          repo_state_.expected_callback_queue.peekDescription();
      repo_state_.expected_callback_queue.pop();
    }

    auto const fallback_callback =
        repo_state_.fallback_callbacks.get(*this, this_method);

    if (fallback_callback) {
      return fallback_callback(std::move(args)...);
    }

    if (!repo_state_.expectations_paused &&
        repo_state_.unexpected_call_handler) {
      repo_state_.unexpected_call_handler(expectation_description);
    }

    return default_callback(std::move(args)...);
  }

 private:
  RepoState& repo_state_;
};

}  // namespace internal

class Repo {
 public:
  ~Repo() {
    while (!state_.expected_callback_queue.isEmpty()) {
      auto const description = state_.expected_callback_queue.peekDescription();
      state_.expected_callback_queue.pop();

      if (state_.missing_call_handler) {
        state_.missing_call_handler(description);
      }
    }
  }

  void setUnexpectedCallHandler(
      std::function<void(std::optional<std::string> const&)> handler) {
    state_.unexpected_call_handler = std::move(handler);
  }

  void setMissingCallHandler(std::function<void(std::string const&)> handler) {
    state_.missing_call_handler = std::move(handler);
  }

  void pauseExpectations() { state_.expectations_paused = true; }

  void resumeExpectations() { state_.expectations_paused = false; }

  template <class Mock, class... Args>
  std::unique_ptr<Mock> create(Args... args) {
    auto mock = std::make_unique<Mock>(state_, std::forward<Args>(args)...);
    mocks_.insert(reinterpret_cast<uintptr_t>(mock.get()));
    return mock;
  }

  template <typename Callback,
            typename Mock,
            typename ReturnType,
            typename... Args>
  void expectCall(std::string description,
                  Mock const& mock,
                  ReturnType (Mock::MockedType::*method)(Args...),
                  Callback&& callback) {
    expectedCallInternal(
        std::move(description), mock, method,
        std::function<ReturnType(Args...)>(std::forward<Callback>(callback)));
  }

  template <typename Callback,
            typename Mock,
            typename ReturnType,
            typename... Args>
  void expectCall(std::string description,
                  Mock const& mock,
                  ReturnType (Mock::MockedType::*method)(Args...) const,
                  Callback&& callback) {
    expectedCallInternal(
        std::move(description), mock, method,
        std::function<ReturnType(Args...)>(std::forward<Callback>(callback)));
  }

  template <typename Callback,
            typename Mock,
            typename ReturnType,
            typename... Args>
  void onCall(Mock const& mock,
              ReturnType (Mock::MockedType::*method)(Args...),
              Callback&& callback) {
    state_.fallback_callbacks.add(
        mock, method,
        std::function<ReturnType(Args...)>(std::forward<Callback>(callback)));
  }

  template <typename Callback,
            typename Mock,
            typename ReturnType,
            typename... Args>
  void onCall(Mock const& mock,
              ReturnType (Mock::MockedType::*method)(Args...) const,
              Callback&& callback) {
    state_.fallback_callbacks.add(
        mock, method,
        std::function<ReturnType(Args...)>(std::forward<Callback>(callback)));
  }

 private:
  template <typename Mock, typename Method, typename Callback>
  void expectedCallInternal(std::string description,
                            Mock const& mock,
                            Method method,
                            Callback&& callback) {
    if (mocks_.count(reinterpret_cast<uintptr_t>(&mock)) == 0) {
      throw std::invalid_argument{
          "[comock] Cannot set a method call expectation for a mock "
          "object that was not created in the repository."};
    }

    state_.expected_callback_queue.push(std::move(description), mock, method,
                                        std::forward<Callback>(callback));
  }

 private:
  std::unordered_set<uintptr_t> mocks_ = {};
  internal::RepoState state_ = {
      false,
      {},
      {},
      [](std::optional<std::string> const& description) {
        auto const& description_string =
            description ? *description : "No calls were expected.";
        std::cerr << "[comock] Unexpected method call. Expectation violated: "
                  << description_string << std::endl;
      },
      [](std::string const& description) {
        std::cerr << "[comock] Missing method call. Expectation violated: "
                  << description << std::endl;
      }};
};

}  // namespace comock

#define COMOCK_DEFINE_BEGIN(MockType, MockedType)                   \
  class MockType : public comock::internal::MockBase<MockedType> {  \
   public:                                                          \
    template <typename... Args>                                     \
    MockType(comock::internal::RepoState& repo_state, Args... args) \
        : comock::internal::MockBase<MockedType>{                   \
              repo_state, std::forward<Args>(args)...} {}

#define COMOCK_DEFINE_END \
  }                       \
  ;

#define COMOCK_METHOD(MethodName, ReturnType, ArgTypeSeq, SpecifierSeq)       \
  _COMOCK_PREFIX_SPECIFIERS(SpecifierSeq)                                     \
  ReturnType MethodName(_COMOCK_TO_PARAMS((void)ArgTypeSeq))                  \
      _COMOCK_POSTFIX_SPECIFIERS(SpecifierSeq) {                              \
    using Method =                                                            \
        ReturnType (MockedType::*)(COMOCK_TO_TYPES((void)ArgTypeSeq))         \
            _COMOCK_CONST_SPECIFIER((void)SpecifierSeq);                      \
    auto const method = static_cast<Method>(&MockedType::MethodName);         \
    auto const default_callback =                                             \
        [this](_COMOCK_TO_PARAMS((void)ArgTypeSeq)) {                         \
          if constexpr (std::is_abstract_v<MockedType>) {                     \
            return ReturnType();                                              \
          } else {                                                            \
            return MockedType::MethodName(_COMOCK_TO_ARGS((void)ArgTypeSeq)); \
          }                                                                   \
        };                                                                    \
    using Mock = comock::internal::MockBase<MockedType>;                      \
    return Mock::call(std::function{default_callback},                        \
                      method _COMOCK_COMMA_IF((void)ArgTypeSeq)               \
                          _COMOCK_TO_ARGS((void)ArgTypeSeq));                 \
  }

#define _COMOCK_TO_PARAMS(ArgTypeSeq) \
  BOOST_PP_SEQ_FOR_EACH_I(_COMOCK_EXPAND_PARAM, arg, ArgTypeSeq)

#define _COMOCK_EXPAND_PARAM(unused, Name, Index, Type)                        \
  BOOST_PP_IF(Index, _COMOCK_EXPAND_PARAM1, _COMOCK_EXPAND_PARAM2)(Type, Name, \
                                                                   Index)

#define _COMOCK_EXPAND_PARAM1(Type, Name, Index) \
  BOOST_PP_COMMA_IF(BOOST_PP_GREATER(Index, 1))  \
  Type BOOST_PP_CAT(Name, Index)

#define _COMOCK_EXPAND_PARAM2(Type, Name, Index)

#define COMOCK_TO_TYPES(ArgTypeSeq) \
  BOOST_PP_SEQ_FOR_EACH_I(_COMOCK_EXPAND_TYPE, arg, ArgTypeSeq)

#define _COMOCK_EXPAND_TYPE(unused1, unused2, Index, Type) \
  BOOST_PP_IF(Index, _COMOCK_EXPAND_TYPE1, _COMOCK_EXPAND_TYPE2)(Type, Index)

#define _COMOCK_EXPAND_TYPE1(Type, Index) \
  BOOST_PP_COMMA_IF(BOOST_PP_GREATER(Index, 1)) Type

#define _COMOCK_EXPAND_TYPE2(Type, Index)

#define _COMOCK_TO_ARGS(ArgTypeSeq) \
  BOOST_PP_SEQ_FOR_EACH_I(_COMOCK_EXPAND_ARG, arg, ArgTypeSeq)

#define _COMOCK_EXPAND_ARG(unused1, Name, Index, unused2) \
  BOOST_PP_IF(Index, _COMOCK_EXPAND_ARG1, _COMOCK_EXPAND_ARG2)(Name, Index)

#define _COMOCK_EXPAND_ARG1(Name, Index)        \
  BOOST_PP_COMMA_IF(BOOST_PP_GREATER(Index, 1)) \
  std::move(BOOST_PP_CAT(Name, Index))

#define _COMOCK_EXPAND_ARG2(Name, Index)

#define _COMOCK_COMMA_IF(ArgTypeSeq) \
  BOOST_PP_COMMA_IF(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ArgTypeSeq)))

#define _COMOCK_CONST_SPECIFIER(SpecifierSeq) \
  BOOST_PP_SEQ_FOR_EACH_I(_COMOCK_EXPAND_CONST, _, SpecifierSeq)

#define _COMOCK_EXPAND_CONST(unused1, unused2, unused3, Specifier) \
  BOOST_PP_CAT(_COMOCK_CONST_SPECIFIER_, Specifier)

#define _COMOCK_CONST_SPECIFIER_const const
#define _COMOCK_CONST_SPECIFIER_inline
#define _COMOCK_CONST_SPECIFIER_constexpr
#define _COMOCK_CONST_SPECIFIER_consteval
#define _COMOCK_CONST_SPECIFIER_virtual
#define _COMOCK_CONST_SPECIFIER_friend
#define _COMOCK_CONST_SPECIFIER_static
#define _COMOCK_CONST_SPECIFIER_volatile
#define _COMOCK_CONST_SPECIFIER_noexcept
#define _COMOCK_CONST_SPECIFIER_override
#define _COMOCK_CONST_SPECIFIER_final
#define _COMOCK_CONST_SPECIFIER_void

#define _COMOCK_POSTFIX_SPECIFIERS(SpecifierSeq) \
  BOOST_PP_SEQ_FOR_EACH_I(_COMOCK_EXPAND_POSTFIX_SPECIFIER, _, SpecifierSeq)

#define _COMOCK_EXPAND_POSTFIX_SPECIFIER(unused1, unused2, unused3, Specifier) \
  BOOST_PP_CAT(_COMOCK_POSTFIX_SPECIFIER_, Specifier)

#define _COMOCK_POSTFIX_SPECIFIER_const const
#define _COMOCK_POSTFIX_SPECIFIER_volatile volatile
#define _COMOCK_POSTFIX_SPECIFIER_noexcept noexcept
#define _COMOCK_POSTFIX_SPECIFIER_override override
#define _COMOCK_POSTFIX_SPECIFIER_final final
#define _COMOCK_POSTFIX_SPECIFIER_inline
#define _COMOCK_POSTFIX_SPECIFIER_constexpr
#define _COMOCK_POSTFIX_SPECIFIER_consteval
#define _COMOCK_POSTFIX_SPECIFIER_virtual
#define _COMOCK_POSTFIX_SPECIFIER_friend
#define _COMOCK_POSTFIX_SPECIFIER_static
#define _COMOCK_POSTFIX_SPECIFIER_void

#define _COMOCK_PREFIX_SPECIFIERS(SpecifierSeq) \
  BOOST_PP_SEQ_FOR_EACH_I(_COMOCK_EXPAND_PREFIX_SPECIFIER, _, SpecifierSeq)

#define _COMOCK_EXPAND_PREFIX_SPECIFIER(unused1, unused2, unused3, Specifier) \
  BOOST_PP_CAT(_COMOCK_PREFIX_SPECIFIER_, Specifier)

#define _COMOCK_PREFIX_SPECIFIER_inline inline
#define _COMOCK_PREFIX_SPECIFIER_constexpr constexpr
#define _COMOCK_PREFIX_SPECIFIER_consteval consteval
#define _COMOCK_PREFIX_SPECIFIER_virtual virtual
#define _COMOCK_PREFIX_SPECIFIER_friend friend
#define _COMOCK_PREFIX_SPECIFIER_static static
#define _COMOCK_PREFIX_SPECIFIER_const
#define _COMOCK_PREFIX_SPECIFIER_volatile
#define _COMOCK_PREFIX_SPECIFIER_noexcept
#define _COMOCK_PREFIX_SPECIFIER_override
#define _COMOCK_PREFIX_SPECIFIER_final
#define _COMOCK_PREFIX_SPECIFIER_void

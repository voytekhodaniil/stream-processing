#pragma once

#include <functional>

template <typename F> class FunctionWrapper {
  F f_;

public:
  FunctionWrapper(F f) : f_(f){};
  template <typename T> 
  std::invoke_result<F, T>::type operator()(T value) { return f_(value); }
};
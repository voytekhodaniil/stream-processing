#pragma once

template <typename F> class FunctionWrapper {
  F f_;

public:
  FunctionWrapper(F f) : f_(f){};
  template <typename T> T operator()(T value) { return f_(value); }
};
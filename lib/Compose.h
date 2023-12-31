#pragma once

#include <functional>
// #include <iostream>

template <typename T, typename F0, typename... F> class ComposeClass {
protected:
  F0 *f0_;
  ComposeClass<T, F...> tail_;

public:
  using Input = T;
  using Output = typename std::invoke_result<ComposeClass<T, F...>, T>::type;
  ComposeClass(F0 *f0, F *...f) : f0_(f0), tail_(f...) {}

  Output operator()(Input x) { return tail_((*f0_)(x)); }
  ~ComposeClass() { delete f0_; }

  ComposeClass(ComposeClass<T, F0, F...> &old)
      : f0_(new F0(*old.f0_)), tail_(old.tail_) {}
  ComposeClass<T, F0, F...> &operator=(ComposeClass<T, F0, F...> &other) {
    if (this == std::addressof(other))
      return *this;
    delete f0_;
    f0_ = new F0(*other.f0_);
    tail_ = other.tail_;
    return *this;
  }
};

template <typename T, typename F> class ComposeClass<T, F> {
protected:
  F *f_;

public:
  using Input = T;
  using Output = typename std::invoke_result<F, T>::type;
  ComposeClass(F *f) : f_(f) {}
  ~ComposeClass() { delete f_; }

  Output operator()(Input x) { return (*f_)(x); }

  ComposeClass(ComposeClass<T, F> &old) { f_ = new F(*old.f_); }
  ComposeClass<T, F> &operator=(ComposeClass<T, F> &other) {
    if (this == std::addressof(other))
      return *this;
    delete f_;
    f_ = new F(*other.f0_);
    return *this;
  }
};

template <typename T, typename F0, typename... F>
ComposeClass<T, F0, F...> Compose(F0 *f0, F *...f) {
  return ComposeClass<T, F0, F...>(f0, f...);
}

template <typename T, typename F0, typename... F>
ComposeClass<T, F0, F...> *NewCompose(F0 *f0, F *...f) {
  return new ComposeClass<T, F0, F...>(f0, f...);
}
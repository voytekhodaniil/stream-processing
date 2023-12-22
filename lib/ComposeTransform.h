#pragma once

#include <functional>
#include <optional>

template <typename T> struct CallTransformRealization {
  using Output = T;
  template <typename F> static const void call(T data, F *next) {
    (*next)(data);
  }
};

template <typename T> struct CallTransformRealization<std::optional<T>> {
  using Output = T;

  template <typename F> static const void call(std::optional<T> data, F *next) {
    if (data.has_value())
      (*next)(data.value());
  }
};

template <typename T> struct CallTransformRealization<std::vector<T>> { // TODO: make universal for any iterable class
  using Output = T;

  template <typename F> static const void call(std::vector<T> data, F *next) {
    for (auto &d : data)
      (*next)(d);
  }
};

template <typename T, typename F0, typename... F> class ComposeTransformClass {
protected:
  F0 *f0_;
  ComposeTransformClass<T, F...> tail_;

public:
  using Input = T;

  ComposeTransformClass(F0 *f0, F *...f) : f0_(f0), tail_(f...) {}

  void operator()(Input x) {
    CallTransformRealization<typename std::invoke_result<F0, T>::type>::call(
        (*f0_)(x), &tail_);
  }

  ~ComposeTransformClass() { delete f0_; }

  ComposeTransformClass(ComposeTransformClass<T, F0, F...> &old)
      : f0_(new F0(*old.f0_)), tail_(old.tail_) {}
  ComposeTransformClass<T, F0, F...> &
  operator=(ComposeTransformClass<T, F0, F...> &other) {
    if (this == std::addressof(other))
      return *this;
    delete f0_;
    f0_ = new F0(*other.f0_);
    tail_ = other.tail_;
    return *this;
  }
};

template <typename T, typename F> class ComposeTransformClass<T, F> {
protected:
  F *f_;

public:
  using Input = T;
  using Output = typename std::invoke_result<F, T>::type;
  ComposeTransformClass(F *f) : f_(f) {}
  ~ComposeTransformClass() { delete f_; }

  void operator()(Input x) { (*f_)(x); }

  ComposeTransformClass(ComposeTransformClass<T, F> &old) {
    f_ = new F(*old.f_);
  }
  ComposeTransformClass<T, F> &operator=(ComposeTransformClass<T, F> &other) {
    if (this == std::addressof(other))
      return *this;
    delete f_;
    f_ = new F(*other.f0_);
    return *this;
  }
};

template <typename T, typename F0, typename... F>
ComposeTransformClass<T, F0, F...> ComposeTransform(F0 *f0, F *...f) {
  return ComposeTransformClass<T, F0, F...>(f0, f...);
}

template <typename T, typename F0, typename... F>
ComposeTransformClass<T, F0, F...> *NewComposeTransform(F0 *f0, F *...f) {
  return new ComposeTransformClass<T, F0, F...>(f0, f...);
}

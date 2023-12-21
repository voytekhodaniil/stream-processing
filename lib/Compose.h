#pragma once

#include <functional>

// Deducting arguments for old-style functions

/**
 * @brief Specifies Intput and Output type of Callable
 * @details Generally, "Callable" is struct with defined operator() method. But
 * because of parameter overloading, we need provide call arguments, to get
 * result. So struct CallSignature by specialization defines types, that will be
 * using in Compose
 * @tparam T
 */
template <typename... T> struct CallSignature;

template <typename In, typename Out> struct CallSignature<Out(In)> {
  using InputType = In;
  using OutputType = Out;
};

template <typename In, typename Out> struct CallSignature<Out (*)(In)> {
  using InputType = In;
  using OutputType = Out;
};

template <class F> using ReturnType = typename CallSignature<F>::OutputType;
template <class F> using InputType = typename CallSignature<F>::InputType;

// Compose of different functions, or types for which CallSignature template
// specialized By using of compile-time polymorphism, achieving zero overhead
/**
 * @brief Providing zero-overhead composition of functions.
 * @details Recursive structure, that compiles to calls of types with
 * specizalization CallSignature, provided to constructor.
 * @code {.cpp}
 * Compose(a,b,c)(x) == c(b(a(x)))
 * @endcode
 *
 * @tparam F0
 * @tparam ...F
 */
template <typename F0, typename... F> class Compose {
  F0 f0_;
  Compose<F...> tail_;

public:
  Compose(F0 f0, F... f) : f0_(f0), tail_(f...) {}

  ReturnType<Compose<F...>> operator()(InputType<F0> x) {
    return tail_(f0_(x));
  }
};

template <typename F> class Compose<F> {
  F f_;

public:
  Compose(F f) : f_(f) {}

  ReturnType<F> operator()(InputType<F> x) { return f_(x); }
};

// Allowing to use Compose() as stage of
template <typename In, typename... T> struct CallSignature<Compose<In, T...>> {
  using InputType = typename CallSignature<In>::InputType;
  using OutputType = typename CallSignature<Compose<T...>>::OutputType;
};

template <typename In> struct CallSignature<Compose<In>> {
  using InputType = typename CallSignature<In>::InputType;
  using OutputType = typename CallSignature<In>::OutputType;
};

// Implementation for lambdas
// As it not possible to deduct lambda arguments as old-style functions, to keep
// call optimizations, specify Input/Output type of lambda
template <typename... T> class LambdaStage;

template <typename F, typename In, typename Out> class LambdaStage<F, In, Out> {
  F f_;

public:
  LambdaStage(F f) : f_(f) {}

  Out operator()(In x) { return f_(x); }
};

template <typename In, typename Out> struct LambdaStage<In, Out> {
  template <typename F> static LambdaStage<F, In, Out> build(F f) {
    return LambdaStage<F, In, Out>(f);
  };
};

template <typename F, typename In, typename Out>
struct CallSignature<LambdaStage<F, In, Out>> {
  using InputType = In;
  using OutputType = Out;
};
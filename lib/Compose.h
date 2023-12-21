#pragma once

#include <functional>

template <typename T, typename F0, typename... F>
class ComposeClass {
    F0 f0_;
    ComposeClass<T, F...> tail_;

   public:
    using Input = T;
    using Output = typename  std::invoke_result< ComposeClass<T, F...>,T>::type;
    ComposeClass(F0 f0, F... f) : f0_(f0), tail_(f...) {}

    Output operator()(Input x) {
        return tail_(f0_(x));
    }
};

template <typename T, typename F>
class ComposeClass<T, F> {
    F f_;

   public:
    using Input = T;
    using Output = typename std::invoke_result<F,T>::type;
    ComposeClass(F f) : f_(f) {}

    Output operator()(Input x) { return f_(x); }
};

template <typename T, typename F0, typename... F>
ComposeClass<T, F0, F...> Compose(F0 f0, F... f) {
    return ComposeClass<T, F0, F...>(f0, f...);
}
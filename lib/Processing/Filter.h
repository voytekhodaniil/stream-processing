
#include <optional>
template <typename F> class LambdaFilter {
  F f_;

public:
  LambdaFilter(F f) : f_(f) {}
  template <typename T>
  std::optional<T> operator()(T data) {
    if (f_(data))
      return {data};
    else
      return {};
  }
};
#pragma once
#include "Input.h"
#include <optional>
#include <stdexcept>

template <typename T> class RangeInput : public virtual Input<T> {
  T _from;
  T _to;
  T _step;
  T _current;

public:
  /**
   * @brief Construct a new Range Input< T> object
   * @warning step must be greater than 0, from must be smaller than to
   * @param from
   * @param to
   * @param step
   */
  RangeInput<T>(T from, T to, T step) : _from(from), _to(to), _step(step) {}
  void start() { _current = _from; }
  void stop() {}
  bool has_next() { return _current + _step < _to; }
  std::optional<T> get_next() {
    if (!has_next())
      return {};
    _current = _current + _step;
    return {_current};
  }
};
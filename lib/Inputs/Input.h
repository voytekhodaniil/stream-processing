#pragma once

#include <optional>
template <typename T> class Input {
public:
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual std::optional<T> get_next() = 0;
};

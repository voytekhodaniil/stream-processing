#include <iostream>
#include <ostream>

#pragma once
#include "../Compose.h"
#include <fstream>
#include <iostream>
#include <string>

class LogOutput {
  std::ostream &output;

public:
  LogOutput(std::ostream &source = std::cout) : output(source) {}
  template <typename T> T operator()(T data) {
    output << data << std::endl;
    return data;
  }
  ~LogOutput() {}
};

template <typename F> class LogOutputLambda {
  std::ostream *output;
  F f_;

public:
  LogOutputLambda(F f, std::ostream *source = &std::cout)
      : output(source), f_(f) {}
  template <typename T> T operator()(T data) {
    f_(*output, data);
    return data;
  }
};
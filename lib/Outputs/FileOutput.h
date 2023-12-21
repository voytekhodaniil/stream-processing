#pragma once
#include "../Compose.h"
#include <fstream>
#include <iostream>
#include <string>

class FileOutput {
  std::ofstream *output;

public:
  FileOutput(std::string path) { output = new std::ofstream(path); }
  template <typename T> T operator()(T data) {
    *output << data;
    return data;
  }
  ~FileOutput() {
    output->close();
    delete output;
  }
};

template <typename F> class FileOutputLambda {
  std::ofstream *output;
  F f_;

public:
  FileOutputLambda(std::string path, F f) : f_(f) {
    output = new std::ofstream(path);
  }
  template <typename T> T operator()(T data) {
    f_(*output, data);
    return data;
  }
  ~FileOutputLambda() {
    output->close();
    delete output;
  }
};
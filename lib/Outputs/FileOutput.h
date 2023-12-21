#pragma once
#include "../Compose.h"
#include <fstream>
#include <iostream>
#include <string>

class FileOutput {
  std::ofstream *output;

public:
  FileOutput(std::string path) {
    output = new std::ofstream(path);
    std::cout << "Created" << std::endl;
  }
  template <typename T> T operator()(T data) {
    *output << data;
    return data;
  }
  ~FileOutput() {
    std::cout << "Deleted" << std::endl;
    output->close();
    delete output;
  }
};
#pragma once
#include "../Compose.h"
#include <fstream>
#include <string>

template <typename T> class FileOutput;

template <> class FileOutput<std::string> {
  std::fstream output;

public:
  FileOutput(std::string path) { output = std::fstream(path); }
  std::string operator()(std::string data) {
    output << data;
    return data;
  }
};
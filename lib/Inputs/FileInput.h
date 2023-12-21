#pragma once

#include "Input.h"
#include <fstream>
#include <optional>
#include <string>

template <typename T> class FileInput;

template <> class FileInput<std::string> : public virtual Input<std::string> {
  std::ifstream _file;
  std::string _path;

public:
  FileInput(std::string path) : _path(path) {}
  void start() { _file = std::ifstream(_path); }
  void end() { _file.close(); }
  std::optional<std::string> get_next() {
    std::string line;
    if (!std::getline(_file, line)) {
      return {};
    }
    return {line};
  }
};

using FileLineInput = FileInput<std::string>;

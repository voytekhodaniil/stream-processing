#pragma once
#include "Compose.h"
#include "Inputs/Input.h"

template <typename Input, class Processing> class SyncProcessing {
  Input *input;
  Processing *processing;

public:
  SyncProcessing(Input *input_, Processing *processing_)
      : input(input_), processing(processing_){};

  size_t run() {
    size_t count = 0;
    input->start();

    while (true) {

      auto input_data = input->get_next();
      if (!input_data.has_value())
        break;

      auto output_data = (*processing)(input_data.value());
      ++count;
    }
    input->stop();
    return count;
  }

  ~SyncProcessing() {
    delete processing;
    delete input;
  }
};
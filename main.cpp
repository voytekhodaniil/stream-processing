#include "lib/Compose.h"
#include "lib/ComposeTransform.h"
#include "lib/Inputs/FileInput.h"
#include "lib/Inputs/RangeInput.h"
#include "lib/Outputs/FileOutput.h"
#include "lib/Outputs/LogOutput.h"
#include "lib/Processing/Filter.h"
#include "lib/Processing/FunctionWrapper.h"
#include "lib/SyncProcessing.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <thread>

int a(int i) { return i * 2; }
int print(int i) {
  std::cout << 'c' << i << std::endl;
  return i;
}

std::string print_string(std::string p) {
  std::cout << p << std::endl;
  return p;
}

void task1(std::string msg) { std::cout << "task1 says: " << msg; }

void test_func(FileOutput *f) { (*f)(10); }

template <typename T> class SumCalls {
  T default_;

public:
  SumCalls(T base) : default_(base){};
  T operator()(T value) {
    T current = default_;
    default_ = value;
    return current;
  }
};

int main(int, char **) {

  std::chrono::milliseconds timespan(10);
  auto slow_task = new FunctionWrapper([timespan](int i) {
    std::this_thread::sleep_for(timespan);
    return i;
  });

  auto filter_even = new LambdaFilter([](int i) { //
    return (i % 2);
  });

  auto print_to_stdout = new FunctionWrapper([]<typename T>(T i) {
    std::cout << i << std::endl;
    return i;
  });

  SyncProcessing(
      new RangeInput(0, 100 + 1, 1),
      NewComposeTransform<int>(         //
          filter_even, new LogOutput(), //
          new FileOutputLambda(
              "test.txt", [](std::ofstream &f, int i) { f << i << '\n'; }) //
          ))
      .run();
}

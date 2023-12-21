#include "lib/Compose.h"
#include "lib/Inputs/FileInput.h"
#include "lib/Inputs/RangeInput.h"
#include "lib/Outputs/FileOutput.h"
#include "lib/Processing/FunctionWrapper.h"
#include "lib/SyncProcessing.h"
#include <chrono>
#include <iostream>
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
  int v = 8841;
  auto print_line = [v]<typename T>(T i) {
    std::cout << v << ' ' << i << std::endl;
    return i;
  };

  SyncProcessing(new RangeInput(0, 10, 1),
                 NewCompose<int>(                     //
                     new SumCalls(0),                 //
                     new FunctionWrapper(print_line), //
                     new FileOutput("test.txt")       //
                     ))
      .run();

  // std::thread t1(processing, 20);
  // std::thread t2(processing, 30);
  // std::thread t3(processing, 40);
  // t1.detach();
  // t2.detach();
  // t3.detach();
  // std::cout << "Sleep:\n";
  // std::chrono::milliseconds timespan(10); // or whatever
  // std::this_thread::sleep_for(timespan);
  // std::cout << "Done:\n";
}

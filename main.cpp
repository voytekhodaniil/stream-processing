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

  // test_func(new FileOutput("test.txt"));
  int v = 8841;
  auto print_line = [v]<typename T>(T i) {
    std::cout << v << ' ' << i << std::endl;
    return i;
  };

  // auto f = Compose<int>(new FunctionCall(a),                             //
  //                       new FunctionCall([](int a) { return a * 123; }), //
  //                       new FunctionCall(print_line),                    //
  //                       new FileOutput("test.txt")                       //
  // );
  auto f = Compose<int>(new SumCalls(0), new FunctionWrapper(print_line));
  auto f1 = f;
  f(5);
  f(10);
  f(20);

  f1(5);
  // f1(5);
  // f1(5);

  // int sum = 5;

  // auto interestingStage =
  //     LambdaStage<int, int>::build([&sum](int input) -> int {
  //       sum += 1;
  //       return input * sum;
  //     });

  // Compose processing(interestingStage, print);
  // //   std::cout << processing(1) << std::endl;
  // //   std::cout << processing(1) << std::endl;
  // //   std::cout << processing(1) << std::endl;
  // //   std::cout << processing(1) << std::endl;

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

  // Task

  // std::cout << SyncProcessing(RangeInput(0, 10, 1), //
  //                             Compose(a, print,
  //                                     LambdaStage<int, std::string>::build(
  //                                         [](int input) -> std::string {
  //                                           return std::to_string(input) +
  //                                           '\n';
  //                                         }),
  //                                     FileOutput<std::string>("./test.txt")))
  //                  .run()
  //           << std::endl;
}

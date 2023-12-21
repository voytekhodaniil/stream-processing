#include "lib/Compose.h"
#include "lib/Inputs/FileInput.h"
#include "lib/Inputs/RangeInput.h"
#include "lib/Outputs/FileOutput.h"
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

int main(int, char **) {
  auto print_line = []<typename T>(T i) {
    std::cout << i << std::endl;
    return i;
  };

  Compose<int>(
      a, print_line, [](int i) { return i * 10; }, print_line)(5);

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

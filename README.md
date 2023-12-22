# Stream processing library
This library provides convenient and effective realization for processing data, parallel and async.
Main aim - by utilizing compile-time polymorphism, make that kind of wrapper, which will work similar to default spaghetti-like realization. Developing this idea for multithreaded make this lib ideal for High-throughput parsing and data processing.

Project done as study project. So:
- [Lab1.md](Lab 1)
- [Lab2.md](Lab 2)
- [Lab3.md](Lab 3)

# Example of usage 
Simple example - writing to file only odd numbers from 0 to 100;
```c++
SyncProcessing(
    new RangeInput(0, 100, 1),
    NewComposeTransform<int>( //
        filter_even,
        print_to_stdout, //
        new FileOutputLambda(
            "test.txt", [](std::ofstream &f, int i) { f << i << '\n'; }) //
        ))
    .run()
```
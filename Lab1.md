# Lab 1
Project structure:

`SyncProcessing` - class that for each item in `Input` calls `Processing`

 `Input<T>` - abstract class, that describes some source of data with type `T`. Main method is `get_next()->std::optional<T>`


`Processing` - any structure with implemented `operator()`. With ` std::invoke_result<Processing, T>` extracting return type for input type `T`. So it possible to make conceptual class, for example Log, that can log multiple type of input data.

`ComposeClass` - main part of lab1. It shows power of compile time polymorphism. `Compose` - wrapper on ComposeClass, to deduct templates, transforms `Compose(a,b,c,d)`, where a,b,c,d - `Processing`s to a new `Processing`, call of which is equal to `d(c(b(a())))`. If compare resulting asm of compile-time and run-time polymorphic sollutions, it is seen, that compile time builds to 
```asm 
call a
call b
call c
call d
```
When run-time have multiply type casting, which make calls slowly. 

`ComposeTransformClass` - class similar to ComposeClass, but call of it does not return class. Class provide filtering and expanding arrays: by specific realizations of call if function returns std::optionals and std::vector respectively.

Firstly imagined as example of inheritance with templates and recursion, but it is not possible to recursively replace class. (If do it with templates, we need specify template parameter, that take parameter, that take parameter... ). Maybe it is possible to do that with marcos, but because `ComposeClass` have only one non trivial method (copy assignment), I consider that it is better to just copy and replace. Actually ComposeClass may be removed, but I stay it as elegant example, and it is also useful in some cases.


Some usefull classes:
- FileLineInput = FileInput<std::string> - read lines from file
- RangeInput<T> - for loop example
- FileOutput<T> - writes data to file, using std::fstream
- FileOutputLambda<T> - writes data to file, using std::fstream, formatted by lambda function provided as argument
- LogOutput - prints to provided ostream data separeted by new lines
- FunctionWrapper - wrapper to any callable function. Needed because lambdas cant be deleted - so we need specific realization of destruction of object.
- LambdaFilter - filter data by result of lambda provided as argument.
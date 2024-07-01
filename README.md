# VisualBenchmarking
Visual Benchmarking using C++ and Chrome Tracing for single threaded projects, multithreading will be supported in the future

#### Usage
##### Include "benchmark.h" in to your project

##### To start the session for benchmarking, call this function
```
START_BENCHMARK_SESSION("Session Name");
```
This profiles into a file that can be opened in Chrome tracing to view the benchmarking results
```
START_CONSOLE_SESSION("Session Name");
```
This writes the benchmarked readings into the console.

##### To profile any function in your benchmark while your session is active, add this function in the beginning of the code of your function
```
PROFILE_FUNCTION();
or
PROFILE_FUNCTION_DETAILED();
```

##### To end the session, call this function
```
END_SESSION();
```

##### Example
```
#include "../benchmark.h"
#include <iostream>

int fibonacci(int number) {
    PROFILE_FUNCTION();     //profiling this function for benchmarking
    if (number == 1) 
        return 1;
    if (number == 0)
        return 0;
    return fibonacci(number - 1) + fibonacci(number - 2);
}

int main() {
    int number;
    std::cin >> number;
    START_BENCHMARK_SESSION("Fibonacci");     //starting the session from where benchmarking starts
    
    std::cout << fibonacci(number) << std::endl;    //this code will be benchmarked
    
    END_BENCHMARK_SESSION();      //ending the session
}
```

##### Open [Chrome Tracing](chrome://tracing/) which comes pre-installed with Google Chrome by typing chrome://tracing
##### After executing your code a file named results.json would appear drag and drop your json file in chrome tracing

##### To turn off benchmarking just mark BENCHMARKING OFF at line number 6 in the "benchmark.h" header file
```
#define BENCHMARKING OFF
```

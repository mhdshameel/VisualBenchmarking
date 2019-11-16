#include "../benchmark.h"
#include <iostream>

#define BENCHMARKING 1
#if BENCHMARKING
    #define PROFILE_SCOPE(name) InstrumentationTimer timer(name)
    #define START_SESSION(name) Instrumentor::Get().BeginSession(name)
    #define END_SESSION() Instrumentor::Get().EndSession()
    #define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
    #define PROFILE_FUNCTION_DETAILED() PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
    #define PROFILE_FUNCTION() 
    #define PROFILE_FUNCTION_DETAILED()
#endif

int fibonacci(int number) {
    PROFILE_FUNCTION();

    if (number == 1) 
        return 1;
    if (number == 0)
        return 0;
    
    return fibonacci(number - 1) + fibonacci(number - 2);
}

int main() {
    int number;
    std::cin >> number;
    START_SESSION("Fibonacci");
    std::cout << fibonacci(number) << std::endl;
    END_SESSION();
}
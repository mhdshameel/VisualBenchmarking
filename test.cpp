#include "Instrumentor.h"
#include <iostream>

int fibonacci(int number) {
    PROFILE_FUNCTION();

    if (number == 1) 
        return 1;
    if (number == 0)
        return 0;
    
    return fibonacci(number - 1) + fibonacci(number - 2);
}

int main() {
    Instrumentor::Get().BeginSession("Session Name");
    std::cout << fibonacci(100) << std::endl;
    Instrumentor::Get().EndSession();
}
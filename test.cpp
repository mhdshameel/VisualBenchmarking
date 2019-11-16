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
    int number;
    std::cin >> number;
    Instrumentor::Get().BeginSession("Session Name");
    std::cout << fibonacci(number) << std::endl;
    Instrumentor::Get().EndSession();
}
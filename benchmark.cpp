#include "Benchmark.h"


std::once_flag IInstrumentor::_creation_once_flag;
IInstrumentor* IInstrumentor::instance = nullptr;

IInstrumentor& IInstrumentor::Get() {
    if(instance) return *instance;

    throw std::exception("Instrumentor instance not created");
}

IInstrumentor& IInstrumentor::Create(bool output_to_console) {
    std::call_once(_creation_once_flag,
        [output_to_console]() {
            if (output_to_console)
                instance = new ConsoleInstrumentator();
            else
                instance = new FilestreamInstrumentor();
        }
    ); //thread safe initialization
    return *instance;
}

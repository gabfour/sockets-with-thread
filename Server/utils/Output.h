#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include "Semaphore.h"
#include "../GameConfig.h"

class Output
{
private:
	static Output* singleton_;
	CSemaphore sem_std_out;
	Output();
	

public:
    template <typename... T> void print(T...);
    template <typename... T> void print_debug(T...);
    void print_error(const std::string, const char*, bool = true);
    void print_error(const char*, const char*, bool = true);
    void print_error(const char*, bool = true);
    bool confirm_exit();

    Output(Output& other) = delete;
    void operator=(const Output&) = delete;

    static Output* GetInstance();
};

template <typename... T> void Output::print(T... args)
{
    sem_std_out.wait();
    ((std::cout << args), ...);
    std::cout.flush();
    sem_std_out.notify();
}


template <typename... T> void Output::print_debug(T... args)
{
#if DEBUG == true
    sem_std_out.wait();
    ((std::cout << args), ...);
    std::cout.flush();
    sem_std_out.notify();
#endif
}

#endif

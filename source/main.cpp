#include <iostream>

#include "computer.h"
#include "config.h"

void version()
{
    std::cout << NAME << ": version " << VERSION << std::endl << "built at " << __TIME__ << std::endl;
}

int main(int argv, char **argc)
{
    return 0;
}
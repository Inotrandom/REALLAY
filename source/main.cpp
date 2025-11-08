#include <iostream>
#include "computer.h"

int main(int argv, char **argc)
{
    computer_t comp = computer_t();
    comp.create_relay(1, 2);
    comp.create_relay(2, 3);
}
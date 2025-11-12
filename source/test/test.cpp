#include "test.h"
#include "computer.h"

static test_t TEST_TEST = test_t("test_test", []()
{
    return true;
});

static test_t TEST_RELAY = test_t("test_relay", []()
{
    computer_t comp = computer_t();
    
    comp.create_relay(0, {fct_conduitptr(2)}, {fct_conduitptr(1)}, true);
    comp.create_relay(1, {}, {}, false);
    comp.create_relay(2, {}, {}, false);

    comp.compute();

    return false;
});

int main(int argv, char **argc)
{
    TEST_TEST.run();
}
#include "test.h"
#include "computer.h"

static test_t TEST_TEST = test_t("test_test", []()
{
    return true;
});

static test_t TEST_RELAY = test_t("test_relay", []()
{
    computer_t comp = computer_t();

    // r0
    // [set] > r1
    // [pass] > r2
    //
    // r1
    // [set] > r2
    // [pass]
    //
    // r2
    // [set] > r3
    // [pass]
    //
    // r3
    // [set]
    // [pass]

    // Intended behavior:
    // r0 sets r1 to true
    // r1 sets r2 to true
    // r1 can now pass r2; r3 is now true
    
    // If any of the conduits connected to the inbound PASS terminal of a relay
    // are TRUE, then the relay will set all of the outbound connections to TRUE
    // if and only if the relay's value is TRUE

    // Relays who have no conduits connected to the inbound PASS terminal will
    // implicitly set all of the outbound connections to TRUE if and only if
    // the relay's value is true
    comp.create_relay(0, {fct_conduitptr(2, CONDUIT_TYPE::PASS)}, {fct_conduitptr(1, CONDUIT_TYPE::SET)}, true);
    comp.create_relay(1, {}, {}, false);
    comp.create_relay(2, {}, {}, false);
    comp.create_relay(3, {}, {}, false);

    comp.compute();

    return false;
});

int main(int argv, char **argc)
{
    TEST_TEST.run();
}
#include "computer.h"

void computer_t::complete_conduit_references()
{
    for (auto [k, p_relay] : m_components)
    {
        for (auto p_conduit : p_relay->get_pass_terminal())
        {
            // Request is invalid if this is false
            if (is_handle(p_conduit->outrequest) == false) continue;

            // Fulfill the request... because you can
            p_conduit->out = m_components[p_conduit->outrequest];
        }
    }
}

void computer_t::compute()
{
    uint64_t total_operations;
    
    for (auto p_relay : m_components)
    {
        
    }
}
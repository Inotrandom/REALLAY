#ifndef H_COMPUTER
#define H_COMPUTER

#include <map>
#include <cstdint>
#include "comp/relay.h"

class computer_t
{
public:
    auto is_handle(uint64_t which) -> bool
    {
        return (m_components.find(which) != m_components.end());
    }

    void create_relay(uint64_t handle, connections pass_connections, connections set_connections, bool value)
    {
        std::shared_ptr<relay_t> new_relay = std::make_shared<relay_t>(pass_connections, set_connections, value);

        if (is_handle(handle) == false) return;

        m_components[handle] = new_relay;
    }

    void complete_references()
    {

    }

    void compute()
    {
        uint64_t total_operations;
        bool busy = true;

        while (busy)
        {

        }
    }
private:
    std::map<uint64_t, std::shared_ptr<relay_t>> m_components{{}};
};

#endif
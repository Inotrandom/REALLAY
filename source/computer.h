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

    void create_relay(uint64_t handle, uint64_t handle_connection)
    {
        std::shared_ptr<relay_t> rel = std::make_shared<relay_t>(handle_connection);
        
        if (is_handle(handle) == true) return; // Anti-aliasing

        m_components[handle] = rel;
    }

    void complete_references()
    {
        for (auto &[handle, relay] : m_components)
        {
            if (is_handle(relay->get_handle_connection()) == false) continue;

            relay->connect(m_components[relay->get_handle_connection()]);
        }
    }
private:
    std::map<uint64_t, std::shared_ptr<relay_t>> m_components{{}};
};

#endif
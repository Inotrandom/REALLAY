#ifndef H_RELAY
#define H_RELAY

#include <memory>
#include <cstdint>
#include <vector>
#include <thread>

const std::chrono::milliseconds SWITCH_ON = std::chrono::milliseconds(5);
const std::chrono::milliseconds SWITCH_OFF = std::chrono::milliseconds(15);

enum CONDUIT_TYPE // The connection type of the conduit
{
    SET,
    PASS
};

class relay_t;

struct conduit_t
{
    std::shared_ptr<relay_t> out{nullptr};
    uint64_t outrequest{0};
    bool value{false};
    CONDUIT_TYPE conduit_type{CONDUIT_TYPE::SET};

    conduit_t(uint64_t aoutrequest, CONDUIT_TYPE aconduit_type)
    {
        outrequest = aoutrequest;
        conduit_type = aconduit_type;
    }
};

inline auto fct_conduitptr(uint64_t aoutrequest, CONDUIT_TYPE aconduit_type) -> std::shared_ptr<conduit_t>
{
    std::shared_ptr<conduit_t> res = std::make_shared<conduit_t>(aoutrequest, aconduit_type);
    return res;
}

// Beautiful template syntax
typedef std::vector<std::shared_ptr<conduit_t>> connections;

/**
 * @brief Binary component
 */
class relay_t
{
public:
    relay_t(connections pass_connections, connections set_connections, bool value, bool pass_value = false)
    {
        m_pass_terminal = pass_connections;
        m_set_terminal = set_connections;
        m_value = value;
        m_pass_terminal_value = pass_value;
    }

    auto get_value() -> bool&
    {
        return m_value;
    }

    auto get_pass_terminal() -> connections&
    {
        return m_pass_terminal;
    }

    auto get_set_terminal() -> connections&
    {
        return m_set_terminal;
    }

    void connect_pass_terminal(std::shared_ptr<conduit_t> which)
    {
        m_pass_terminal.push_back(which);
    }

    void connect_set_terminal(std::shared_ptr<conduit_t> which)
    {
        m_set_terminal.push_back(which);
    }

    void set(bool to)
    {
        if (to == get_value()) return;

        std::chrono::milliseconds t;

        if (to == true)
        {
            t = SWITCH_ON;
        }
        else
        {
            t = SWITCH_OFF;
        }

        std::this_thread::sleep_for(t);
    }

    auto get_pass_value() -> bool&
    {
        return m_pass_terminal_value;
    }

    /**
     * @brief Compute the relay
    */
    void compute()
    {
        bool will_set = false;
        for (auto connection : m_set_terminal)
        {
            if (connection->value == true)
            {
                will_set = true;
                break;
            }
        }

        set(will_set);

        for (auto connection : m_pass_terminal)
        {
            // If it can pass, and the value is true...
            connection->value = (m_value && m_pass_terminal_value);
        }
    }
private:
    connections m_pass_terminal{{}};
    connections m_set_terminal{{}};

    bool m_value{false};
    bool m_pass_terminal_value{false};
};

#endif
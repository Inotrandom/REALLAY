#ifndef H_RELAY
#define H_RELAY

#include <memory>
#include <cstdint>
#include <vector>
#include <thread>

const std::chrono::milliseconds SWITCH_ON = std::chrono::milliseconds(5);
const std::chrono::milliseconds SWITCH_OFF = std::chrono::milliseconds(15);

class relay_t;

struct conduit_t
{
    std::shared_ptr<relay_t> out{nullptr};
    std::shared_ptr<relay_t> in{nullptr};
    uint64_t outrequest{0};
    uint64_t inrequest{0};
    bool value{false};

    conduit_t(uint64_t ainrequest, uint64_t aoutrequest)
    {
        outrequest = aoutrequest;
        inrequest = ainrequest;
    }
};

auto fct_conduitptr(uint64_t ainrequest, uint64_t aoutrequest) -> std::shared_ptr<conduit_t>
{
    std::shared_ptr<conduit_t> res = std::make_shared<conduit_t>(ainrequest, aoutrequest);
    return res;
}

typedef std::vector<std::shared_ptr<conduit_t>> connections;

/**
 * @brief Binary component
 */
class relay_t
{
public:
    relay_t(connections pass_connections, connections set_connections, bool value)
    {
        m_value = value;
    }

    auto get_value() -> bool&
    {
        return m_value;
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
            connection->value = m_value;
        }
    }
private:
    std::vector<std::shared_ptr<conduit_t>> m_pass_terminal{{}};
    std::vector<std::shared_ptr<conduit_t>> m_set_terminal{{}};

    bool m_value{false};
};

#endif
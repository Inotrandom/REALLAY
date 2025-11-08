#ifndef H_RELAY
#define H_RELAY

#include <memory>
#include <cstdint>
#include <thread>

const std::chrono::milliseconds SWITCH_ON = std::chrono::milliseconds(5);
const std::chrono::milliseconds SWITCH_OFF = std::chrono::milliseconds(15);

/**
 * @brief Binary component
 */
class relay_t
{
public:
    relay_t(uint64_t handle_connection)
    {
        m_handle_connection = handle_connection;
    }

    auto get_value() -> bool&
    {
        return m_value;
    }

    auto get_handle_connection() -> uint64_t
    {
        return m_handle_connection;
    }

    /**
     * @brief Connect the relay's request (m_handle_connection) with a reference
     * to another relay_t object
     */
    void connect(std::shared_ptr<relay_t> to)
    {
        m_connection = to;
    }

    void compute()
    {
        std::chrono::milliseconds t;

        if (get_value() == true)
        {
            t = SWITCH_ON;
        }
        else
        {
            t = SWITCH_OFF;
        }

        std::this_thread::sleep_for(t);
        m_connection->get_value() = get_value();
    }
private:
    uint64_t m_handle_connection{0};

    std::shared_ptr<relay_t> m_connection{nullptr};

    bool m_value{false};
};

#endif
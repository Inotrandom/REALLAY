#ifndef H_TEST
#define H_TEST

#include <string>
#include <iostream>

struct test_t
{
    bool (*m_fn)();
    std::string m_name;

    test_t(const std::string name, bool (*fn)())
    {
        m_fn = fn;
        m_name = name;
    }

    void run()
    {
        bool res = m_fn();

        if (res == true)
        {
            std::cout << "test [" << m_name << "] passed without error.";
        }
        else if (res == false)
        {
            std::cout << "test [" << m_name << "] failed without error.";
        }
    }
};

#endif
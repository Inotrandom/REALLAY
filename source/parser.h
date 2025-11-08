#ifndef H_PARSER
#define H_PARSER

#include <string>
#include <sstream>
#include <vector>
#include <cstdint>

auto string_split(std::string& s, const std::string& delimiter) -> std::vector<std::string>
{
    std::vector<std::string> tokens;
    uint64_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) 
    {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    tokens.push_back(s);

    return tokens;
}

#endif
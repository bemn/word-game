#pragma once

#include <string>
#include <vector>

class InputSource {
public:
    virtual std::vector<std::wstring> read() = 0;
    virtual std::string description() const = 0;
    virtual ~InputSource() = default;
};

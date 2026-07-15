#pragma once

#include <string>

namespace sigrid_pdf{

struct Object{

    unsigned int objectNumber = 0;
    std::string description = "";

    virtual std::string getString() const = 0;

    std::string getObjectString() const;

};

}  // namespace sigrid_pdf
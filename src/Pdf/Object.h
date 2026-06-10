#pragma once

#include <string>

namespace myPdf{

    struct Object{

        unsigned int objectNumber = 0;
        std::string description = "";

        virtual std::string getString() const = 0;

        std::string getObjectString() const;

    };
}
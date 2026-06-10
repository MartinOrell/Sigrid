#pragma once

#include "Object.h"
#include "Pages.h"

namespace myPdf{

    struct Catalog : Object{

        Pages pages;

        std::string getString() const override;

    };
}
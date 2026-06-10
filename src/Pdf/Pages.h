#pragma once

#include <vector>

#include "Object.h"
#include "Page.h"

namespace myPdf{

    struct Pages : Object{

        std::vector<Page> kids;

        std::string getString() const override;

    };
}
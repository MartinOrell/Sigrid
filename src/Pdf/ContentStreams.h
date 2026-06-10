#pragma once

#include <vector>

#include "Object.h"
#include "ContentStream.h"

namespace myPdf{

    struct ContentStreams : Object{

        std::vector<ContentStream> streams;

        std::string getString() const override;

    };
}
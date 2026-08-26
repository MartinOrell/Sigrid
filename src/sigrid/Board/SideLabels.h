#pragma once

#include "sigrid/utilities/GraphicText/GraphicText.h"

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/String/String.h"

#include "sigrid/Board/BoardLabelContainer.h"

namespace sigrid{

struct SideLabels{

    BoardLabelContainer getContainer() const;

    sigrid_list::Vector<sigrid::GraphicText> labels;
    bool isVisible = false;
    sigrid::String fontFilename;
    float labelSizeFactor = 0.f; //fraction of tileHeight
};

}  // namespace sigrid


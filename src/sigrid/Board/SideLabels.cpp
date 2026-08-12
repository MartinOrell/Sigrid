#include "sigrid/Board/SideLabels.h"

sigrid::BoardLabelContainer sigrid::SideLabels::getContainer() const{

    sigrid::BoardLabelContainer container;
    container.isVisible = this->isVisible;
    container.size = this->labelSizeFactor;
    container.font = this->fontFilename;

    return container;
}
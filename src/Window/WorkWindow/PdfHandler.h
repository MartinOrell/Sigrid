#pragma once

#include <vector>
#include "../../Board/Board.h"
#include "../../Layout/LayoutGrid.h"

namespace sigrid{

    class PdfHandler{

        public:

            void updateLayout();
            void savePdf(const std::vector<sigrid::Board>& boards);

        private:
        
            typedef unsigned int LayoutItem;
            LayoutGrid m_layout;
    };
}
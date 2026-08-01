#pragma once

#include "sigrid/utilities/lists/VectorWithDisplayGrid.h"
#include "sigrid/Board/Board.h"
#include "sigrid/Layout/LayoutGrid.h"

namespace sigrid{

class PdfHandler{

  public:

    PdfHandler() = default;
    PdfHandler(const PdfHandler&) = default;
    PdfHandler(PdfHandler&&) = default;
    PdfHandler& operator=(const PdfHandler&) = default;
    PdfHandler& operator=(PdfHandler&&) = default;

    void updateLayout();
    void savePdf(const sigrid_list::VectorWithDisplayGrid<sigrid::Board>& boards);

  private:

    typedef unsigned int LayoutItem;
    LayoutGrid m_layout;
};

}  // namespace sigrid
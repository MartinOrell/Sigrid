#include "sigrid/Window/WorkWindow/PdfHandler.h"

#include <iostream>

#include <SFML/Graphics/Image.hpp>

#include "sigrid/Pdf/Pdf.h"
#include "sigrid/Pdf/Image.h"

void sigrid::PdfHandler::updateLayout(){

    unsigned int i = 0;
    for(int y = 7; y > 0; y-=2){
        for(unsigned int x = 1; x < 7; x+=2){
            m_layout.setFromXCoord(LayoutItem{i}, x);
            m_layout.setToXCoord(LayoutItem{i}, x+1);
            m_layout.setFromYCoord(LayoutItem{i}, y);
            m_layout.setToYCoord(LayoutItem{i}, y+1);
            i++;
        }
    }

    m_layout.setPx(0, 0.f);
    m_layout.setPx(1, 35.f);
    m_layout.setPx(2, 185.f);
    m_layout.setPx(3, 220.f);
    m_layout.setPx(4, 370.f);
    m_layout.setPx(5, 405.f);
    m_layout.setPx(6, 555.f);
    m_layout.setPx(7, 595.f);

    m_layout.setPy(0, 0.f);
    m_layout.setPy(1, 72.f);
    m_layout.setPy(2, 222.f);
    m_layout.setPy(3, 257.f);
    m_layout.setPy(4, 407.f);
    m_layout.setPy(5, 442.f);
    m_layout.setPy(6, 592.f);
    m_layout.setPy(7, 627.f);
    m_layout.setPy(8, 777.f);
    m_layout.setPy(9, 842.f);
}

void sigrid::PdfHandler::savePdf(const sigrid_list::VectorWithDisplayGrid<sigrid::Board>& boards){

    std::cout << "Preparing to save pdf" << std::endl;
    sigrid_pdf::Pdf pdf;

    for(unsigned int i = 0; i < boards.size(); i++){
        unsigned int pageId = i/12;
        unsigned int boardId = i%12;

        sigrid_pdf::Image pdImage;

        auto position_o = m_layout.getTopLeftPosition(boardId);

        if(position_o == std::nullopt){
            std::cerr << "WorkWindow: Failed getting position for board "
                << boardId << std::endl;
            return;
        }
        pdImage.xPos = position_o.value().x;
        pdImage.yPos = position_o.value().y;

        auto size_o = m_layout.getSize(boardId);

        if(size_o == std::nullopt){
            std::cerr << "WorkWindow: Failed getting size for board "
                << boardId << std::endl;
            return;
        }

        unsigned int entitledWidth = size_o.value().x;
        unsigned int entitledHeight = size_o.value().y;

        float quality = 4;

        auto board_o = boards.at(i);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();

        sigrid::Image sigridImage = board.getImage(entitledWidth*quality, entitledHeight*quality);

        pdImage.displayWidth = sigridImage.getWidth()/quality;
        pdImage.displayHeight = sigridImage.getHeight()/quality;
        pdImage.dataWidth = sigridImage.getWidth();
        pdImage.dataHeight = sigridImage.getHeight();
        
        std::cout << "loading data from " << board.getName()
            << " (" << i+1 << "/" << boards.size() << ")" << std::endl;
        pdImage.asciiHexStream = sigridImage.getAsciiHexStream().getStdString();
        std::cout << "data loaded" << std::endl;

        pdf.addImage(pageId, std::move(pdImage));
    }

    pdf.save("saveData/boards/pdf/boards.pdf");
}
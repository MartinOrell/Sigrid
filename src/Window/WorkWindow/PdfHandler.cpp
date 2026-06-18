#include "PdfHandler.h"

#include <iostream>
#include <sstream>
#include <iomanip>

#include <SFML/Graphics/Image.hpp>

#include "../../Pdf/Pdf.h"
#include "../../Pdf/Image.h"

using namespace sigrid;

void PdfHandler::updateLayout(){

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

void PdfHandler::savePdf(const std::vector<sigrid::Board>& boards){

    std::cout << "Preparing to save pdf" << std::endl;
    myPdf::Pdf pdf;

    for(unsigned int i = 0; i < boards.size(); i++){
        unsigned int pageId = i/12;
        unsigned int boardId = i%12;

        myPdf::Image pdImage;

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

        sf::Image sfImage = boards.at(i).getImage(entitledWidth*quality, entitledHeight*quality);
        
        pdImage.displayWidth = sfImage.getSize().x/quality;
        pdImage.displayHeight = sfImage.getSize().y/quality;
        pdImage.dataWidth = sfImage.getSize().x;
        pdImage.dataHeight = sfImage.getSize().y;
        
        std::cout << "loading data from " << boards.at(i).getName()
            << " (" << i+1 << "/" << boards.size() << ")" << std::endl;
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for(unsigned int y = 0; y < sfImage.getSize().y; y++){
            for(unsigned int x = 0; x < sfImage.getSize().x; x++){
                const auto& pixel = sfImage.getPixel({x,y});
                const auto& red = pixel.r;
                const auto& green = pixel.g;
                const auto& blue = pixel.b;

                ss << std::hex << std::setw(2) << static_cast<int>(red);
                ss << std::hex << std::setw(2) << static_cast<int>(red);
                ss << std::hex << std::setw(2) << static_cast<int>(red);
            }
        }
        pdImage.asciiHexStream = ss.str();
        std::cout << "data loaded" << std::endl;

        pdf.addImage(pageId, std::move(pdImage));
    }

    pdf.save("saveData/boards/pdf/boards.pdf");
}
#include "Pdf.h"

#include <iostream>
#include <fstream>

#include "Catalog.h"
#include "Pages.h"
#include "ProcedureSet.h"
#include "MediaBox.h"
#include "PageResources.h"
#include "ExternalObjects.h"
#include "ContentStreams.h"

using namespace myPdf;

Pdf::Pdf(){
    m_images.push_back(std::vector<Image>{});
}

void Pdf::addImage(const unsigned int pageId, const myPdf::Image& image){
    while(m_images.size() <= pageId){
        m_images.push_back(std::vector<Image>{});
    }
    m_images.at(pageId).push_back(image);

    if(m_images.size() > m_numPages){
        m_numPages = m_images.size();
    }
}

std::string header(const std::string& version){

    std::string s;
    s.append("%PDF-");
    s.append(version);
    s.append("\n\n");
    return s;
}

bool Pdf::save(const std::string& filename) const{

    std::cout << "Saving pdf " << filename << std::endl;

    std::ofstream file{filename};

    if(!file.is_open()){
        std::cerr << "Pdf: Failed opening file " << filename << std::endl;
        return false;
    }

    unsigned int nextON = 1; //nextObjectNumber
    std::vector<Object*> objectPtrs;

    Catalog catalog;
    catalog.description = "Catalog/Root";
    catalog.objectNumber = nextON++;
    objectPtrs.push_back(&catalog);

    catalog.pages.description = "Pages";
    catalog.pages.objectNumber = nextON++;
    objectPtrs.push_back(&catalog.pages);

    ProcedureSet procedureSet;
    procedureSet.description = "Procedure Set";
    procedureSet.objectNumber = nextON++;
    objectPtrs.push_back(&procedureSet);

    MediaBox mediaBox;
    mediaBox.description = "MediaBox for A4 size";
    mediaBox.objectNumber = nextON++;
    objectPtrs.push_back(&mediaBox);

    catalog.pages.kids.reserve(m_numPages);
    for(unsigned int pageId = 0; pageId < m_numPages; pageId++)
    {
        catalog.pages.kids.push_back(Page{});
        auto& page = catalog.pages.kids.back();

        page.description = "Page" + std::to_string(pageId);
        page.objectNumber = nextON++;
        objectPtrs.push_back(&page);
        page.parentObjectNumber = catalog.pages.objectNumber;
        page.mediaBoxObjectNumber = mediaBox.objectNumber;

        if(m_images.at(pageId).size() > 0){
            page.resources.description = "Page" + std::to_string(pageId) + " Resource Dictionary";
            page.resources.objectNumber = nextON++;
            objectPtrs.push_back(&page.resources);
            page.resources.procedureSetObjectNumber = procedureSet.objectNumber;
        }        

        if(m_images.at(pageId).size() > 0){
            page.resources.externalObjects.description = "Page" + std::to_string(pageId) + " External objects";
            page.resources.externalObjects.objectNumber = nextON++;
            objectPtrs.push_back(&page.resources.externalObjects);

            page.resources.externalObjects.xObjects.reserve(m_images.at(pageId).size());
        }
        
        for(unsigned int imageId = 0; imageId < m_images.at(pageId).size(); imageId++){
            page.resources.externalObjects.xObjects.push_back(ExternalObject{});
            auto& xObject = page.resources.externalObjects.xObjects.back();

            xObject.description = "Page" + std::to_string(pageId) + " Image" + std::to_string(imageId);
            xObject.objectNumber = nextON++;
            objectPtrs.push_back(&xObject);
            xObject.image = m_images.at(pageId).at(imageId);
        }

        if(m_images.at(pageId).size() > 0){
            page.contents.description = "Page" + std::to_string(pageId) + " Content streams";
            page.contents.objectNumber = nextON++;
            objectPtrs.push_back(&page.contents);

            page.contents.streams.reserve(m_images.at(pageId).size());
        }

        for(unsigned int imageId = 0; imageId < m_images.at(pageId).size(); imageId++){
            page.contents.streams.push_back(ContentStream{});
            auto& stream = page.contents.streams.back();

            stream.description = "Page" + std::to_string(pageId) + " Content stream " + std::to_string(imageId);
            stream.objectNumber = nextON++;
            objectPtrs.push_back(&stream);
            stream.image = m_images.at(pageId).at(imageId);
            stream.imageId = imageId;
        }
    }

    std::vector<unsigned int> xRefOffsets;

    std::string s;
    s.append(header(m_version));


    for(const auto& oPtr: objectPtrs){
        xRefOffsets.push_back(s.length());
        s.append(oPtr->getObjectString());
    }

    unsigned int startXRef = s.length();
    unsigned int xRefSize = xRefOffsets.size()+1;

    s.append("xref\n");
    s.append("0 ");
    s.append(std::to_string(xRefSize));
    s.append("\n");
    s.append("0000000000 65535 f \n");
    for(auto& offset: xRefOffsets){
        std::string offsetNumber = std::to_string(offset);
        offsetNumber.insert(0,10 - offsetNumber.length(), '0');

        s.append(offsetNumber);
        s.append(" 00000 n \n");
    }
    s.append("\n");

    s.append("trailer\n");
    s.append("<<\n");
    s.append("  /Size ");
    s.append(std::to_string(xRefSize));
    s.append("\n");
    s.append("  /Root 1 0 R\n");
    s.append(">>\n");
    s.append("startxref\n");
    s.append(std::to_string(startXRef));
    s.append("\n");
    s.append("%%EOF");

    file << s;

    std::cout << "saved " << filename << std::endl;
    return true;
}
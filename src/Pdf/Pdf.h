#pragma once

#include <string>
#include <vector>

#include "Image.h"

namespace myPdf{

    class Pdf{
      
        public:
            Pdf();
            void addImage(const unsigned int imageId, const myPdf::Image& image);
            bool save(const std::string& filename) const;

        private:

            std::string m_version = "1.2";
            unsigned int m_numPages = 1;
            std::vector<std::vector<Image>> m_images;
    };

}
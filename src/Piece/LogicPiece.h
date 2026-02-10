#pragma once

#include <string>

namespace sigrid{

    class LogicPiece{

        public:

            LogicPiece(std::string notation, int colorId);
            int colorId() const;
            std::string notation() const;

            bool operator==(const LogicPiece& rhs) const;

        private:
            std::string m_notation;
            int m_colorId;
    };

}
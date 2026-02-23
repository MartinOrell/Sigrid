#pragma once

#include <string>

namespace sigrid{

    class Coord{

        public:

            Coord(const int x, const int y);
            Coord(const std::string& notation, const bool isLeftToRight, const bool isTopToBottom, const unsigned int numColumns, const unsigned int numRows);

            bool operator<(const Coord& rhs) const;
            bool operator==(const Coord& rhs) const;
            bool operator!=(const Coord& rhs) const;

            std::string getNotation(const bool isLeftToRight, const bool isTopToBottom, const unsigned int numColumns, const unsigned int numRows) const;

            int x;
            int y;

        private:
            

    };

}
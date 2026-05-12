#pragma once

#include <string>

namespace sigrid{

    namespace notation{
        std::string getColumnNotation(const int& x);
        std::string getRowNotation(const int& y);
    }

    struct Coord{
        Coord();
        Coord(const int x, const int y);
        Coord(const std::string& notation);

        Coord& operator=(const Coord& rhs);

        bool operator<(const Coord& rhs) const;
        bool operator==(const Coord& rhs) const;
        bool operator!=(const Coord& rhs) const;

        std::string getNotation() const;

        int x;
        int y;
    };

}
#pragma once

#include <string>
#include <istream>

namespace sigrid_coord{

struct Coord{
    Coord();
    Coord(const int x, const int y);
    Coord(const std::string& notation);

    Coord& operator=(const Coord& rhs);

    bool operator<(const Coord& rhs) const;
    bool operator==(const Coord& rhs) const;
    bool operator!=(const Coord& rhs) const;

    bool set(const std::string& notation);

    std::string getNotation() const;

    bool load(std::istream& is);

    int x;
    int y;
};

std::string getColumnNotation(const int& x);
std::string getRowNotation(const int& y);

}  // namespace sigrid_coord
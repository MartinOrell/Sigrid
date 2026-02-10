#pragma once

namespace sigrid{

    class Coord{

        public:

            Coord(int x, int y);

            bool operator<(const Coord& rhs) const;
            bool operator==(const Coord& rhs) const;
            bool operator!=(const Coord& rhs) const;

            int x;
            int y;

        private:
            

    };

}
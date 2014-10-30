#ifndef _POINT_BASE_H_
#define _POINT_BASE_H_

namespace Utilities {
    struct Point {
        int x;
        int y;

        /* Constructor/Destructor */
        Point() { x = 0;y = 0; }
        Point(int x, int y) { this->x = x; this->y = y; }
        ~Point() {}

        /* Overloaded Operators */
        bool operator==(const Point& rhs) {
            if(rhs.x == this->x && rhs.y == this->y) { 
                return true; 
            }
            return false;
        }
    };
}

#endif  //_POINT_BASE_H_

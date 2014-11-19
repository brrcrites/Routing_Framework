#ifndef _SEGMENT_GROUP_BASE_H_
#define _SEGMENT_GROUP_BASE_H_

#include "pathsegment.h"
#include <vector>

using std::vector;
using Utilities::Point;
using Utilities::PathSegment;

namespace Utilities {
    class SegmentGroup {
        private:
            vector<PathSegment*> segments;

            bool on_segment(Point p1, Point p2, Point p3);

        public:
            SegmentGroup();
            ~SegmentGroup();

            /* Accessors */
            unsigned size() const;
            PathSegment* at(unsigned index) const;
            bool empty() const;
            bool contains(const Point& point);
            int get_length();
            void print();

            /* Mutators */
            void add_segment(PathSegment* pathsegment);
            void add_segment(Point source, Point sink);
            void remove_segment(PathSegment* pathsegment);
            void remove_segment(Point soruce, Point sink);
            void remove_segment(int index);
    };
}

#endif //_PATH_SEGMENT_GROUP_BASE_H_
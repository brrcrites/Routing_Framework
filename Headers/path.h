#ifndef _PATH_BASE_H_
#define _PATH_BASE_H_

#include "segmentgroup.h"
#include <vector>

using std::vector;
using Utilities::Point;
using Utilities::PathSegment;

namespace Utilities {
    class Path: public SegmentGroup {
        private:
            Point source;
            Point sink;

        public:
            Path();
            ~Path();

            /* Accessors */
            Point get_source();
            Point get_sink();

            /* 
            == Inherited Accessors ==
            unsigned size() const;
            PathSegment* at(unsigned index) const;
            bool empty() const;
            bool contains(const Point& point);
            int get_length();
            void print();
            */

            /* Mutators */
            void set_source(Point source);
            void set_sink(Point sink);

            /*
            == Inherited Mutators ==
            void add_segment(PathSegment* pathsegment);
            void add_segment(Point source, Point sink);
            void remove_segment(PathSegment* pathsegment);
            void remove_segment(Point soruce, Point sink);
            void remove_segment(int index);
            */
    };
}

#endif //_PATH_BASE_H_

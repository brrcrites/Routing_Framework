#include "../Headers/segmentgroup.h"
#include "../Headers/claim.h"

#include <iostream>

using std::cout;
using std::endl;

bool Utilities::SegmentGroup::on_segment(Point p1,Point p2,Point p3) {
    if((p2.x <= std::max(p1.x,p3.x) && p2.x >= std::min(p1.x,p3.x)) &&
            (p2.y <= std::max(p1.y,p3.y) && p2.y >= std::min(p1.y,p3.y))) {
        return true;
    }
    return false;
}

Utilities::SegmentGroup::SegmentGroup() {
    /* Empty Constructor */
}

Utilities::SegmentGroup::~SegmentGroup() {
    while(!this->segments.empty()) {
        PathSegment* temp = this->segments.back();
        segments.pop_back();
        delete(temp);
    }
}

unsigned Utilities::SegmentGroup::size() const {
    return this->segments.size();
}

PathSegment* Utilities::SegmentGroup::at(unsigned index) const { 
    return this->segments.at(index); 
}

bool Utilities::SegmentGroup::empty() const {
    return this->segments.empty();
}

bool Utilities::SegmentGroup::contains(const Point& point) {
    for(unsigned i = 0; i < this->segments.size(); i++) {
        if(on_segment(segments.at(i)->get_source(),segments.at(i)->get_sink(),point)) {
            return true;
        }
    }
    return false;
}

int Utilities::SegmentGroup::get_length() {
    int total_length = 0;
    for(int i = 0; i < this->segments.size(); i++) {
        total_length += this->segments.at(i)->get_length();
    }
    return total_length;
}

void Utilities::SegmentGroup::print() {
    if(this->segments.size() <= 0) {
        return;
    }
    for(unsigned i = 0; i < this->segments.size(); i++) {
        this->segments.at(i)->print();
        if(i < this->segments.size() -1) {
            cout << " | ";
        }
    }
    cout << endl;
}

void Utilities::SegmentGroup::add_segment(PathSegment* pathsegment) {
    this->segments.push_back(pathsegment);
}

void Utilities::SegmentGroup::add_segment(Point source, Point sink) {
    this->segments.push_back(new PathSegment(source, sink));
}

/* Note: if the pathsegment appears multiple times in the path, all instances will be removed */
void Utilities::SegmentGroup::remove_segment(PathSegment* pathsegment) {
    for(vector<PathSegment*>::iterator it = this->segments.begin(); it != this->segments.end(); it++) {
        if((*it) == pathsegment) {
            this->segments.erase(it);
            if(it == this->segments.end()) { break; }
        }
    }
    delete pathsegment;
}

/* Note: if the pathsegment appears multiple times in the path, all instances will be removed */
void Utilities::SegmentGroup::remove_segment(Point source, Point sink) {
    PathSegment* to_delete;
    for(vector<PathSegment*>::iterator it = this->segments.begin(); it != this->segments.end(); it++) {
        if((*it)->get_source() == source && (*it)->get_sink() == sink) {
            to_delete = (*it);
            this->segments.erase(it);
            if(it == this->segments.end()) { break; }
        }
    }
    if(to_delete != NULL) { delete to_delete; }
}

void Utilities::SegmentGroup::remove_segment(int index) {
    if(index >= this->segments.size()) {
        claim("Attempting to remove segment with index out of range of the paths size", kError);
    }
    vector<PathSegment*>::iterator it = this->segments.begin();
    it += index;
    PathSegment* to_remove = *it;       //TODO: Double check that this *it is correct
    this->segments.erase(it);
    delete to_remove;
}

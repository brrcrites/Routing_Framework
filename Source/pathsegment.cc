#include "../Headers/pathsegment.h"
#include "../Headers/claim.h"

#include <iostream>

using std::cout;
using Utilities::Point;

void Utilities::PathSegment::update_length() {
    if(this->source.x == this->sink.x && this->source.y == this->sink.y) {
        claim("You have entered two equal points, PathSegment length is zero", kWarning);
        this->length = 0;
    }
    if(this->source.x == this->sink.x) {
        if(source.y > sink.y) {
            this->length = this->source.y - this->sink.y;
        } else {
            this->length = this->sink.y - this->source.y;
        }
    }
    else if(this->source.y == this->sink.y) {
        if(this->source.x > this->sink.x) {
            this->length = this->source.x - this->sink.x;
        } else {
            this->length = this->sink.x - this->source.x;
        }
    }
    else {
        claim("PathSegment being created does not represent a straight line segment", kError);
    }
}

Utilities::PathSegment::PathSegment(Point source, Point sink):
        source(source.x,source.y),sink(sink.x,sink.y) {
    update_length();
}

Utilities::PathSegment::PathSegment(int p1_x, int p1_y, int p2_x, int p2_y):
        source(p1_x,p1_y),sink(p2_x,p2_y) {
    update_length();
}

Utilities::PathSegment::~PathSegment() {
    /* Empty Destructor */
}

bool Utilities::PathSegment::operator==(const PathSegment& rhs) {
    if(this->source == rhs.source && this->sink == rhs.sink) {
        return true;
    }
    return false;
}

Point Utilities::PathSegment::get_source() {
    return this->source;
}

Point Utilities::PathSegment::get_sink() {
    return this->sink;
}

int Utilities::PathSegment::get_length() {
    return this->length;
}

bool Utilities::PathSegment::contains_points(Point source, Point sink) {
    if(source == this->source && sink == this->sink) {
        return true;
    }
    return false;
}

void Utilities::PathSegment::print_source() {
    cout << "(" << this->source.x << "," << this->source.y << ")";
}

void Utilities::PathSegment::print_sink() {
    cout << "(" << this->sink.x << "," << this->sink.y << ")";
}

void Utilities::PathSegment::print() {
    this->print_source();
    cout << " -> ";
    this->print_sink();
}

void Utilities::PathSegment::set_source(Point source) {
    this->source = source;
    update_length();
}

void Utilities::PathSegment::set_sink(Point sink) {
    this->sink = sink;
    update_length();
}


#include "../Headers/path.h"
#include "../Headers/claim.h"

Utilities::Path::Path() {
    /* Empty Constructor */
}

Utilities::Path::~Path() {
    /* Emptry Destructor */
}

Point Utilities::Path::get_source() {
    return this->source;
}

Point Utilities::Path::get_sink() {
    return this->sink;
}

void Utilities::Path::set_source(Point source) {
    this->source = source;
}

void Utilities::Path::set_sink(Point sink) {
    this->sink = sink;
}
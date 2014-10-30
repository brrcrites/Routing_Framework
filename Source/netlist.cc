#include "../Headers/netlist.h"

Utilities::Netlist::Netlist() {
    /* Empty Constructor */
}

Utilities::Netlist::~Netlist() {
    /* Emptry Destructor */
}

Point Utilities::Netlist::get_source() {
    return this->source;
}

vector<Point> Utilities::Netlist::get_sinks() {
    return this->sinks;
}

void Utilities::Netlist::set_source(Point source) {
    this->source = source;
}

void Utilities::Netlist::add_sink(Point sink) {
    this->sinks.push_back(sink);
}

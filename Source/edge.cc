#include "../Headers/edge.h"

using Utilities::Node;

Utilities::Edge::Edge(Node* head, Node* tail) {
    this->head = head;
    this->tail = tail;
}

Utilities::Edge::~Edge() {
	head = NULL;
	tail = NULL;
}

Node* Utilities::Edge::get_head() {
    return this->head;
}

Node* Utilities::Edge::get_tail() {
    return this->tail;
}

void Utilities::Edge::set_head(Node* head) {
    this->head = head;
}

void Utilities::Edge::set_tail(Node* tail) {
    this->tail = tail;
}

Node* Utilities::Edge::get_end(Node* start) {
    return (start == this->head) ? this->tail : this->head;
}

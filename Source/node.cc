#include "../Headers/edge.h"
#include "../Headers/node.h"
#include "../Headers/claim.h"

#include <iostream>

Utilities::Node::Node(int x, int y, int cost):coord(x,y){
      this->cost = cost;
}

Utilities::Node::Node(Point coord, int cost):coord(coord.x,coord.y){
      this->cost = cost;
}

Utilities::Node::~Node() {
      for(int i=0; i < connections.size(); i++) {
            Edge* edge_to_remove = this->connections.at(i);
            //Remove the edge from the node at the other end of the edge's connection list
			if (edge_to_remove) { 
				edge_to_remove->get_end(this)->remove_connection(edge_to_remove);
				//Remove the edge from the current object's connection list
				this->remove_connection(edge_to_remove);
				//Delete edge
				delete edge_to_remove;
			}
      }
}

Utilities::Point Utilities::Node::get_coord() {
      return this->coord;
}

int Utilities::Node::get_x() {
      return this->coord.x;
}

int Utilities::Node::get_y() {
      return this->coord.y;
}

unsigned Utilities::Node::connections_size() {
      return this->connections.size(); 
}

bool Utilities::Node::connections_empty() {
      return this->connections.empty();
}

bool Utilities::Node::connections_contains(Edge* edge) {
      for(int i = 0; i < this->connections.size(); i++) {
            if(this->connections.at(i) == edge) {
                  return true;
            }
      }
      return false;
}

Utilities::Edge* Utilities::Node::connections_at(unsigned index) {
      if(index >= connections.size()) {
            claim("Attemping to access connection outside of the connection list's range", kError);
      }
      return this->connections.at(index);          //at(...) will throw an out of range exception
}

int Utilities::Node::get_cost() {
      return this->cost;
}

void Utilities::Node::set_coord(int x, int y) {
      this->coord.x = x;
      this->coord.y = y;
}

void Utilities::Node::set_coord(Point coord) {
      this->coord = coord;
}

void Utilities::Node::set_x_coord(int x) {
      this->coord.x = x;
}

void Utilities::Node::set_y_coord(int y) {
      this->coord.y = y;
}

void Utilities::Node::set_connections(vector<Edge*> connections) {
      this->connections = connections;
}

void Utilities::Node::add_connection_mirrored(Edge* connection) {
      //TODO: Check the connections list first to make sure to not add duplicates
      this->connections.push_back(connection);
}

void Utilities::Node::add_connection(Edge* connection) {
      //TODO: Check the connections list first to make sure to not add duplicates
      this->connections.push_back(connection);
      connection->get_end(this)->add_connection_mirrored(connection);
}

void Utilities::Node::set_cost(int cost) {
      this->cost = cost;
}

//If an edge occurs multiple times in the connection list, all instances will be removed
void Utilities::Node::remove_connection(Edge* connection) {
      //std::cout << "Removing Connection: (" << connection->get_head()->get_x() << "," << connection->get_head()->get_y() << ") -> (" << connection->get_tail()->get_x() << "," << connection->get_tail()->get_y() << ")" << std::endl;
      bool nothing_removed = true;
	  vector<Edge*>::iterator connections_it = connections.begin();
      //for(int i = 0; i < this->connections.size(); i++) {
      for(/* connections_it */;connections_it != connections.end();connections_it++) {
            if((*connections_it) == connection) {
                  nothing_removed = false;
				  connections.erase(connections_it);
				  if (connections_it == connections.end()) { break; }
            }
      }
      if(nothing_removed) {
            //TODO: Add debug warning if it gets here without a delete
      }
}

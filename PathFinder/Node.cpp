#include "Node.h"
#include "tools.h"


Node::Node(QPoint position, float radius):
	id(lastId++),
	position(position),
	radius(radius)
{
}

Node::Node(IdType id):
	id(id),
	radius(6)
{
}

QVector<Branch> const & Node::connectedNodes() const {
	return connected;
}

void Node::connect(Node * other, float distance) {
	connected.push_back({other, distance});
}

void Node::connect(Node * other) {
	connected.push_back({other, ::distance(position, other->position)});
}

void Node::computeDistances() {
	for (auto& c : connected) {
		float d = ::distance(position, c.node->position);
		c.distance = d;
		for (auto& oc : c.node->connected)
			if (oc.node == this) {
				oc.distance = d; 
				break;
			}
	}		
}

IdType Node::lastId = 0;

#include "Graph.h"
#include <limits>
#include <qqueue.h>
#include "tools.h"
#include "Exception.h"

void Graph::initNodeDataTable(IdType srcId) const {
	size_t size = nodes.size();
	data.resize(size);
	for (size_t i = 0; i < size; ++i) {
		data[i].visited = false;
		data[i].distance = std::numeric_limits<float>::max();
		data[i].path.clear();
	}
	data[srcId].visited = true;
	data[srcId].distance = 0;
	data[srcId].path = {nodes[srcId]};
}

Graph::~Graph() {
	for (auto n : nodes)
		delete n;
}

void Graph::addNext(Node * n) {
	n->id = nodes.isEmpty() ? 0 : nodes.last()->id + 1;
	nodes.push_back(n);
}

void Graph::add(Node * n) {
	n->id = freeId();
	nodes.push_back(n);
}

bool Graph::contains(IdType id) const {
	for (auto n : nodes)
		if (n->id == id)
			return true;
	return false;
}

Node * Graph::get(IdType id) {
	if (id < nodes.size())
		return nodes[id];
	return nullptr;
}

Path Graph::shortestPath(IdType srcId, IdType destId) const {
	if (srcId == destId)
		return Path{nodes[srcId]};
	Node* src = nodes[srcId];
	Node* dest = nodes[destId];
	initNodeDataTable(srcId);
	QQueue<Node*> queue;
	queue.push_back(src);
	while (!queue.isEmpty()) {
		Node* n = queue.takeLast();
		NodeData& current = data[n->id];
		for (Branch const& nb : n->connected) {
			NodeData& neighbor = data[nb.node->id];
			float d = current.distance + nb.distance;
			if (d < neighbor.distance) {
				neighbor.distance = d;
				neighbor.path = current.path;
				neighbor.path.push_back(nb.node);
				queue.push_back(nb.node);
				neighbor.visited = true;
			}
			else if (!neighbor.visited && nb.node->id != destId) {
				queue.push_back(nb.node);
				neighbor.visited = true;
			}
		}
	}
	return data[destId].path;
}

Path Graph::shortestPath(QString const & src, QString const & dest) const {
	Node* nsrc = findByName(src);
	Node* ndest = findByName(dest);
	if (nsrc && ndest)
		return shortestPath(nsrc->id, ndest->id);
	else
		throw Exception("Could not find specified nodes");
}

QVector<Node*> const & Graph::allNodes() const {
	return nodes;
}

bool Graph::detected(Node * n, QPoint const & pos) {
	return (n->position - pos).manhattanLength() < n->radius;
}

void Graph::removeSelfConnections(Node * n) {
	for (auto& c : n->connected) {
		for (auto& nc : c.node->connected)
			if (nc.node == n) {
				nc = c.node->connected.last();
				c.node->connected.pop_back();
			}
	}
}

IdType Graph::freeId() const {
	IdType max = nodes.first()->id;
	for (Node* n : nodes) {
		if (n->id > max)
			max = n->id;
	}
	return max + 1;
}

bool Graph::removeAt(QPoint const & p) {
	for (Node*& n : nodes) {
		if (detected(n, p)) {
			removeSelfConnections(n);
			delete n;
			n = nodes.last();
			nodes.pop_back();
			return true;
		}		
	}
	return false;
}

Node * Graph::findAt(QPoint const & p) {
	for (Node* n : nodes) {
		if (detected(n, p)) 
			return n;
	}
	return nullptr;
}

Node * Graph::findByName(QString const & name) const {
	for (Node* n : nodes) {
		if (n->name == name)
			return n;
	}
	return nullptr;
}

void Graph::calculateDistances() {
	for (Node* n : nodes) {
		for (auto& c : n->connected) 
			c.distance = ::distance(n->position, c.node->position);
	}
}

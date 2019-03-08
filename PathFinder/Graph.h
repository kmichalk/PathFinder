#pragma once

#include "Path.h"

class Graph
{
	struct NodeData {
		bool visited;
		float distance;
		QVector<Node*> path;
	};

	mutable QVector<Node*> nodes;
	mutable QVector<NodeData> data;

	void initNodeDataTable(IdType srcId) const;
	static bool detected(Node * n, QPoint const & pos);
	void removeSelfConnections(Node* n);
	IdType freeId() const;

public:
	~Graph();
	void addNext(Node* n);
	void add(Node* n);
	bool contains(IdType id) const;
	Node* get(IdType id);
	Path shortestPath(IdType srcId, IdType destId) const;
	Path shortestPath(QString const& src, QString const& dest) const;
	QVector<Node*> const& allNodes() const;
	bool removeAt(QPoint const& p);
	Node* findAt(QPoint const& p);
	Node* findByName(QString const& name) const;
	void calculateDistances();
};


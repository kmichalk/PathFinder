#include "GraphSerializer.h"
#include "Graph.h"
#include <qfile.h>
#include <qtextstream.h>


void GraphSerializer::parseLine(QString const & line) {
	if (inputLineExpr.exactMatch(line)) {
		QString srcId = inputLineExpr.cap(1);
		Node* n = assertNode(srcId);
		n->position = parsePosition(inputLineExpr.cap(2), inputLineExpr.cap(3));
		parseNodeInfo(n, inputLineExpr.cap(4));
		QStringList destIdList = inputLineExpr.cap(5).split(';');
		parseDestinationNodesList(n, destIdList);
	}
	else
		throw Exception("Invalid expression: " + line);
}

void GraphSerializer::parseDestinationNodesList(Node* srcNode, QStringList const & destNodes) {
	for (QString const& ns : destNodes) {
		QString destName = ns.trimmed();
		if (destName.isEmpty())
			continue;
		Node* n = assertNode(destName);
		srcNode->connect(n, 0);
	}
}

void GraphSerializer::parseNodeInfo(Node * n, QString const & info) {
	n->name = info.trimmed();
}

Node* GraphSerializer::assertNode(QString const & sid) {
	if (!idMap.contains(sid)) {
		idMap[sid] = lastId;
		Node* n = new Node(lastId++);
		result->addNext(n);
		return n;
	}
	return result->get(idMap[sid]);
}

void GraphSerializer::reset() {
	idMap.clear();
	result = nullptr;
	lastId = 0;
}

QPoint GraphSerializer::parsePosition(QString const & sx, QString const & sy) {
	bool ok = false;
	QPoint result(sx.toInt(&ok), sy.toInt(&ok));
	if (!ok)
		throw Exception("Error in node position");
	return result;
}

GraphSerializer::GraphSerializer():
	result(nullptr),
	idMap(),
	lastId(0)
{
}


GraphSerializer::~GraphSerializer() {
}

Graph * GraphSerializer::readFile(QString const & filename) {
	reset();
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
		throw Exception("Error: cannot open file");
	result = new Graph;
	QTextStream in(&file);
	while (!in.atEnd()) 
		parseLine(in.readLine());
	file.close();
	result->calculateDistances();
	
	return result;
}

void GraphSerializer::writeFile(Graph * g, QString const& filename) {
	if (g == nullptr)
		throw Exception("Error: no data to write");
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
		return;
	QTextStream out(&file);
	for (Node* n : g->allNodes()) {
		out << n->id << " (" << n->position.x() << "," << n->position.y() << ") ";
		if (!n->name.isEmpty())
			out <<n->name << " ";
		out <<"-> ";
		auto& connected = n->connectedNodes();
		for (int i = 0; i < connected.size() - 1; ++i)
			out << connected[i].node->id << ";  ";
		if (!connected.empty())
			out << connected.last().node->id;
		out << endl;
	}
	file.close();
}

QRegExp GraphSerializer::inputLineExpr = QRegExp("(\\w+)\\s*\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\)([^-]*)\\s*->(.*)");
QRegExp GraphSerializer::destNodeExpr = QRegExp("\\s*(\\w+)\\s*:\\s*([0-9.]+)\\s*");
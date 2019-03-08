#pragma once

#include <qstring.h>
#include <qregexp.h>
#include <qmap.h>
#include "Node.h"
#include "Exception.h"


class Graph;
class AbstractValueInterpreter;

class GraphSerializer
{
	static QRegExp inputLineExpr;
	static QRegExp destNodeExpr;
	Graph* result;
	QMap<QString, IdType> idMap;
	IdType lastId;

	void parseLine(QString const& line);
	void parseDestinationNodesList(Node* srcNode, QStringList const& destNodes);
	void parseNodeInfo(Node* n, QString const& info);
	Node* assertNode(QString const& sid);
	void reset();
	QPoint parsePosition(QString const& sx, QString const& sy);

public:
	GraphSerializer();
	~GraphSerializer();
	Graph* readFile(QString const& filename);
	void writeFile(Graph* g, QString const& filename);
};


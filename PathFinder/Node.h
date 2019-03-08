#pragma once

#include <qvector.h>
#include <qvariant.h>


class Node;

struct Branch {
	Node* node;
	float distance;
};

using IdType = unsigned;

class Node
{
	friend class Graph;
	static IdType lastId;

protected:
	QVector<Branch> connected;
	QVariant value;

public:
	QPoint position;
	QString name;
	float radius;
	IdType id;

	Node(QPoint position, float radius = 6);
	Node(IdType id);

	QVector<Branch> const& connectedNodes() const;
	void connect(Node* other, float distance);
	void connect(Node* other);
	void computeDistances();


	template<class _Value>
	inline _Value getValue() const {
		return value.value<_Value>();
	}

	inline QVariant const& getAbstractValue() const {
		return value;
	}

	inline void setAbstractValue(QVariant const& v) {
		value = v;
	}

	inline QPoint pos() const {
		return position;
	}

	inline void setPosition(QPoint const& pos) {
		position = pos;
	}

	inline void move(QPoint const& p) {
		position += p;
	}
};


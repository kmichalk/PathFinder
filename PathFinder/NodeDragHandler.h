#pragma once

#include "qpoint.h"
#include <qobject.h>
#include <qcursor.h>

class Node;

class NodeDragHandler
{
	QPoint grabOffset;
	QPoint grabNodePos;
	QPoint grabMousePos;
	Qt::CursorShape prevShape;
	bool dragging;
	QPoint offset;
	Node* node;

public:
	NodeDragHandler();

	bool isDragging() const;
	void grab(Node* n);
	void release();
	void update();
	Node* getDraggedNode() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////

__inline bool NodeDragHandler::isDragging() const {
	return dragging;
}

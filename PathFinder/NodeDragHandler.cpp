#include "NodeDragHandler.h"
#include "MapView.h"
#include "Node.h"


NodeDragHandler::NodeDragHandler():
	grabOffset(0,0),
	grabMousePos(0,0),
	grabNodePos(0,0),
	prevShape(),
	dragging(false),
	node(nullptr)
{
}


void NodeDragHandler::grab(Node* n) {
	node = n;
	grabNodePos = n->pos();
	grabMousePos = QCursor::pos();
	dragging = true;
}

void NodeDragHandler::release() {
	dragging = false;
	node = nullptr;
}

void NodeDragHandler::update() {
	offset = QCursor::pos() - grabMousePos;
	if (node)
		node->setPosition(grabNodePos + offset);
}

Node * NodeDragHandler::getDraggedNode() const {
	return node;
}


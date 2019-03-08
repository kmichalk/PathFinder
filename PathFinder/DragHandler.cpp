#include "DragHandler.h"
#include "MapView.h"
#include "NodeDragHandler.h"



DragHandler::DragHandler(MapView* parent):
	parent(parent),
	grabOffset(0,0),
	grabMousePos(0,0),
	prevShape(),
	dragging(false),
	offset(0,0)
{
}

DragHandler::~DragHandler() {
}


void DragHandler::grab() {
	grabOffset = offset;
	grabMousePos = QCursor::pos();
	dragging = true;
}

void DragHandler::release() {
	dragging = false;
}

void DragHandler::update() {
	offset = grabOffset + QCursor::pos() - grabMousePos;
}


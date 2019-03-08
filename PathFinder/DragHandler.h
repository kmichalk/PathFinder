#pragma once

#include "qpoint.h"
#include <qobject.h>
#include <qcursor.h>

class MapView;

class DragHandler: public QObject
{
	Q_OBJECT;

	MapView* parent;
	QPoint grabOffset;
	QPoint grabMousePos;
	Qt::CursorShape prevShape;
	bool dragging;
	QPoint offset;

public:
	DragHandler(MapView* parent);
	//DragHandler();
	~DragHandler();

	bool isDragging() const;
	QPoint getOffset() const;
	void grab();
	void release();
	void update();
};

///////////////////////////////////////////////////////////////////////////////////////////////

__inline bool DragHandler::isDragging() const {
	return dragging;
}

///////////////////////////////////////////////////////////////////////////////////////////////

__inline QPoint DragHandler::getOffset() const {
	return offset;
}
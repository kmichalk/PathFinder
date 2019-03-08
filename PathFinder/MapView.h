#pragma once

#include "DragHandler.h"
#include "NodeDragHandler.h"
#include "ConnectHandler.h"
#include "Graph.h"
#include <qgraphicsview.h>


class MapView: public QGraphicsView
{
	Q_OBJECT;

	DragHandler dragHandler;
	NodeDragHandler nodeDragHandler;
	ConnectHandler connectHandler;
	Node* selectedNode;
	QPixmap* graphicsData;
	QPainter painter;
	QGraphicsScene scene;
	Graph* map;
	Path path;
	QPoint origin;
	float pointRadius;
	QPen pointPen;
	QPen pathPointPen;
	QPen connectLinePen;
	QPen linePen;
	QPen pathLinePen;
	QPen selectedNodePen;


	static bool leftButton(QMouseEvent* e);
	static bool rightButton(QMouseEvent* e);
	QLine generateLineToMouse(Node* src) const;

public:
	MapView(QWidget* parent = Q_NULLPTR);
	virtual ~MapView();

	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;
	void setMap(Graph* map);
	void setGraphics(QPixmap* pixmap);
	QPoint getOrigin() const;
	Node* getSelectedNode();
	void displayPath(Path const& path);
signals:
	void nodeSelected(Node*);
};


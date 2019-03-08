#include "MapView.h"
#include <qevent.h>
#include <iostream>


bool MapView::leftButton(QMouseEvent * e) {
	return e->button() == Qt::MouseButton::LeftButton;
}

bool MapView::rightButton(QMouseEvent * e) {
	return e->button() == Qt::MouseButton::RightButton;
}

QLine MapView::generateLineToMouse(Node * src) const {
	if (src)
		return QLine(src->pos() + dragHandler.getOffset(), mapFromGlobal(QCursor::pos()));
	else
		return QLine();
}

MapView::MapView(QWidget* parent):
	QGraphicsView(parent),
	dragHandler(this),
	selectedNode(nullptr),
	graphicsData(nullptr),
	map(nullptr),
	pointRadius(6),
	pointPen(QPen(QBrush(QColor(200, 50, 50)), pointRadius*2, Qt::PenStyle::SolidLine , Qt::PenCapStyle::RoundCap)),
	pathPointPen(QPen(QBrush(QColor(50, 50, 200)), pointRadius*2, Qt::PenStyle::SolidLine , Qt::PenCapStyle::RoundCap)),
	connectLinePen(QPen(QBrush(QColor(200, 50, 50)), 2, Qt::PenStyle::SolidLine , Qt::PenCapStyle::RoundCap)),
	linePen(QPen(QBrush(QColor(200, 50, 50)), 4, Qt::PenStyle::SolidLine , Qt::PenCapStyle::RoundCap)),
	pathLinePen(QPen(QBrush(QColor(50, 50, 200)), 4, Qt::PenStyle::SolidLine , Qt::PenCapStyle::RoundCap)),
	selectedNodePen(QPen(QBrush(QColor(100, 150, 0)), pointRadius*2, Qt::PenStyle::SolidLine , Qt::PenCapStyle::RoundCap))
{	
}


MapView::~MapView() {
}

void disp(QPoint p) {
	std::cout << p.x() << ", "<< p.y() << std::endl;
}

void disp(QPointF p) {
	std::cout << p.x() << ", "<< p.y() << std::endl;
}


void MapView::mousePressEvent(QMouseEvent * event) {
	if (map && graphicsData) {
		if (rightButton(event)) {
			if (Node* n = map->findAt(event->pos() - dragHandler.getOffset()))
				nodeDragHandler.grab(n);
		}
		else if (leftButton(event)) {
			if (event->modifiers() & Qt::KeyboardModifier::ControlModifier) {
				map->removeAt(event->pos() - dragHandler.getOffset());
				selectedNode = nullptr;
			}
			else
				if (Node* n = map->findAt(event->pos() - dragHandler.getOffset())) {
					selectedNode = n;
					connectHandler.grab(n);
				}
				else
					dragHandler.grab();
		}
		viewport()->update();
	}
	emit nodeSelected(selectedNode);
}

void MapView::mouseMoveEvent(QMouseEvent * event) {
	if (map && graphicsData) {
		if (nodeDragHandler.isDragging()) {
			nodeDragHandler.update();
			nodeDragHandler.getDraggedNode()->computeDistances();
			path.clear();
		}
		else if (!connectHandler.getSource() && dragHandler.isDragging())
			dragHandler.update();
		viewport()->update();
	}
}

void MapView::mouseReleaseEvent(QMouseEvent * event) {
	if (map && graphicsData) {
		if (leftButton(event)) {
			dragHandler.release();
			connectHandler.release(map->findAt(event->pos() - dragHandler.getOffset()));
		}
		if (rightButton(event)) {
			nodeDragHandler.release();
		}
		viewport()->update();
	}
}

void MapView::mouseDoubleClickEvent(QMouseEvent * event) {
	if (map && graphicsData) {
		if (!(event->modifiers() & Qt::KeyboardModifier::ControlModifier)) {
			if (leftButton(event)) {
				map->add(new Node(event->pos()-dragHandler.getOffset()));
				viewport()->update();
			}
		}
	}
}

void MapView::paintEvent(QPaintEvent * event) {
	painter.begin(viewport());
	QPoint offset = dragHandler.getOffset();
	if (graphicsData)
		painter.drawPixmap(offset, *graphicsData);
	if (map) {
		for (Node* n : map->allNodes()) {
			painter.setPen(n == selectedNode ? selectedNodePen : pointPen);
			painter.drawPoint(n->position + offset);
			painter.setPen(linePen);
			for (auto& c : n->connectedNodes())
				painter.drawLine(n->pos() + offset, c.node->position + offset);
		}
		if (connectHandler.getSource()) {
			painter.setPen(connectLinePen);
			painter.drawLine(generateLineToMouse(connectHandler.getSource()));
		}
	}
	if (!path.isEmpty()) {
		Node* prev = path.first();
		for (Node* n : path) {
			painter.setPen(pathPointPen);
			painter.drawPoint(n->position + offset);
			painter.setPen(pathLinePen);
			painter.drawLine(n->pos() + offset, prev->position + offset);
			prev = n;
		}
	}
	painter.end();
}

void MapView::setMap(Graph * map) {
	this->map = map;
}

void MapView::setGraphics(QPixmap * pixmap) {
	delete graphicsData;
	graphicsData = pixmap;
	viewport()->update();
}

QPoint MapView::getOrigin() const {
	return origin;
}

Node * MapView::getSelectedNode() {
	return selectedNode;
}

void MapView::displayPath(Path const & path) {
	this->path = path;
	viewport()->update();
}

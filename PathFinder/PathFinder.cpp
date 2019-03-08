#include "PathFinder.h"
#include "GraphSerializer.h"
#include <iostream>
#include <qfiledialog.h>

PathFinder::PathFinder(QWidget *parent):
	QMainWindow(parent),
	map(nullptr) {
	ui.setupUi(this);
	loadDirectory = QDir::currentPath() + "\\Resources";
	saveDirectory = QDir::currentPath() + "\\Resources";
	loadImage(".\\Resources\\mapka.jpg");
	loadMap(".\\Resources\\agh.txt");
	ui.mapView->viewport()->update();
}

PathFinder::~PathFinder() {
	delete map;
}

void PathFinder::connectSignals() {
	connect(ui.loadImageButton, &QPushButton::clicked,
			this, &PathFinder::on_loadImageButton_clicked);
	connect(ui.saveMapButton, &QPushButton::clicked,
			this, &PathFinder::on_saveMapButton_clicked);
	connect(ui.loadMapButton, &QPushButton::clicked,
			this, &PathFinder::on_loadMapButton_clicked);
	connect(ui.mapView, &MapView::nodeSelected,
			this, &PathFinder::on_mapView_nodeSelected);
	connect(ui.inputBox, &QLineEdit::textEdited,
			this, &PathFinder::on_inputBox_textEdited);
	connect(ui.computeButton, &QPushButton::clicked,
			this, &PathFinder::on_computeButton_clicked);
}

void PathFinder::loadMap(QString const & filename) {
	try {
		Graph* m = graphSerializer.readFile(filename);
		delete map;
		map = m;
		ui.mapView->setMap(m);
		ui.infoMessageBox->setText("ok");
	}
	catch (Exception e) {
		ui.infoMessageBox->setText(e.message);
	}
}

void PathFinder::loadImage(QString const & filename) {
	QPixmap* p = new QPixmap;
	p->load(filename);
	ui.mapView->setGraphics(p);
	if (map == nullptr)
		map = new Graph;
	ui.mapView->setMap(map);
}

void PathFinder::saveMap(QString const & filename) {
	try {
		graphSerializer.writeFile(map, filename);
		ui.infoMessageBox->setText("ok");
	}
	catch (Exception e) {
		ui.infoMessageBox->setText(e.message);
	}
}

void PathFinder::computeShortestPath(QString const & src, QString const & dest) {
	try {
		Path path = map->shortestPath(src.trimmed(), dest.trimmed());
		ui.mapView->displayPath(path);
		ui.infoMessageBox->setText(QString("Path length: ") + QString::number(pathLength(path)));
	}
	catch (Exception e) {
		ui.infoMessageBox->setText(e.message);
	}
}

float PathFinder::pathLength(Path const & p) const {
	float result = 0;
	Node* prev = p.first();
	for (Node* n : p) {
		result += ::distance(n->position, prev->position);
		prev = n;
	}
	return result;
}

void PathFinder::on_saveMapButton_clicked() {
	saveMap(QFileDialog::getSaveFileName(this,
										 tr("Save map"),
										 saveDirectory,
										 tr("Text files (*.txt);;All files (*)")));

}

void PathFinder::on_loadMapButton_clicked() {
	loadMap(QFileDialog::getOpenFileName(this,
										 tr("Load map"),
										 loadDirectory,
										 tr("Text files (*.txt);;All files (*)")));
}

void PathFinder::on_computeButton_clicked() {
	Node* n = ui.mapView->getSelectedNode();
	if (n == nullptr) {
		if (inputLineExpr.exactMatch(ui.inputBox->text()))
			computeShortestPath(inputLineExpr.cap(1), inputLineExpr.cap(2));
		else
			ui.infoMessageBox->setText("Invalid input expression for compute");
	}
	else {
		ui.infoMessageBox->setText("Deselect node to use compute button");
	}
}

void PathFinder::on_inputBox_textEdited(QString const & text) {
	if (Node* n = ui.mapView->getSelectedNode())
		n->name = text;
}

void PathFinder::on_mapView_nodeSelected(Node * n) {
	if (n != nullptr) {
		ui.inputBox->setText(n->name);
		ui.inputBox->setFocus();
		ui.infoMessageBox->setText(QString::number(n->id));
	}
	else {
		ui.inputBox->setText("");
	}
}

void PathFinder::on_loadImageButton_clicked() {
	loadImage(QFileDialog::getOpenFileName(this,
										   tr("Load image"),
										   loadDirectory,
										   tr("Image files (*.jpg);;All files (*)")));
}

QRegExp PathFinder::inputLineExpr = QRegExp("(.+)->(.+)");
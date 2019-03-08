#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PathFinder.h"
#include "GraphSerializer.h"

class PathFinder : public QMainWindow
{
	Q_OBJECT;

	GraphSerializer graphSerializer;
	Graph* map;
	QString loadDirectory;
	QString saveDirectory;
	static QRegExp inputLineExpr;

public:
	PathFinder(QWidget *parent = Q_NULLPTR);
	~PathFinder();

private:
	Ui::PathFinderClass ui;
	void connectSignals();
	void loadMap(QString const& filename);
	void loadImage(QString const& filename);
	void saveMap(QString const& filename);
	void computeShortestPath(QString const& src, QString const& dest);
	float pathLength(Path const& p) const;

public slots:
	void on_loadImageButton_clicked();
	void on_saveMapButton_clicked();
	void on_loadMapButton_clicked();
	void on_computeButton_clicked();
	void on_inputBox_textEdited(QString const& text);
	void on_mapView_nodeSelected(Node* n);
};

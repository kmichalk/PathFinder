/********************************************************************************
** Form generated from reading UI file 'PathFinder.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATHFINDER_H
#define UI_PATHFINDER_H

#include <MapView.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PathFinderClass
{
public:
    QWidget *centralWidget;
    QPushButton *loadImageButton;
    MapView *mapView;
    QPushButton *loadMapButton;
    QLabel *infoMessageBox;
    QPushButton *saveMapButton;
    QLineEdit *inputBox;
    QPushButton *computeButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PathFinderClass)
    {
        if (PathFinderClass->objectName().isEmpty())
            PathFinderClass->setObjectName(QStringLiteral("PathFinderClass"));
        PathFinderClass->setEnabled(true);
        PathFinderClass->resize(1117, 859);
        PathFinderClass->setStyleSheet(QStringLiteral("background-color: rgb(89, 89, 89);"));
        centralWidget = new QWidget(PathFinderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        loadImageButton = new QPushButton(centralWidget);
        loadImageButton->setObjectName(QStringLiteral("loadImageButton"));
        loadImageButton->setGeometry(QRect(400, 775, 96, 26));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(10);
        loadImageButton->setFont(font);
        loadImageButton->setStyleSheet(QStringLiteral("background-color: rgb(145, 145, 145);"));
        mapView = new MapView(centralWidget);
        mapView->setObjectName(QStringLiteral("mapView"));
        mapView->setGeometry(QRect(5, 5, 1106, 766));
        mapView->setStyleSheet(QStringLiteral("background-color: rgb(50, 50, 50);"));
        loadMapButton = new QPushButton(centralWidget);
        loadMapButton->setObjectName(QStringLiteral("loadMapButton"));
        loadMapButton->setGeometry(QRect(500, 775, 96, 26));
        loadMapButton->setFont(font);
        loadMapButton->setStyleSheet(QStringLiteral("background-color: rgb(145, 145, 145);"));
        infoMessageBox = new QLabel(centralWidget);
        infoMessageBox->setObjectName(QStringLiteral("infoMessageBox"));
        infoMessageBox->setGeometry(QRect(700, 775, 411, 26));
        infoMessageBox->setFont(font);
        infoMessageBox->setStyleSheet(QLatin1String("background-color: rgb(70, 70, 70);\n"
"color: rgb(190, 190, 190);"));
        saveMapButton = new QPushButton(centralWidget);
        saveMapButton->setObjectName(QStringLiteral("saveMapButton"));
        saveMapButton->setGeometry(QRect(600, 775, 96, 26));
        saveMapButton->setFont(font);
        saveMapButton->setStyleSheet(QStringLiteral("background-color: rgb(145, 145, 145);"));
        inputBox = new QLineEdit(centralWidget);
        inputBox->setObjectName(QStringLiteral("inputBox"));
        inputBox->setEnabled(true);
        inputBox->setGeometry(QRect(5, 775, 291, 26));
        inputBox->setStyleSheet(QLatin1String("QLineEdit{\n"
"	background-color:rgb(40,40,40);\n"
"	color: rgb(190, 190, 190);\n"
"	border: 1px solid rgb(120,120,120);\n"
"}\n"
"QLineEdit:disabled{\n"
"	background-color:rgb(90,90,90);\n"
"	color: rgb(190, 190, 190);\n"
"	border: 1px solid rgb(120,120,120);\n"
"}\n"
"\n"
"\n"
""));
        computeButton = new QPushButton(centralWidget);
        computeButton->setObjectName(QStringLiteral("computeButton"));
        computeButton->setGeometry(QRect(300, 775, 96, 26));
        computeButton->setFont(font);
        computeButton->setStyleSheet(QStringLiteral("background-color: rgb(145, 145, 145);"));
        PathFinderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PathFinderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1117, 21));
        PathFinderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PathFinderClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PathFinderClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PathFinderClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PathFinderClass->setStatusBar(statusBar);

        retranslateUi(PathFinderClass);

        QMetaObject::connectSlotsByName(PathFinderClass);
    } // setupUi

    void retranslateUi(QMainWindow *PathFinderClass)
    {
        PathFinderClass->setWindowTitle(QApplication::translate("PathFinderClass", "PathFinder", Q_NULLPTR));
        loadImageButton->setText(QApplication::translate("PathFinderClass", "load image", Q_NULLPTR));
        loadMapButton->setText(QApplication::translate("PathFinderClass", "load map", Q_NULLPTR));
        infoMessageBox->setText(QString());
        saveMapButton->setText(QApplication::translate("PathFinderClass", "save map", Q_NULLPTR));
        computeButton->setText(QApplication::translate("PathFinderClass", "compute", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PathFinderClass: public Ui_PathFinderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATHFINDER_H

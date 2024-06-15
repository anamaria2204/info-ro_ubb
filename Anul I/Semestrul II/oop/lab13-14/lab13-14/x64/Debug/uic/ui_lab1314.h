/********************************************************************************
** Form generated from reading UI file 'lab1314.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB1314_H
#define UI_LAB1314_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab1314Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lab1314Class)
    {
        if (lab1314Class->objectName().isEmpty())
            lab1314Class->setObjectName("lab1314Class");
        lab1314Class->resize(600, 400);
        menuBar = new QMenuBar(lab1314Class);
        menuBar->setObjectName("menuBar");
        lab1314Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lab1314Class);
        mainToolBar->setObjectName("mainToolBar");
        lab1314Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(lab1314Class);
        centralWidget->setObjectName("centralWidget");
        lab1314Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lab1314Class);
        statusBar->setObjectName("statusBar");
        lab1314Class->setStatusBar(statusBar);

        retranslateUi(lab1314Class);

        QMetaObject::connectSlotsByName(lab1314Class);
    } // setupUi

    void retranslateUi(QMainWindow *lab1314Class)
    {
        lab1314Class->setWindowTitle(QCoreApplication::translate("lab1314Class", "lab1314", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab1314Class: public Ui_lab1314Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB1314_H

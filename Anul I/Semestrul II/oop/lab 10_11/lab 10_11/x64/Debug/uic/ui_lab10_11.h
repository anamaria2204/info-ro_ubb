/********************************************************************************
** Form generated from reading UI file 'lab10_11.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB10_11_H
#define UI_LAB10_11_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab10_11Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lab10_11Class)
    {
        if (lab10_11Class->objectName().isEmpty())
            lab10_11Class->setObjectName("lab10_11Class");
        lab10_11Class->resize(600, 400);
        menuBar = new QMenuBar(lab10_11Class);
        menuBar->setObjectName("menuBar");
        lab10_11Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lab10_11Class);
        mainToolBar->setObjectName("mainToolBar");
        lab10_11Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(lab10_11Class);
        centralWidget->setObjectName("centralWidget");
        lab10_11Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lab10_11Class);
        statusBar->setObjectName("statusBar");
        lab10_11Class->setStatusBar(statusBar);

        retranslateUi(lab10_11Class);

        QMetaObject::connectSlotsByName(lab10_11Class);
    } // setupUi

    void retranslateUi(QMainWindow *lab10_11Class)
    {
        lab10_11Class->setWindowTitle(QCoreApplication::translate("lab10_11Class", "lab10_11", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab10_11Class: public Ui_lab10_11Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB10_11_H

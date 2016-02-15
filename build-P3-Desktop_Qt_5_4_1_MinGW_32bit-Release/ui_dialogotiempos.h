/********************************************************************************
** Form generated from reading UI file 'dialogotiempos.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOTIEMPOS_H
#define UI_DIALOGOTIEMPOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_DialogoTiempos
{
public:
    QGridLayout *gridLayout;
    QTableView *tableViewTiempos;

    void setupUi(QDialog *DialogoTiempos)
    {
        if (DialogoTiempos->objectName().isEmpty())
            DialogoTiempos->setObjectName(QStringLiteral("DialogoTiempos"));
        DialogoTiempos->setWindowModality(Qt::ApplicationModal);
        DialogoTiempos->resize(916, 315);
        DialogoTiempos->setModal(true);
        gridLayout = new QGridLayout(DialogoTiempos);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableViewTiempos = new QTableView(DialogoTiempos);
        tableViewTiempos->setObjectName(QStringLiteral("tableViewTiempos"));

        gridLayout->addWidget(tableViewTiempos, 0, 0, 1, 1);


        retranslateUi(DialogoTiempos);

        QMetaObject::connectSlotsByName(DialogoTiempos);
    } // setupUi

    void retranslateUi(QDialog *DialogoTiempos)
    {
        DialogoTiempos->setWindowTitle(QApplication::translate("DialogoTiempos", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogoTiempos: public Ui_DialogoTiempos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOTIEMPOS_H

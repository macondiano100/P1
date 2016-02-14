/********************************************************************************
** Form generated from reading UI file 'dialogosimulacion.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOSIMULACION_H
#define UI_DIALOGOSIMULACION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Visual/clock.h"

QT_BEGIN_NAMESPACE

class Ui_DialogoSimulacion
{
public:
    QGridLayout *gridLayout;
    QLabel *label_6;
    QListView *listaLoteActual;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_proceso_actual;
    QLabel *label_5;
    QLabel *label;
    QLabel *labelNuevos;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    Clock *clock;
    QSpacerItem *horizontalSpacer;
    QListView *listaProcesosBloqueados;
    QListView *listaProcesosTerminados;

    void setupUi(QDialog *DialogoSimulacion)
    {
        if (DialogoSimulacion->objectName().isEmpty())
            DialogoSimulacion->setObjectName(QStringLiteral("DialogoSimulacion"));
        DialogoSimulacion->setWindowModality(Qt::ApplicationModal);
        DialogoSimulacion->resize(617, 480);
        DialogoSimulacion->setFocusPolicy(Qt::StrongFocus);
        gridLayout = new QGridLayout(DialogoSimulacion);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(DialogoSimulacion);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setStyleSheet(QStringLiteral("font-weight:bold;"));

        gridLayout->addWidget(label_6, 7, 1, 1, 1);

        listaLoteActual = new QListView(DialogoSimulacion);
        listaLoteActual->setObjectName(QStringLiteral("listaLoteActual"));
        listaLoteActual->setFocusPolicy(Qt::NoFocus);
        listaLoteActual->setTextElideMode(Qt::ElideNone);
        listaLoteActual->setWordWrap(true);

        gridLayout->addWidget(listaLoteActual, 4, 1, 3, 2);

        label_2 = new QLabel(DialogoSimulacion);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("font-weight: bold"));

        gridLayout->addWidget(label_2, 4, 3, 1, 1);

        label_3 = new QLabel(DialogoSimulacion);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("font-weight: bold"));

        gridLayout->addWidget(label_3, 3, 1, 1, 2);

        label_proceso_actual = new QLabel(DialogoSimulacion);
        label_proceso_actual->setObjectName(QStringLiteral("label_proceso_actual"));

        gridLayout->addWidget(label_proceso_actual, 5, 3, 1, 1);

        label_5 = new QLabel(DialogoSimulacion);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setStyleSheet(QStringLiteral("font-weight:bold"));

        gridLayout->addWidget(label_5, 3, 4, 1, 3);

        label = new QLabel(DialogoSimulacion);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("font-weight: bold"));
        label->setWordWrap(true);

        gridLayout->addWidget(label, 1, 1, 1, 1);

        labelNuevos = new QLabel(DialogoSimulacion);
        labelNuevos->setObjectName(QStringLiteral("labelNuevos"));

        gridLayout->addWidget(labelNuevos, 1, 2, 1, 1);

        widget = new QWidget(DialogoSimulacion);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        clock = new Clock(widget);
        clock->setObjectName(QStringLiteral("clock"));
        clock->setStyleSheet(QLatin1String("background-color:rgb(0, 0, 0);\n"
"font:  \"Agency FB\";\n"
"color:rgb(0, 255, 127);"));
        clock->setTextFormat(Qt::RichText);

        horizontalLayout->addWidget(clock);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addWidget(widget, 0, 0, 1, 7);

        listaProcesosBloqueados = new QListView(DialogoSimulacion);
        listaProcesosBloqueados->setObjectName(QStringLiteral("listaProcesosBloqueados"));
        listaProcesosBloqueados->setFocusPolicy(Qt::NoFocus);
        listaProcesosBloqueados->setTextElideMode(Qt::ElideNone);
        listaProcesosBloqueados->setWordWrap(true);

        gridLayout->addWidget(listaProcesosBloqueados, 8, 1, 1, 2);

        listaProcesosTerminados = new QListView(DialogoSimulacion);
        listaProcesosTerminados->setObjectName(QStringLiteral("listaProcesosTerminados"));
        listaProcesosTerminados->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(listaProcesosTerminados, 4, 4, 5, 2);


        retranslateUi(DialogoSimulacion);

        QMetaObject::connectSlotsByName(DialogoSimulacion);
    } // setupUi

    void retranslateUi(QDialog *DialogoSimulacion)
    {
        DialogoSimulacion->setWindowTitle(QApplication::translate("DialogoSimulacion", "Dialog", 0));
        label_6->setText(QApplication::translate("DialogoSimulacion", "Procesos Bloqueados", 0));
        label_2->setText(QApplication::translate("DialogoSimulacion", "Proceso En Ejecuci\303\263n", 0));
        label_3->setText(QApplication::translate("DialogoSimulacion", "Procesos Listos", 0));
        label_proceso_actual->setText(QApplication::translate("DialogoSimulacion", "TextLabel", 0));
        label_5->setText(QApplication::translate("DialogoSimulacion", "Procesos Terminados", 0));
        label->setText(QApplication::translate("DialogoSimulacion", "Procesos Nuevos", 0));
        labelNuevos->setText(QApplication::translate("DialogoSimulacion", "TextLabel", 0));
        label_4->setText(QApplication::translate("DialogoSimulacion", "Tiempo Actual", 0));
        clock->setText(QApplication::translate("DialogoSimulacion", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogoSimulacion: public Ui_DialogoSimulacion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOSIMULACION_H

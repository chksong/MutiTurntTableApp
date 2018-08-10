/********************************************************************************
** Form generated from reading UI file 'QDlgDevManager.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDLGDEVMANAGER_H
#define UI_QDLGDEVMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QDlgDevManager
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *PB_ADD;
    QPushButton *PB_DEL;
    QPushButton *PB_MODIF;
    QPushButton *PB_CANCLE;

    void setupUi(QDialog *QDlgDevManager)
    {
        if (QDlgDevManager->objectName().isEmpty())
            QDlgDevManager->setObjectName(QStringLiteral("QDlgDevManager"));
        QDlgDevManager->resize(592, 360);
        horizontalLayoutWidget = new QWidget(QDlgDevManager);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 571, 341));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tableView = new QTableView(horizontalLayoutWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setStyleSheet(QLatin1String("QHeaderView::section {\n"
"background-color: rgb(200, 200, 255);\n"
"}"));
        tableView->horizontalHeader()->setDefaultSectionSize(151);

        verticalLayout_2->addWidget(tableView);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        PB_ADD = new QPushButton(horizontalLayoutWidget);
        PB_ADD->setObjectName(QStringLiteral("PB_ADD"));

        verticalLayout->addWidget(PB_ADD);

        PB_DEL = new QPushButton(horizontalLayoutWidget);
        PB_DEL->setObjectName(QStringLiteral("PB_DEL"));

        verticalLayout->addWidget(PB_DEL);

        PB_MODIF = new QPushButton(horizontalLayoutWidget);
        PB_MODIF->setObjectName(QStringLiteral("PB_MODIF"));

        verticalLayout->addWidget(PB_MODIF);

        PB_CANCLE = new QPushButton(horizontalLayoutWidget);
        PB_CANCLE->setObjectName(QStringLiteral("PB_CANCLE"));

        verticalLayout->addWidget(PB_CANCLE);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QDlgDevManager);
        QObject::connect(PB_MODIF, SIGNAL(clicked()), QDlgDevManager, SLOT(bt_save_click()));
        QObject::connect(PB_CANCLE, SIGNAL(clicked()), QDlgDevManager, SLOT(bt_cancle_click()));
        QObject::connect(PB_ADD, SIGNAL(clicked()), QDlgDevManager, SLOT(bt_add_click()));
        QObject::connect(PB_DEL, SIGNAL(clicked()), QDlgDevManager, SLOT(bt_del_click()));

        QMetaObject::connectSlotsByName(QDlgDevManager);
    } // setupUi

    void retranslateUi(QDialog *QDlgDevManager)
    {
        QDlgDevManager->setWindowTitle(QApplication::translate("QDlgDevManager", "QDlgDevManager", Q_NULLPTR));
        PB_ADD->setText(QApplication::translate("QDlgDevManager", "\346\267\273\345\212\240", Q_NULLPTR));
        PB_DEL->setText(QApplication::translate("QDlgDevManager", "\345\210\240\351\231\244", Q_NULLPTR));
        PB_MODIF->setText(QApplication::translate("QDlgDevManager", "\346\217\220\344\272\244\344\277\256\346\224\271", Q_NULLPTR));
        PB_CANCLE->setText(QApplication::translate("QDlgDevManager", "\346\222\244\351\224\200\344\277\256\346\224\271", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QDlgDevManager: public Ui_QDlgDevManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDLGDEVMANAGER_H

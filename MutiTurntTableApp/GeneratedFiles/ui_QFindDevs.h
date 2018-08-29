/********************************************************************************
** Form generated from reading UI file 'QFindDevs.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFINDDEVS_H
#define UI_QFINDDEVS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QFindDevs
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_COM;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *PB_Find;
    QPushButton *PB_RENAME;
    QPushButton *PB_ADD;

    void setupUi(QDialog *QFindDevs)
    {
        if (QFindDevs->objectName().isEmpty())
            QFindDevs->setObjectName(QStringLiteral("QFindDevs"));
        QFindDevs->resize(469, 309);
        horizontalLayoutWidget = new QWidget(QFindDevs);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 10, 461, 291));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_COM = new QLineEdit(horizontalLayoutWidget);
        lineEdit_COM->setObjectName(QStringLiteral("lineEdit_COM"));

        horizontalLayout_2->addWidget(lineEdit_COM);


        verticalLayout_2->addLayout(horizontalLayout_2);

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
        PB_Find = new QPushButton(horizontalLayoutWidget);
        PB_Find->setObjectName(QStringLiteral("PB_Find"));

        verticalLayout->addWidget(PB_Find);

        PB_RENAME = new QPushButton(horizontalLayoutWidget);
        PB_RENAME->setObjectName(QStringLiteral("PB_RENAME"));

        verticalLayout->addWidget(PB_RENAME);

        PB_ADD = new QPushButton(horizontalLayoutWidget);
        PB_ADD->setObjectName(QStringLiteral("PB_ADD"));

        verticalLayout->addWidget(PB_ADD);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(QFindDevs);
        QObject::connect(PB_Find, SIGNAL(clicked()), QFindDevs, SLOT(clickFindDev()));
        QObject::connect(PB_RENAME, SIGNAL(clicked()), QFindDevs, SLOT(clickReName()));
        QObject::connect(PB_ADD, SIGNAL(clicked()), QFindDevs, SLOT(clickAddDev()));

        QMetaObject::connectSlotsByName(QFindDevs);
    } // setupUi

    void retranslateUi(QDialog *QFindDevs)
    {
        QFindDevs->setWindowTitle(QApplication::translate("QFindDevs", "QFindDevs", Q_NULLPTR));
        label->setText(QApplication::translate("QFindDevs", "\344\270\262\345\217\243\345\234\260\345\235\200", Q_NULLPTR));
        PB_Find->setText(QApplication::translate("QFindDevs", "\346\237\245\346\211\276", Q_NULLPTR));
        PB_RENAME->setText(QApplication::translate("QFindDevs", "\350\256\276\345\256\232\345\234\260\345\235\200", Q_NULLPTR));
        PB_ADD->setText(QApplication::translate("QFindDevs", "\346\267\273\345\212\240\345\210\260\347\256\241\347\220\206\347\263\273\347\273\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QFindDevs: public Ui_QFindDevs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFINDDEVS_H

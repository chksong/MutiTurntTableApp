/********************************************************************************
** Form generated from reading UI file 'QtRunModel.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTRUNMODEL_H
#define UI_QTRUNMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtRunModel
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *RB_Y_UP;
    QRadioButton *RB_Y_DOWN;
    QRadioButton *RB_Y_STOP;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *RB_X_SHUN;
    QRadioButton *RB_X_NIE;
    QRadioButton *RB_X_STOP;
    QPushButton *PB_Set_Save;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *PB_Set_Save_2;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *QtRunModel)
    {
        if (QtRunModel->objectName().isEmpty())
            QtRunModel->setObjectName(QStringLiteral("QtRunModel"));
        QtRunModel->resize(334, 192);
        groupBox = new QGroupBox(QtRunModel);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(170, 20, 140, 110));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 100, 80));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        RB_Y_UP = new QRadioButton(layoutWidget);
        buttonGroup = new QButtonGroup(QtRunModel);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(RB_Y_UP);
        RB_Y_UP->setObjectName(QStringLiteral("RB_Y_UP"));
        RB_Y_UP->setAutoExclusive(false);

        verticalLayout->addWidget(RB_Y_UP);

        RB_Y_DOWN = new QRadioButton(layoutWidget);
        buttonGroup->addButton(RB_Y_DOWN);
        RB_Y_DOWN->setObjectName(QStringLiteral("RB_Y_DOWN"));
        RB_Y_DOWN->setAutoExclusive(false);

        verticalLayout->addWidget(RB_Y_DOWN);

        RB_Y_STOP = new QRadioButton(layoutWidget);
        buttonGroup->addButton(RB_Y_STOP);
        RB_Y_STOP->setObjectName(QStringLiteral("RB_Y_STOP"));
        RB_Y_STOP->setAutoExclusive(false);

        verticalLayout->addWidget(RB_Y_STOP);

        groupBox_2 = new QGroupBox(QtRunModel);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 20, 130, 111));
        groupBox_2->setCheckable(false);
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 20, 100, 81));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        RB_X_SHUN = new QRadioButton(layoutWidget1);
        RB_X_SHUN->setObjectName(QStringLiteral("RB_X_SHUN"));

        verticalLayout_2->addWidget(RB_X_SHUN);

        RB_X_NIE = new QRadioButton(layoutWidget1);
        RB_X_NIE->setObjectName(QStringLiteral("RB_X_NIE"));

        verticalLayout_2->addWidget(RB_X_NIE);

        RB_X_STOP = new QRadioButton(layoutWidget1);
        RB_X_STOP->setObjectName(QStringLiteral("RB_X_STOP"));

        verticalLayout_2->addWidget(RB_X_STOP);

        PB_Set_Save = new QPushButton(QtRunModel);
        PB_Set_Save->setObjectName(QStringLiteral("PB_Set_Save"));
        PB_Set_Save->setGeometry(QRect(50, 150, 75, 23));
        pushButton_2 = new QPushButton(QtRunModel);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(200, 150, 75, 23));
        pushButton_3 = new QPushButton(QtRunModel);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(200, 150, 75, 23));
        PB_Set_Save_2 = new QPushButton(QtRunModel);
        PB_Set_Save_2->setObjectName(QStringLiteral("PB_Set_Save_2"));
        PB_Set_Save_2->setGeometry(QRect(50, 150, 75, 23));

        retranslateUi(QtRunModel);
        QObject::connect(pushButton_3, SIGNAL(clicked()), QtRunModel, SLOT(reject()));
        QObject::connect(PB_Set_Save_2, SIGNAL(clicked()), QtRunModel, SLOT(saveCfg()));

        QMetaObject::connectSlotsByName(QtRunModel);
    } // setupUi

    void retranslateUi(QDialog *QtRunModel)
    {
        QtRunModel->setWindowTitle(QApplication::translate("QtRunModel", "\346\227\245\351\225\234\347\232\204\350\277\220\345\212\250\346\250\241\345\274\217", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("QtRunModel", "\344\277\257\344\273\260\347\224\265\346\234\272\350\277\220\350\275\254\346\226\271\345\274\217", Q_NULLPTR));
        RB_Y_UP->setText(QApplication::translate("QtRunModel", "\344\277\257\344\273\260\345\220\221\344\270\212", Q_NULLPTR));
        RB_Y_DOWN->setText(QApplication::translate("QtRunModel", "\344\277\257\344\273\260\345\220\221\344\270\213", Q_NULLPTR));
        RB_Y_STOP->setText(QApplication::translate("QtRunModel", "\344\277\257\344\273\260\345\201\234\346\255\242", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("QtRunModel", "\346\260\264\345\271\263\347\224\265\346\234\272\350\277\220\350\275\254\346\226\271\345\274\217", Q_NULLPTR));
        RB_X_SHUN->setText(QApplication::translate("QtRunModel", "\351\241\272\346\227\266\351\222\210", Q_NULLPTR));
        RB_X_NIE->setText(QApplication::translate("QtRunModel", "\351\200\206\346\227\266\351\222\210", Q_NULLPTR));
        RB_X_STOP->setText(QApplication::translate("QtRunModel", "\344\277\257\344\273\260\345\201\234\346\255\242", Q_NULLPTR));
        PB_Set_Save->setText(QApplication::translate("QtRunModel", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("QtRunModel", "\345\217\226\346\266\210", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("QtRunModel", "\345\217\226\346\266\210", Q_NULLPTR));
        PB_Set_Save_2->setText(QApplication::translate("QtRunModel", "\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtRunModel: public Ui_QtRunModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTRUNMODEL_H

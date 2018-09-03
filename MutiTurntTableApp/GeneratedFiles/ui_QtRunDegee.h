/********************************************************************************
** Form generated from reading UI file 'QtRunDegee.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTRUNDEGEE_H
#define UI_QTRUNDEGEE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QtRunDegee
{
public:

    void setupUi(QDialog *QtRunDegee)
    {
        if (QtRunDegee->objectName().isEmpty())
            QtRunDegee->setObjectName(QStringLiteral("QtRunDegee"));
        QtRunDegee->resize(400, 300);

        retranslateUi(QtRunDegee);

        QMetaObject::connectSlotsByName(QtRunDegee);
    } // setupUi

    void retranslateUi(QDialog *QtRunDegee)
    {
        QtRunDegee->setWindowTitle(QApplication::translate("QtRunDegee", "QtRunDegee", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtRunDegee: public Ui_QtRunDegee {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTRUNDEGEE_H

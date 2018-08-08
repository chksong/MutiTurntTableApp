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
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QDlgDevManager
{
public:

    void setupUi(QDialog *QDlgDevManager)
    {
        if (QDlgDevManager->objectName().isEmpty())
            QDlgDevManager->setObjectName(QStringLiteral("QDlgDevManager"));
        QDlgDevManager->resize(400, 300);

        retranslateUi(QDlgDevManager);

        QMetaObject::connectSlotsByName(QDlgDevManager);
    } // setupUi

    void retranslateUi(QDialog *QDlgDevManager)
    {
        QDlgDevManager->setWindowTitle(QApplication::translate("QDlgDevManager", "QDlgDevManager", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QDlgDevManager: public Ui_QDlgDevManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDLGDEVMANAGER_H

#pragma once

#include <QDialog>
#include "ui_QDlgDevManager.h"

class QDlgDevManager : public QDialog
{
	Q_OBJECT

public:
	QDlgDevManager(QWidget *parent = Q_NULLPTR);
	~QDlgDevManager();

private:
	Ui::QDlgDevManager ui;
};

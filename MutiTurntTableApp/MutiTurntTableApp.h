#pragma once

#include <QtWidgets/QDialog>
#include "ui_MutiTurntTableApp.h"

class MutiTurntTableApp : public QDialog
{
	Q_OBJECT

public:
	MutiTurntTableApp(QWidget *parent = Q_NULLPTR);

public slots:
	void devManager();
	void viewLog();
signals:


private:
	void setMyUI();

private:
	Ui::MutiTurntTableAppClass ui;
};

#pragma once

#include <QtWidgets/QDialog>
#include "ui_MutiTurntTableApp.h"

class MutiTurntTableApp : public QDialog
{
	Q_OBJECT

public:
	MutiTurntTableApp(QWidget *parent = Q_NULLPTR);

private:
	Ui::MutiTurntTableAppClass ui;
};

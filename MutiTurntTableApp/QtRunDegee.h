#pragma once

#include <QDialog>
#include "ui_QtRunDegee.h"

class QtRunDegee : public QDialog
{
	Q_OBJECT

public:
	QtRunDegee(QWidget *parent = Q_NULLPTR);
	~QtRunDegee();

private:
	Ui::QtRunDegee ui;
};

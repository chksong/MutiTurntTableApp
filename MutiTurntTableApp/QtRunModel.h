#pragma once

#include <QDialog>
#include "ui_QtRunModel.h"

#include <QtViewItem.h>

class QtRunModel : public QDialog
{
	Q_OBJECT

public:
	QtRunModel(QWidget *parent = Q_NULLPTR);
	~QtRunModel();


public slots:
	void saveCfg();
private:
	Ui::QtRunModel ui;

	QtViewItem  *m_ParentItem;
};

#pragma once

#include <QDialog>
#include "ui_QFindDevs.h"
#include <QStandardItem>


#include <array>

#include "TurnTableCommunication.h"

class QFindDevs : public QDialog
{
	Q_OBJECT

public:
	QFindDevs(QWidget *parent = Q_NULLPTR);
	~QFindDevs();

public slots:
	void clickFindDev();
	void clickReName();
	void clickAddDev();

private:
	Ui::QFindDevs ui;
	QStandardItemModel *model;

	//���豸��ȡ�ĵ�ַ
	std::array<char, 4> devAddress;
	CTurnTableCommunication * m_dev;
};

#pragma once

#include <QtWidgets/QDialog>
#include "ui_MutiTurntTableApp.h"

class MutiTurntTableApp : public QDialog
{
	Q_OBJECT

public:
	MutiTurntTableApp(QWidget *parent = Q_NULLPTR);

protected slots :
	void devManager();
	void viewLog();

	//�������ӵ��豸����ʼ���׶���
	void findDev();
	

	// �ֶ��趨���ǵ�λ��
	void manSatellitePOS();
	// �����ϻ�ȡ����λ��
	void GetSatellitePOSFromNet();
	// ���ļ���ȡ��λ��
	void GetSatellitePOSFromFile();


protected slots:
	void actionOneSlot();
	void actionTwoSlot();
	void actionThreeSlot();
	
signals:


private:
	void setMyUI();

private:
	Ui::MutiTurntTableAppClass ui;
};

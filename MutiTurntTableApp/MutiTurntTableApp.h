#pragma once

#include <QtWidgets/QDialog>
#include "ui_MutiTurntTableApp.h"

#include <vector>
#include <tuple>
#include <memory>

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


	void addDevBySignal(std::tuple<QString, QString, QString>& msgData);
	void delDevBySignal(std::tuple<QString, QString, QString>& msgData);
	
signals:


private:
	void setMyUI();
	void LoadDataFromDB();

private:
	Ui::MutiTurntTableAppClass ui;


	using SmartQStringPtr = std::shared_ptr<QString>;
	std::vector <std::tuple<SmartQStringPtr, SmartQStringPtr, SmartQStringPtr>> m_arrayDev;
};

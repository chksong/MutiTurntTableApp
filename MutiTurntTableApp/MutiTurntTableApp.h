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

	//查找链接的设备，初始化阶段用
	void findDev();
	

	// 手动设定卫星的位置
	void manSatellitePOS();
	// 从网上获取卫星位置
	void GetSatellitePOSFromNet();
	// 从文件获取的位置
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

#include "QtViewItem.h"


#include <QAction>
#include <QDebug>

#include <QMessageBox>

#include "QtRunDegee.h"
#include "QtRunModel.h"



QtViewItem::QtViewItem(QObject *parent)
	: QPushButton(reinterpret_cast<QWidget *> (parent))
{


	QAction *actionSetModel = new QAction(this);
	QAction *actionRun = new QAction(this);
	QAction *actionThree = new QAction(this);

	actionSetModel->setText("运转方式");
	actionRun->setText("运转度数");

	actionThree->setText("ActionThree");
	setContextMenuPolicy(Qt::ActionsContextMenu);

	addAction(actionSetModel);
	connect(actionSetModel, &QAction::triggered, this, &QtViewItem::menuRunModel);
	addAction(actionRun);
	connect(actionRun, &QAction::triggered, this, &QtViewItem::menuRunDegree);
	addAction(actionThree);




	// 暂时配置每个
	m_X_Model = 0;
	m_Y_Model = 0;


	m_devCommunication = new CTurnTableCommunication(this);
	
}

QtViewItem::~QtViewItem()
{


}


bool QtViewItem::setCfg(SmartQStringPtr strAddres, SmartQStringPtr strCOM, SmartQStringPtr strCamIP)
{
	m_strAddress = strAddres;
	m_strCamIP = strCamIP;
	m_strCOM = strCOM;


	QStringList addreslist = m_strAddress->split(" ");

	if (addreslist.count() != 4)
	{
		return false;
	}
	
	for (int addrSize = 0; addrSize < addreslist.size(); addrSize++)
	{
		bool retOK;
		unsigned int value = addreslist[addrSize].toInt(&retOK, 16);
		if (!retOK || value > 0xFF)
		{
			return false;
		}
		arrayAddress[addrSize] = value;
	}

	m_devCommunication->setAddress(arrayAddress);
	return true;
}


bool QtViewItem::start()
{
	return m_devCommunication->setAndOpenCOM(* (m_strCOM.get()) );
}


void QtViewItem::menuRunModel()
{
	QtRunModel *runModel = new QtRunModel(this);

	if (runModel->exec() == QDialog::Accepted)
	{
		// 调用串口发送 运动方式
		auto test = 1;
		m_devCommunication->setRunModle_xy(m_X_Model, m_Y_Model);
		return;
	}
	else {
		auto test3 = 2;
		return; 
	}

	


}


void QtViewItem::menuRunDegree()
{
	QtRunDegee *runDegee = new QtRunDegee(this);

	if (runDegee->exec() == QDialog::Accepted)
	{
		// 调用串口发送 运动方式
		auto test = 1;
	//	m_devCommunication->setRunDegree_xy();
		return;
	}
	else {
		auto test3 = 2;




		return;
	}


}
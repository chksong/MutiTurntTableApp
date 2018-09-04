#include "MutiTurntTableApp.h"

#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QLabel>

#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QAction>

#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <QSqlRecord>

#include "QDlgDevManager.h"
#include "QtViewItem.h"
#include "QFindDevs.h"


MutiTurntTableApp::MutiTurntTableApp(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;;
	setWindowFlags(flags);

	
	setWindowTitle(QStringLiteral("ת̨����"));
	
	//showFullScreen();

	LoadDataFromDB();
	setMyUI();  //�Լ����ò���
}

// �����ݿ����
void MutiTurntTableApp::LoadDataFromDB()
{
	m_arrayDev.clear();

	QSqlTableModel *modelQuery = new QSqlTableModel(this);
	modelQuery->setTable("tb_devs");
	modelQuery->select();
	for (int i = 0; i < modelQuery->rowCount(); ++i) {
		QSqlRecord record = modelQuery->record(i);
		QString name = record.value("name").toString();
		
		SmartQStringPtr ptrDev = std::make_shared<QString>(record.value("name").toString());
		SmartQStringPtr ptrCOM = std::make_shared<QString>(record.value("dev_ip").toString());
		SmartQStringPtr ptrCamIP = std::make_shared<QString>(record.value("camer_ip").toString());

		m_arrayDev.push_back(std::make_tuple(ptrDev, ptrCOM, ptrCamIP));
	}
}



// ���ñ��ز���
void MutiTurntTableApp::setMyUI()
{
	int ColNumSize = 6;
	int arraySize = m_arrayDev.size();
	// ��������ռ�
	QGridLayout *pLayout = new QGridLayout();
	//for (auto row  :{0 ,1,2,3,4 }) {
	//	for (auto col : { 0 ,1,2,3,4 ,5 }) {


	for (int row = 0; row <= arraySize / ColNumSize; ++row) {
		for (int col = 0 ; col < arraySize % ColNumSize; ++ col ) {
			auto index = row * ColNumSize + col;

			SmartQStringPtr ptrDev = std::get<0>(m_arrayDev[index]);
			SmartQStringPtr ptrCOM = std::get<1>(m_arrayDev[index]);
			SmartQStringPtr ptrCamIP = std::get<2>(m_arrayDev[index]);

			QtViewItem *curItem = new QtViewItem(this);
			curItem->setCfg(ptrDev, ptrCOM, ptrCamIP);
			curItem->start();
			
			curItem->setFixedSize(200, 200);
			pLayout->addWidget(curItem, row, col);
		}
	}

	// ����ˮƽ���
	pLayout->setHorizontalSpacing(3);
	// ���ô�ֱ���
	pLayout->setVerticalSpacing(3);
	// ��������
	pLayout->setContentsMargins(10, 10, 10, 10);
	pLayout->setGeometry(this->geometry());
	//setLayout(pLayout);



	// ����ҳ�沼�ִ���
	QWidget *container = new QWidget(this);
	container->setLayout(pLayout);

	// Put it into a scroll area
	QScrollArea *area = new QScrollArea(this);
	area->setWidget(container);

	// Make the scroll step the same width as the fixed widgets in the grid
	area->horizontalScrollBar()->setSingleStep(container->width() / 24);

	QVBoxLayout *layoutLevel_1 = new QVBoxLayout(this);
//	layout->addWidget(new QLabel("Something else", this));
	QMenuBar* pMenuBar = new QMenuBar(this);
	//QMenu* devsMenu = pMenuBar->addMenu(QString::fromLocal8Bit("�豸����"));
//	QAction* openAction = devsMenu->addAction("&Open", this, SLOT(slotOpen()), QKeySequence::Open);

	QMenu* menuSetting= pMenuBar->addMenu(QString::fromLocal8Bit("ϵͳ����"));
	//�������ǵ�λ��
	QMenu* menuSatellite = menuSetting->addMenu(QString::fromLocal8Bit("����λ��"));

	QAction *manualAction = new QAction(QString::fromLocal8Bit("�ֶ�����"), this);
	menuSatellite->addAction(manualAction);

	QAction *netAction = new QAction(QString::fromLocal8Bit("�����ȡ"), this);
	menuSatellite->addAction(netAction);

	QAction *formFileAction = new QAction(QString::fromLocal8Bit("�ļ���ȡ"), this);
	menuSatellite->addAction(formFileAction);


	QAction *devAction = new QAction(QString::fromLocal8Bit("ת̨����"), this);
	menuSetting->addAction(devAction);
	connect(devAction, &QAction::triggered, this, &MutiTurntTableApp::devManager);
	
	



	QAction *logAction = new QAction(QString::fromLocal8Bit("��־�鿴"), this);
	pMenuBar->addAction(logAction);
	connect(devAction, &QAction::triggered, this, &MutiTurntTableApp::viewLog);

	layoutLevel_1->addWidget(pMenuBar);
	layoutLevel_1->addWidget(area);

	// ״̬��
	QStatusBar *pStatuBar = new QStatusBar();
	QLabel *msgLabel = new QLabel(this);
	msgLabel->setStyleSheet(" QLabel{ color: red  ;}");
	msgLabel->setFixedWidth(200);
	msgLabel->setText("Ready :");
	pStatuBar->addWidget(msgLabel);

	QLabel *stateLabel2 = new QLabel(this);
	stateLabel2->setStyleSheet(" QLabel{ color: red }");
	stateLabel2->setText("4444 :");
	pStatuBar->addWidget(stateLabel2);
	layoutLevel_1->addWidget(pStatuBar);

	layoutLevel_1->setContentsMargins(3,0,3,3);
	setLayout(layoutLevel_1);
}



// �鿴��־
void MutiTurntTableApp::viewLog()
{



}




//���� ���ӵ��豸
void MutiTurntTableApp::findDev()
{
	QFindDevs *dlg = new QFindDevs(this);
	dlg->show();
}


//// �ֶ��趨���ǵ�λ��
void MutiTurntTableApp::manSatellitePOS()
{

}

// �����ϻ�ȡ����λ��
void MutiTurntTableApp::GetSatellitePOSFromNet()
{

}

// ���ļ���ȡ��λ��
void MutiTurntTableApp::GetSatellitePOSFromFile()
{


}

// ת̨�豸����
void MutiTurntTableApp::devManager()
{
	QDlgDevManager *dlgDev = new QDlgDevManager(this);
	connect(dlgDev, &QDlgDevManager::sigAddDevToUI, this, &MutiTurntTableApp::addDevBySignal);
	connect(dlgDev, &QDlgDevManager::sigDelDevToUI, this, &MutiTurntTableApp::delDevBySignal);
	dlgDev->show();
}




// �յ����� �豸������ ����豸����Ϣ
void MutiTurntTableApp::addDevBySignal(std::tuple<QString, QString, QString>& msgData)
{
	//
	//  ............
	// 


}

// // �յ����� �豸������ ɾ���豸����Ϣ
void MutiTurntTableApp::delDevBySignal(std::tuple<QString, QString, QString>& msgData)
{
	//
	//  ............




}


//


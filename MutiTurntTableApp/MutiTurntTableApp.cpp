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


#include "QDlgDevManager.h"

MutiTurntTableApp::MutiTurntTableApp(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint;;
	setWindowFlags(flags);

	setMyUI();  //�Լ����ò���
	setWindowTitle(QStringLiteral("ת̨����"));
	
	//showFullScreen();
}



// ���ñ��ز���
void MutiTurntTableApp::setMyUI()
{

	// ��������ռ�
	QGridLayout *pLayout = new QGridLayout();
	for (auto row  :{0 ,1,2,3,4 }) {
		for (auto col : { 0 ,1,2,3,4 ,5 }) {
			QPushButton *tmpButton = new QPushButton(this);
			tmpButton->setFixedSize(200, 200);
			pLayout->addWidget(tmpButton, row, col);
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

	QAction *devAction = new QAction(QString::fromLocal8Bit("ת̨����"), this);
	pMenuBar->addAction(devAction);
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


// ת̨�豸����
void MutiTurntTableApp::devManager()
{
	QDlgDevManager *dlgDev = new QDlgDevManager(this);
	dlgDev->show();
}
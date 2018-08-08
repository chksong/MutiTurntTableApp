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

	setMyUI();  //自己设置布局
	setWindowTitle(QStringLiteral("转台管理"));
	
	//showFullScreen();
}



// 设置本地布局
void MutiTurntTableApp::setMyUI()
{

	// 设置网格空间
	QGridLayout *pLayout = new QGridLayout();
	for (auto row  :{0 ,1,2,3,4 }) {
		for (auto col : { 0 ,1,2,3,4 ,5 }) {
			QPushButton *tmpButton = new QPushButton(this);
			tmpButton->setFixedSize(200, 200);
			pLayout->addWidget(tmpButton, row, col);
		}
	}

	// 设置水平间距
	pLayout->setHorizontalSpacing(3);
	// 设置垂直间距
	pLayout->setVerticalSpacing(3);
	// 设置外间距
	pLayout->setContentsMargins(10, 10, 10, 10);
	pLayout->setGeometry(this->geometry());
	//setLayout(pLayout);



	// 整个页面布局窗口
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
	//QMenu* devsMenu = pMenuBar->addMenu(QString::fromLocal8Bit("设备管理"));
//	QAction* openAction = devsMenu->addAction("&Open", this, SLOT(slotOpen()), QKeySequence::Open);

	QAction *devAction = new QAction(QString::fromLocal8Bit("转台管理"), this);
	pMenuBar->addAction(devAction);
	connect(devAction, &QAction::triggered, this, &MutiTurntTableApp::devManager);

	QAction *logAction = new QAction(QString::fromLocal8Bit("日志查看"), this);
	pMenuBar->addAction(logAction);
	connect(devAction, &QAction::triggered, this, &MutiTurntTableApp::viewLog);

	layoutLevel_1->addWidget(pMenuBar);
	layoutLevel_1->addWidget(area);

	// 状态栏
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



// 查看日志
void MutiTurntTableApp::viewLog()
{


}


// 转台设备管理
void MutiTurntTableApp::devManager()
{
	QDlgDevManager *dlgDev = new QDlgDevManager(this);
	dlgDev->show();
}
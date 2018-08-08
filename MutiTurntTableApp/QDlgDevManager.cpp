#include "QDlgDevManager.h"


//数据库密码 inhu!@#$%^001

QDlgDevManager::QDlgDevManager(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowTitle(QStringLiteral("转台设备配置管理"));
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
}

QDlgDevManager::~QDlgDevManager()
{


}


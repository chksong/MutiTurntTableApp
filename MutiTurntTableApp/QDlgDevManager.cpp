#include "QDlgDevManager.h"


//���ݿ����� inhu!@#$%^001

QDlgDevManager::QDlgDevManager(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowTitle(QStringLiteral("ת̨�豸���ù���"));
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);
}

QDlgDevManager::~QDlgDevManager()
{


}


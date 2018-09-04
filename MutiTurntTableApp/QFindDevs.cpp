#include "QFindDevs.h"

#include <QStandardItem>
#include <QMessageBox>
#include <TurnTableCommunication.h>


QFindDevs::QFindDevs(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	setWindowTitle(QString::fromLocal8Bit("添加链接串口的设备"));
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);


	model = new QStandardItemModel();
	model->setColumnCount(2);
	model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("设备地址"));
	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("协议版本"));

	/*ui.tableView->setColumnWidth(0, 250);
	ui.tableView->setColumnWidth(1, 250);*/

	ui.tableView->setModel(model);

	for (int i = 0; i < 1; i++)
	{
		model->setItem(i, 0, new QStandardItem("2009441676"));
		//设置字符颜色 
		model->item(i, 0)->setForeground(QBrush(QColor(255, 0, 0)));
		//设置字符位置 
		model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
		model->setItem(i, 1, new QStandardItem(QString::fromLocal8Bit("哈哈")));
	}

	m_dev = new CTurnTableCommunication(this);
}

QFindDevs::~QFindDevs()
{
	this->disconnect();
	 
}


//通过串口，读取链接到串口的设备号，读取设备的地址，以及协议版本
void QFindDevs::clickFindDev()
{
	model->removeRows(0, model->rowCount());

	// 1. 输入的串口号为空
	if (ui.lineEdit_COM->text().length() == 0)
	{
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("输入的串口是被为空"),
			QMessageBox::Yes);
		return;
	}

	// 2 打开串口设备，如果串口设备，提示错误
	// 3 读取串口设备的设备地址

	
	char version;
	/*
	auto ackData = m_dev->GetDevAddressSync(ui.lineEdit_COM->text(), devAddress, version);
	auto retOK = std::get<0>(ackData);
	if (! retOK) {
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("错误"), std::get<1>(ackData),
			QMessageBox::Yes);
		return;
	}
	*/

	/*** 以后需要注释 测试 ****/
	devAddress[0] = 0x11;
	devAddress[1] = 0x12;
	devAddress[2] = 0x13;
	devAddress[3] = 0x14;
	version = 0x11;
	/**/
	
	int addrow = model->rowCount();
	QString strAddress = QString("%1 %2 %3 %4").arg(devAddress[0], 2, 16, QChar('0'))
		.arg(devAddress[1], 2, 16, QChar('0')).arg(devAddress[2], 2, 16, QChar('0')).arg(devAddress[3], 2, 16, QChar('0'));

	model->setItem(addrow, 0, new QStandardItem(strAddress));
	//设置字符颜色 
	model->item(addrow, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	//设置字符位置 
	model->item(addrow, 0)->setTextAlignment(Qt::AlignCenter);
	model->setItem(addrow, 1, new QStandardItem(QString("%1").arg(version, 2, 16, QChar('0'))));

}



// 重命令的设备的地址
void QFindDevs::clickReName()
{
	if (model->rowCount() < 1 ) { 
		return;
	}
	

	int row = ui.tableView->currentIndex().row();
	//没有选择不能编辑
	if (row < 0 ) {
		if (model->rowCount()) {
			row = 0;
		}
		else {
			return;
		}
	}
	
	
	// 分析地址是否正确
	QModelIndex index = model->index(row, 0);
	QStringList addreslist = model->data(index).toString().split(" ");

	if (addreslist.count() != 4)
	{
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("设定的地址不正确"),
			QMessageBox::Yes);
		return;
	}
	std::array<char, 4> expectAddress;
	for (int addrSize = 0; addrSize < addreslist.size(); addrSize++)
	{
		bool retOK;
		unsigned int value = addreslist[addrSize].toInt(&retOK, 16);
		if ( !retOK ||  value > 0xFF)
		{
			int ok = QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("设定的地址不正确"),
				QMessageBox::Yes);
			return;
		}
		expectAddress[addrSize] = value;
	}
	

	// 设定设定地址
	// 1. 输入的串口号为空
	if (ui.lineEdit_COM->text().length() == 0)
	{
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("输入的串口是被为空"),
			QMessageBox::Yes);
		return;
	}
	
	auto ackData = m_dev->ResetDevAddressSync(ui.lineEdit_COM->text(), expectAddress);
	auto retOK = std::get<0>(ackData);
	if (false == retOK ) { // 设置失败

		//设置失败  还原为原来的数据
		QString strAddress = QString("%1 %2 %3 %4").arg(devAddress[0], 2, 16, QChar('0'))
			.arg(devAddress[1], 2, 16, QChar('0')).arg(devAddress[2], 2, 16, QChar('0')).arg(devAddress[3], 2, 16, QChar('0'));

		model->setItem(row, 0, new QStandardItem(strAddress));
	}
	else { // 设置成功
		devAddress = expectAddress;
	}
}


//讲串口设备，添加到系统中的数据库中。。
//可能需要什么办法，     通知后面的窗口。
void QFindDevs::clickAddDev()
{
	if (model->rowCount() < 1) {
		return;
	}

	int row = ui.tableView->currentIndex().row();
	//没有选择不能编辑
	if (row < 0) {
		if (model->rowCount()) {
			row = 0;
		}
		else {
			return;
		}
	}

	// 分析地址是否正确
	QModelIndex index = model->index(row, 0);
	QString  strAddress = model->data(index).toString();
	QStringList addreslist = model->data(index).toString().split(" ");
	if (addreslist.count() != 4)
	{
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("设定的地址不正确"),
			QMessageBox::Yes);
		return;
	}
	std::array<char, 4> expectAddress;
	for (int addrSize = 0; addrSize < addreslist.size(); addrSize++)
	{
		bool retOK;
		unsigned int value = addreslist[addrSize].toInt(&retOK, 16);
		if (!retOK || value > 0xFF)
		{
			int ok = QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("设定的地址不正确"),
				QMessageBox::Yes);
			return;
		}
		expectAddress[addrSize] = value;
	}


	emit signalAddDev(std::make_tuple(strAddress, ui.lineEdit_COM->text(), QString("")));

	//close();
}

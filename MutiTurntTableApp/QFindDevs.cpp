#include "QFindDevs.h"

#include <QStandardItem>
#include <QMessageBox>
#include <TurnTableCommunication.h>


QFindDevs::QFindDevs(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	setWindowTitle(QString::fromLocal8Bit("������Ӵ��ڵ��豸"));
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);


	model = new QStandardItemModel();
	model->setColumnCount(2);
	model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("�豸��ַ"));
	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("Э��汾"));

	/*ui.tableView->setColumnWidth(0, 250);
	ui.tableView->setColumnWidth(1, 250);*/

	ui.tableView->setModel(model);

	for (int i = 0; i < 1; i++)
	{
		model->setItem(i, 0, new QStandardItem("2009441676"));
		//�����ַ���ɫ 
		model->item(i, 0)->setForeground(QBrush(QColor(255, 0, 0)));
		//�����ַ�λ�� 
		model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
		model->setItem(i, 1, new QStandardItem(QString::fromLocal8Bit("����")));
	}

	m_dev = new CTurnTableCommunication(this);
}

QFindDevs::~QFindDevs()
{
	
	 
}


//ͨ�����ڣ���ȡ���ӵ����ڵ��豸�ţ���ȡ�豸�ĵ�ַ���Լ�Э��汾
void QFindDevs::clickFindDev()
{
	model->removeRows(0, model->rowCount());

	// 1. ����Ĵ��ں�Ϊ��
	if (ui.lineEdit_COM->text().length() == 0)
	{
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����Ĵ����Ǳ�Ϊ��"),
			QMessageBox::Yes);
		return;
	}

	// 2 �򿪴����豸����������豸����ʾ����
	// 3 ��ȡ�����豸���豸��ַ

	
	char version;
	/*
	auto ackData = m_dev->GetDevAddressSync(ui.lineEdit_COM->text(), devAddress, version);
	auto retOK = std::get<0>(ackData);
	if (! retOK) {
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("����"), std::get<1>(ackData),
			QMessageBox::Yes);
		return;
	}
	*/

	/*** �Ժ���Ҫע�� ���� ****/
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
	//�����ַ���ɫ 
	model->item(addrow, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	//�����ַ�λ�� 
	model->item(addrow, 0)->setTextAlignment(Qt::AlignCenter);
	model->setItem(addrow, 1, new QStandardItem(QString("%1").arg(version, 2, 16, QChar('0'))));

}


//�������豸����ӵ�ϵͳ�е����ݿ��С���
//������Ҫʲô�취��     ֪ͨ����Ĵ��ڡ�
void QFindDevs::clickAddDev()
{

}




// ��������豸�ĵ�ַ
void QFindDevs::clickReName()
{
	if (model->rowCount() < 1 ) { 
		return;
	}
	

	int row = ui.tableView->currentIndex().row();
	//û��ѡ���ܱ༭
	if (row < 0 ) {
		if (model->rowCount()) {
			row = 0;
		}
		else {
			return;
		}
	}
	
	
	// ������ַ�Ƿ���ȷ
	QModelIndex index = model->index(row, 0);
	QStringList addreslist = model->data(index).toString().split(" ");

	if (addreslist.count() != 4)
	{
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�趨�ĵ�ַ����ȷ"),
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
			int ok = QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�趨�ĵ�ַ����ȷ"),
				QMessageBox::Yes);
			return;
		}
		expectAddress[addrSize] = value;
	}
	

	// �趨�趨��ַ


	// 1. ����Ĵ��ں�Ϊ��
	if (ui.lineEdit_COM->text().length() == 0)
	{
		int ok = QMessageBox::critical(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����Ĵ����Ǳ�Ϊ��"),
			QMessageBox::Yes);
		return;
	}
	
	auto ackData = m_dev->ResetDevAddressSync(ui.lineEdit_COM->text(), expectAddress);
	auto retOK = std::get<0>(ackData);
	if (false == retOK ) { // ����ʧ��

		//����ʧ��  ��ԭΪԭ��������
		QString strAddress = QString("%1 %2 %3 %4").arg(devAddress[0], 2, 16, QChar('0'))
			.arg(devAddress[1], 2, 16, QChar('0')).arg(devAddress[2], 2, 16, QChar('0')).arg(devAddress[3], 2, 16, QChar('0'));

		model->setItem(row, 0, new QStandardItem(strAddress));
	}
	else { // ���óɹ�
		devAddress = expectAddress;
	}
}
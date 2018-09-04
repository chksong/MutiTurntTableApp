#include "QDlgDevManager.h"


#include <QMessageBox>
#include <QSqlError>
#include "QFindDevs.h"

//���ݿ����� inhu!@#$%^001

QDlgDevManager::QDlgDevManager(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowTitle(QStringLiteral("ת̨�豸���ù���"));
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);



	model = new QSqlTableModel(this);
	model->setTable("tb_devs");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);


	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("�豸��ַ"));
	model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("���ں�"));
	model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("�����IP"));
	model->select(); //ѡȡ�������������


	ui.tableView->setModel(model);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //ʹ�䲻�ɱ༭
	ui.tableView->setColumnHidden(0, true);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


//���������QTableView��ʹ���Ҽ��˵��������ø�����        
//	ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	
}

QDlgDevManager::~QDlgDevManager()
{
	this->disconnect();
}



// �޸����ݵı���
void QDlgDevManager::bt_save_click()
{
	model->database().transaction(); //��ʼ�������
	if (model->submitAll()) {
		model->database().commit(); //�ύ
	}
	else {
		model->database().rollback(); //�ع�
		QMessageBox::warning(this, tr("tableModel"),
			tr("���ݿ����: %1")
			.arg(model->lastError().text()));
	}
}

// �޸����ݳ���
void QDlgDevManager::bt_cancle_click()
{
	model->revertAll();
	
}


void QDlgDevManager::bt_add_click()
{
	/*
	**  ����豸
	int rowNum = model->rowCount(); //��ñ������
	model->insertRow(rowNum); //���һ��
	QString strDev = QString::fromLocal8Bit("���豸 %1").arg(rowNum);
	model->setData(model->index(rowNum, 1), strDev);
	*/

	QFindDevs *dlg = new QFindDevs(this);
	connect(dlg, &QFindDevs::signalAddDev, this, &QDlgDevManager::AddDevBySignal);
	dlg->show();
}


void QDlgDevManager::bt_del_click()
{
	//��ȡѡ�е���
	int curRow = ui.tableView->currentIndex().row();

	 
	QString devAddress = model->data( model->index(curRow, 1)).toString();
	QString devCOM = model->data(model->index(curRow, 2)).toString();


	//ɾ������
	model->removeRow(curRow);
	int ok = QMessageBox::warning(this, QString::fromLocal8Bit("ɾ����ǰ��!"), QString::fromLocal8Bit("��ȷ��"
		"ɾ����ǰ����"),
		QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		model->revertAll(); //�����ɾ��������
		return;
	}
	else 
		model->submitAll(); //�����ύ�������ݿ���ɾ������  

	emit sigAddDevToUI(std::make_tuple(devAddress, devCOM, QString("")));
}



void QDlgDevManager::bt_edit_click()
{
// 	int curRow = ui.tableView->currentIndex().row();
// 	int curCol = ui.tableView->currentIndex().column();
// 	//(const QModelIndex &index, const QVariant &value
// 	QModelIndex  index = ui.tableView->currentIndex();
// 	ui.tableView->cur



}

void QDlgDevManager::AddDevBySignal(std::tuple<QString, QString, QString> & msgData)
{
	QString strDev = std::get<0>(msgData);
	QString strCOM = std::get<1>(msgData);
	QString CarmIP = std::get<2>(msgData);

	QSqlTableModel *modelQuery = new QSqlTableModel(this);
	modelQuery->setTable("tb_devs");
	auto strSql = QString("name = '%1' and dev_ip = '%2'").arg(strDev).arg(strCOM);
	//auto strSql = QString("name = '%1'").arg(strDev)  ;
	modelQuery->setFilter(strSql);
	modelQuery->select();
	auto curRows = modelQuery->rowCount();
	if (curRows) {
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit(
			"�ظ����"),
			QMessageBox::Ok);
		return;
	}

	//����豸
	int rowNum = model->rowCount(); //��ñ������
	model->insertRow(rowNum); //���һ��
	model->setData(model->index(rowNum, 1), strDev);
	model->setData(model->index(rowNum, 2), strCOM);
	model->setData(model->index(rowNum, 3), CarmIP);
	model->submitAll();

	emit sigAddDevToUI(std::make_tuple(strDev,  strCOM , CarmIP));
}
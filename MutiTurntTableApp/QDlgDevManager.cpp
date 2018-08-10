#include "QDlgDevManager.h"


#include <QMessageBox>
#include <QSqlError>

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


	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("����"));
	model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("�豸IP"));
	model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("�����IP"));
	model->select(); //ѡȡ�������������


	ui.tableView->setModel(model);
	ui.tableView->setEditTriggers(QAbstractItemView::DoubleClicked); //ʹ�䲻�ɱ༭
	ui.tableView->setColumnHidden(0, true);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


//���������QTableView��ʹ���Ҽ��˵��������ø�����        
	ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	
}

QDlgDevManager::~QDlgDevManager()
{


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
	int rowNum = model->rowCount(); //��ñ������
	model->insertRow(rowNum); //���һ��
	QString strDev = QString::fromLocal8Bit("���豸 %1").arg(rowNum);
	model->setData(model->index(rowNum, 1), strDev);

}


void QDlgDevManager::bt_del_click()
{
	//��ȡѡ�е���
	int curRow = ui.tableView->currentIndex().row();

	//ɾ������
	model->removeRow(curRow);
	int ok = QMessageBox::warning(this, QString::fromLocal8Bit("ɾ����ǰ��!"), QString::fromLocal8Bit("��ȷ��"
		"ɾ����ǰ����"),
		QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		model->revertAll(); //�����ɾ��������
	}
	else 
		model->submitAll(); //�����ύ�������ݿ���ɾ������  

}



void QDlgDevManager::bt_edit_click()
{
// 	int curRow = ui.tableView->currentIndex().row();
// 	int curCol = ui.tableView->currentIndex().column();
// 	//(const QModelIndex &index, const QVariant &value
// 	QModelIndex  index = ui.tableView->currentIndex();
// 	ui.tableView->cur



}
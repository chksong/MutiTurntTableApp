#include "QDlgDevManager.h"


#include <QMessageBox>
#include <QSqlError>
#include "QFindDevs.h"

//数据库密码 inhu!@#$%^001

QDlgDevManager::QDlgDevManager(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowTitle(QStringLiteral("转台设备配置管理"));
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);



	model = new QSqlTableModel(this);
	model->setTable("tb_devs");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);


	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("名称"));
	model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("设备IP"));
	model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("摄像机IP"));
	model->select(); //选取整个表的所有行


	ui.tableView->setModel(model);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //使其不可编辑
	ui.tableView->setColumnHidden(0, true);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


//如果你用在QTableView中使用右键菜单，需启用该属性        
//	ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	
}

QDlgDevManager::~QDlgDevManager()
{


}



// 修改数据的保存
void QDlgDevManager::bt_save_click()
{
	model->database().transaction(); //开始事务操作
	if (model->submitAll()) {
		model->database().commit(); //提交
	}
	else {
		model->database().rollback(); //回滚
		QMessageBox::warning(this, tr("tableModel"),
			tr("数据库错误: %1")
			.arg(model->lastError().text()));
	}
}

// 修改数据撤销
void QDlgDevManager::bt_cancle_click()
{
	model->revertAll();
	
}


void QDlgDevManager::bt_add_click()
{
	/*
	**  添加设备
	int rowNum = model->rowCount(); //获得表的行数
	model->insertRow(rowNum); //添加一行
	QString strDev = QString::fromLocal8Bit("新设备 %1").arg(rowNum);
	model->setData(model->index(rowNum, 1), strDev);
	*/

	QFindDevs *dlg = new QFindDevs(this);
	dlg->show();
}


void QDlgDevManager::bt_del_click()
{
	//获取选中的行
	int curRow = ui.tableView->currentIndex().row();

	//删除该行
	model->removeRow(curRow);
	int ok = QMessageBox::warning(this, QString::fromLocal8Bit("删除当前行!"), QString::fromLocal8Bit("你确定"
		"删除当前行吗？"),
		QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		model->revertAll(); //如果不删除，则撤销
	}
	else 
		model->submitAll(); //否则提交，在数据库中删除该行  

}



void QDlgDevManager::bt_edit_click()
{
// 	int curRow = ui.tableView->currentIndex().row();
// 	int curCol = ui.tableView->currentIndex().column();
// 	//(const QModelIndex &index, const QVariant &value
// 	QModelIndex  index = ui.tableView->currentIndex();
// 	ui.tableView->cur



}
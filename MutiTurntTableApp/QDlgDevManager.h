#pragma once

#include <QDialog>
#include "ui_QDlgDevManager.h"



#include <QSqlTableModel>
#include <QTableView>


#include <tuple>


class QDlgDevManager : public QDialog
{
	Q_OBJECT

public:
	QDlgDevManager(QWidget *parent = Q_NULLPTR);
	~QDlgDevManager();


signals:
	// 添加删除设备后，发送到主控窗口，以更新界面
	void sigAddDevToUI(std::tuple<QString, QString, QString> &msgData);
	void sigDelDevToUI(std::tuple<QString, QString, QString> &msgData);

public slots:
	void bt_save_click();
	void bt_cancle_click();
	void bt_add_click();
	void bt_edit_click();
	void bt_del_click();

	void AddDevBySignal(std::tuple<QString, QString, QString>& msgData);
private:
	Ui::QDlgDevManager ui;

	QSqlTableModel  *model;


};

#pragma once

#include <QDialog>
#include "ui_QDlgDevManager.h"



#include <QSqlTableModel>
#include <QTableView>



class QDlgDevManager : public QDialog
{
	Q_OBJECT

public:
	QDlgDevManager(QWidget *parent = Q_NULLPTR);
	~QDlgDevManager();

public slots:
	void bt_save_click();
	void bt_cancle_click();
	void bt_add_click();
	void bt_edit_click();
	void bt_del_click();
private:
	Ui::QDlgDevManager ui;

	QSqlTableModel  *model;


};

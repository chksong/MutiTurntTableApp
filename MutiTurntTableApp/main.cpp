#include "MutiTurntTableApp.h"
#include <QtWidgets/QApplication>

#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>


#include <string>

bool openMySQLDB()
{
	// 输出可用数据库引擎
	qDebug() << "Available drivers:";
	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
		qDebug() << driver;

	//建立数据库连接
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("DB_TurnTables");
	db.setUserName("root");
	db.setPassword("123456");
	if (!db.open()) {
		qDebug() << "Failed t connect to root mysql admin";
		return false;
	}
	else 
		qDebug() << "connect to db_turntable sucessful";

	QString strName = QString::fromLocal8Bit("北京市公安局");

	QSqlQuery query(db);
	bool ret = query.exec("CREATE TABLE IF NOT EXISTS tb_devs3 (id int primary key AUTO_INCREMENT,name varchar(200),dev_ip varchar(50),camer_ip varchar(50) ) CHARSET = utf8");
	//auto ret2 = query.exec("insert into tb_devs3(name) values(strNameQSqlQuery query; 
	QSqlQuery query2(db);
	query2.prepare("INSERT INTO tb_devs3 (name, dev_ip) VALUES ( :name, :dev_ip)");
	query2.bindValue(":name", QString::fromLocal8Bit("北京市"));
	query2.bindValue(":dev_ip", "192.168.0.2");
	auto ret2 = query2.exec();


	return true;
}


 

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	openMySQLDB();

	MutiTurntTableApp w;

	w.show();
	return a.exec();
}

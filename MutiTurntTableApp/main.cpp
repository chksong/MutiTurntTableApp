#include "MutiTurntTableApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MutiTurntTableApp w;
	w.show();
	return a.exec();
}

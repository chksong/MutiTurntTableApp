#include "QtRunDegee.h"



QtRunDegee::QtRunDegee(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

}

QtRunDegee::~QtRunDegee()
{
}

#include "QtViewItem.h"


#include <QAction>


QtViewItem::QtViewItem(QObject *parent)
	: QPushButton(reinterpret_cast<QWidget *> (parent))
{


	QAction *actionOne = new QAction(this);
	QAction *actionTwo = new QAction(this);
	QAction  *actionThree = new QAction(this);

	actionOne->setText(QString::fromLocal8Bit("У׼"));
	actionTwo->setText("ActionTwo");
	actionThree->setText("ActionThree");

	setContextMenuPolicy(Qt::ActionsContextMenu);

	addAction(actionOne);
	addAction(actionTwo);
	addAction(actionThree);

}

QtViewItem::~QtViewItem()
{


}

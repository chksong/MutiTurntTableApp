#include "QtRunModel.h"

QtRunModel::QtRunModel(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);


	m_ParentItem = reinterpret_cast<QtViewItem*>( parent);

	if (m_ParentItem->m_X_Model > 0) {
		ui.RB_X_SHUN->setChecked(true);
	}
	else if (m_ParentItem->m_X_Model < 0) {
		ui.RB_X_NIE->setChecked(true);
	}
	else {
		ui.RB_X_STOP->setChecked(true);
	}




	if (m_ParentItem->m_Y_Model >0 )
	{
		ui.RB_Y_UP->setChecked(true);
	} 
	else if (m_ParentItem->m_Y_Model < 0)
	{
		ui.RB_Y_DOWN->setChecked(true);
	}
	else {
		ui.RB_Y_STOP->setChecked(true);
	}
	
}

QtRunModel::~QtRunModel()
{


}


// 保存配置项到  设备
void QtRunModel::saveCfg()
{
	//1  获取选择 

	auto is_x_shun = ui.RB_X_SHUN->isChecked();
	auto is_x_nie = ui.RB_X_NIE->isChecked();
	auto is_x_stop = ui.RB_X_STOP->isChecked();


	auto is_y_up = ui.RB_Y_UP->isChecked();
	auto is_y_down = ui.RB_Y_DOWN->isChecked();
	auto is_y_stop = ui.RB_Y_STOP->isChecked();



	// 2 将配置信息保存到设备，反馈信息
	if (is_x_shun) {
		m_ParentItem->m_X_Model = 1;
	}
	else if (is_x_nie) {
		m_ParentItem->m_X_Model = -1;
	}
	else {
		m_ParentItem->m_X_Model = 0;
	}


	if (is_y_up)
	{
		m_ParentItem->m_Y_Model = 1;
	}
	else if (is_y_down) {
		m_ParentItem->m_Y_Model = -1;
	}
	else {
		m_ParentItem->m_Y_Model = 0;
	}


	accept();
}
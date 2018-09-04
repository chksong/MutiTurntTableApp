#pragma once

#include <QPushButton>
#include <array>
#include <memory>

#include "TurnTableCommunication.h"

class QtViewItem : public QPushButton
{
	Q_OBJECT

public:
	QtViewItem(QObject *parent );
	~QtViewItem();

public:
	using SmartQStringPtr = std::shared_ptr<QString>;
	bool setCfg(SmartQStringPtr strAddres, SmartQStringPtr strCOM, SmartQStringPtr strCamIP);
	bool start();
public slots :
	void menuRunModel();
	void menuRunDegree();

public:

	int  m_X_Model;  // 0 = ֹͣ��1 = ˳ʱ�룬 -1 ��ʱ�� ��
	int  m_Y_Model;  // 0 = ֹͣ��1 = ���ϣ�  -1 ������ת��

private:
	// �豸�Ĵ���Э��
	CTurnTableCommunication *m_devCommunication;

	SmartQStringPtr		m_strCOM;
	SmartQStringPtr		m_strCamIP;
	SmartQStringPtr	    m_strAddress;

	std::array<char, 4> arrayAddress;



};

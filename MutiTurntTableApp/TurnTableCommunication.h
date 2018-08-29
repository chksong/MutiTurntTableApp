#pragma once

#include <array>
#include <string>

#include <QObject>
#include <QString>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <tuple>
#include <array>


enum class FunCodeValue :  char
{
	ReSetAddress   =  2,    //�����վ�ͨ�ŵ�ַ
	QueryAddress   =  3,   //��ѯ�վ���ͨ�ŵ�ַ������汾��Ϣ

	SetRunAngle	   =  8,   //�趨�վ�׷������
	QueryCuraAngle =  10, // ��ѯ�������ĵ�ǰ�ĽǶ�5
	SetZeroAngle   =  55,  // �վ��Ƕ�0λ������

	Y_DOWN  = 31 ,  // Y ��������
	Y_UP	= 32 ,  // Y ����������
	Y_STOP  = 30 ,  // Y ����ֹͣ
	
	X_CW    = 41 ,  // X   ˳ʱ��
	X_ACW   = 42 ,  // X  ��ʱ��
	X_STOP  = 40 ,  // X  ����ֹͣ��

	DetectException = 22 ,// ����쳣
};



#pragma   pack(1)
typedef struct SendData
{
	char address[4];   // �ֻ���ַ
	char funKey;       // ���ܴ���
	char len;          // ���ݳ���
	char data[7];
	char crcLow;       //CRC ��λ
	char crcHight;     //CRC ��λ
}SendDataStruct;

typedef struct AckDate10
{
	char address[4];   // �ֻ���ַ
	char funKey;       // ���ܴ���
	char date[3];     // ����
	char crcLow;       //CRC ��λ
	char crcHight;     //CRC ��λ
}AckDate10Struct;

typedef struct AckDate11
{
	char address[4];   // �ֻ���ַ
	char funKey;       // ���ܴ���
	char tag;         // ��־
	char date[3];     // ����
	char crcLow;       //CRC ��λ
	char crcHight;     //CRC ��λ
}AckDate11Struct;

#pragma pack()

//ת̨�豸ͨ��Э��ĵķ�װ
class CTurnTableCommunication  : QObject
{
	Q_OBJECT
public:
	CTurnTableCommunication(QObject *parent);
	~CTurnTableCommunication();

public:
	//���ô���
	bool setAndOpenCOM(QString &strCOM);
	//���ö��վ��ӵ�ͨ�ŵ�ַ��
	bool setAddress(std::array<char, 4>& address);
	bool MakeSendDataAdrress(SendDataStruct& senddata);

	//ͬ����ѯ�豸��ַ��
	std::tuple<bool, QString> GetDevAddressSync(QString& strCOM ,std::array<char, 4>& ackAddress, char& version);

	// ���������豸�ĵ�ַ
	std::tuple<bool, QString> ResetDevAddressSync(QString& strCOM, std::array<char, 4>& sourceAddress);

	void test();

protected:
	bool openSerialPort(QString &strCOM);

	template<typename T>
	bool SetZeroMem(T& senddata);

	std::tuple<char, char> Get_CRC16(unsigned char *Crc16_num, unsigned char nLength );
	bool  Check_CRC16(unsigned char *Crc16_num, unsigned char nLength);


private:
	std::array<char, 4>  m_address;       //�ֻ���ַ
	QString         m_strCOM;		  // ���ں�

	QSerialPort*   m_Serial;
};


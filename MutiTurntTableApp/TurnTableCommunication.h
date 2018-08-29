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
	ReSetAddress   =  2,    //设置日镜通信地址
	QueryAddress   =  3,   //查询日镜的通信地址和软件版本信息

	SetRunAngle	   =  8,   //设定日镜追日运行
	QueryCuraAngle =  10, // 查询编码器的当前的角度5
	SetZeroAngle   =  55,  // 日镜角度0位置设置

	Y_DOWN  = 31 ,  // Y 向上运行
	Y_UP	= 32 ,  // Y 的向下运行
	Y_STOP  = 30 ,  // Y 方向停止
	
	X_CW    = 41 ,  // X   顺时针
	X_ACW   = 42 ,  // X  逆时针
	X_STOP  = 40 ,  // X  方向停止。

	DetectException = 22 ,// 检查异常
};



#pragma   pack(1)
typedef struct SendData
{
	char address[4];   // 分机地址
	char funKey;       // 功能代码
	char len;          // 数据长度
	char data[7];
	char crcLow;       //CRC 低位
	char crcHight;     //CRC 高位
}SendDataStruct;

typedef struct AckDate10
{
	char address[4];   // 分机地址
	char funKey;       // 功能代码
	char date[3];     // 数据
	char crcLow;       //CRC 低位
	char crcHight;     //CRC 高位
}AckDate10Struct;

typedef struct AckDate11
{
	char address[4];   // 分机地址
	char funKey;       // 功能代码
	char tag;         // 标志
	char date[3];     // 数据
	char crcLow;       //CRC 低位
	char crcHight;     //CRC 高位
}AckDate11Struct;

#pragma pack()

//转台设备通信协议的的封装
class CTurnTableCommunication  : QObject
{
	Q_OBJECT
public:
	CTurnTableCommunication(QObject *parent);
	~CTurnTableCommunication();

public:
	//设置串口
	bool setAndOpenCOM(QString &strCOM);
	//设置定日镜子的通信地址，
	bool setAddress(std::array<char, 4>& address);
	bool MakeSendDataAdrress(SendDataStruct& senddata);

	//同步查询设备地址，
	std::tuple<bool, QString> GetDevAddressSync(QString& strCOM ,std::array<char, 4>& ackAddress, char& version);

	// 重新设置设备的地址
	std::tuple<bool, QString> ResetDevAddressSync(QString& strCOM, std::array<char, 4>& sourceAddress);

	void test();

protected:
	bool openSerialPort(QString &strCOM);

	template<typename T>
	bool SetZeroMem(T& senddata);

	std::tuple<char, char> Get_CRC16(unsigned char *Crc16_num, unsigned char nLength );
	bool  Check_CRC16(unsigned char *Crc16_num, unsigned char nLength);


private:
	std::array<char, 4>  m_address;       //分机地址
	QString         m_strCOM;		  // 串口号

	QSerialPort*   m_Serial;
};


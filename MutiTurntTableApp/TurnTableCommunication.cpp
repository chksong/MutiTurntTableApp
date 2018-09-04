#include "TurnTableCommunication.h"

#include <cstdlib>




CTurnTableCommunication::CTurnTableCommunication(QObject *parent):
	QObject(parent)
{
	m_Serial = new QSerialPort(this);
}


CTurnTableCommunication::~CTurnTableCommunication()
{
	if (m_Serial->isOpen())
	{
		m_Serial->close();
	}
}






bool CTurnTableCommunication::setAddress(std::array<char, 4>& address)
{
	m_address = address;

	return true;
}

bool CTurnTableCommunication::Check_CRC16(unsigned char *Crc16_num, unsigned char nLength )
{
	unsigned short crc = 0xFFFF;

	unsigned char i, j;
	unsigned short Data;
	for (j = 0; j < nLength; j++)
	{
		crc = crc ^ *Crc16_num++;
		for (i = 0; i < 8; i++)
		{
			if ((crc & 0x0001) > 0)
			{
				crc = crc >> 1;
				crc = crc ^ 0xa001;
			}
			else
				crc = crc >> 1;
		}
	}

	//	Data = ((crc & 0x00FF) << 8) | ((crc & 0xFF00) >> 8);
	unsigned char crclow = crc & 0x00FF;
	unsigned char crcHight = (crc & 0xFF00) >> 8;
	return (crclow == Crc16_num[nLength]) && (crcHight == Crc16_num[nLength+1]);
}


// CRC16 校验
std::tuple<char, char> CTurnTableCommunication::Get_CRC16(unsigned char *Crc16_num, unsigned char nLength)
{
	unsigned short crc = 0xFFFF;

	unsigned char i, j;
	unsigned short Data;
	for (j = 0; j < nLength; j++)
	{
		crc = crc ^ *Crc16_num++;
		for (i = 0; i < 8; i++)
		{
			if ((crc & 0x0001) > 0)
			{
				crc = crc >> 1;
				crc = crc ^ 0xa001;
			}
			else
				crc = crc >> 1;
		}
	}

//	Data = ((crc & 0x00FF) << 8) | ((crc & 0xFF00) >> 8);
	unsigned char crclow = crc & 0x00FF;
	unsigned char crcHight = (crc & 0xFF00) >> 8;
	return std::make_tuple(crclow, crcHight);
}




bool CTurnTableCommunication::MakeSendDataAdrress(SendDataStruct& senddata)
{
	senddata.address[0] = m_address[0];
	senddata.address[1] = m_address[1];
	senddata.address[2] = m_address[2];
	senddata.address[3] = m_address[3];

	return true;
}


template<typename T>
bool CTurnTableCommunication::SetZeroMem(T& senddata)
{
	memset(&senddata, 0, sizeof(senddata));
	return true;
}

// 设置和打开串口
bool CTurnTableCommunication::setAndOpenCOM(QString &strCOM)
{
	m_strCOM = strCOM;
	m_Serial->setPortName(m_strCOM);
	
	/* 设置波特率 */
	m_Serial->setBaudRate(QSerialPort::Baud9600);
	/* 设置数据位数 */
	m_Serial->setDataBits(QSerialPort::Data8);
	/* 设置奇偶校验 */
	m_Serial->setParity(QSerialPort::NoParity);
	/* 设置停止位 */
	m_Serial->setStopBits(QSerialPort::OneStop);
	/* m_Serial */
	m_Serial->setFlowControl(QSerialPort::NoFlowControl);
	/* 打开串口 */
	m_Serial->open(QIODevice::ReadWrite);
	/* 设置串口缓冲区大小，这里必须设置为这么大 */
	m_Serial->setReadBufferSize(1024);

	if (!m_Serial->open(QIODevice::ReadWrite)) {
		QString strErr = QString::fromLocal8Bit("Failed to open port %1, error: %2").arg(m_strCOM).arg(m_Serial->errorString());
		return false;
	}
	else {
		return false;
	}
	
}

bool CTurnTableCommunication::openSerialPort(QString &strCOM)
{
	if ( m_Serial->isOpen()) {
		return true;
	}

	m_strCOM = strCOM;
	m_Serial->setPortName(m_strCOM);

	/* 设置波特率 */
	m_Serial->setBaudRate(QSerialPort::Baud9600);
	/* 设置数据位数 */
	m_Serial->setDataBits(QSerialPort::Data8);
	/* 设置奇偶校验 */
	m_Serial->setParity(QSerialPort::NoParity);
	/* 设置停止位 */
	m_Serial->setStopBits(QSerialPort::OneStop);
	/* m_Serial */
	m_Serial->setFlowControl(QSerialPort::NoFlowControl);
	/* 打开串口 */
	m_Serial->open(QIODevice::ReadWrite);
	/* 设置串口缓冲区大小，这里必须设置为这么大 */
	m_Serial->setReadBufferSize(2048);

		//如果打开串口失败，则返回
	if (m_Serial->open(QIODevice::ReadWrite)) {
		return true;
	}
	else {
		return  false;
	}
}
  

std::tuple<bool, QString> CTurnTableCommunication::ResetDevAddressSync(QString& strCOM, std::array<char, 4>& expectAddress)
{
	
	//如果打开串口失败，则返回
	if (! openSerialPort(strCOM)) {
		QString strErr = QString::fromLocal8Bit("打开串口失败 %1, error: %2").arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}


	//组装查询地址的协议，发送
	SendDataStruct  sendData;
	SetZeroMem(sendData);
	sendData.address[0] = 0x00;
	sendData.address[1] = 0x00;
	sendData.address[2] = 0x00;
	sendData.address[3] = 0x00;
	sendData.funKey = static_cast<char>(FunCodeValue::ReSetAddress);
	sendData.len = 0x07;
	sendData.data[0] = expectAddress[0];
	sendData.data[1] = expectAddress[1];
	sendData.data[2] = expectAddress[2];
	sendData.data[3] = expectAddress[3];
	auto crc = Get_CRC16(reinterpret_cast<unsigned char*>(&sendData), sizeof(sendData) - 2);
	sendData.crcLow = std::get<0>(crc);
	sendData.crcHight = std::get<1>(crc);

	// 发送数据
	const qint64 bytesWritten = m_Serial->write(reinterpret_cast<char*>(&sendData), sizeof(sendData));
	if (bytesWritten == -1) {
		QString strErr = QString::fromLocal8Bit("Failed to write the data to port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}
	else if (bytesWritten != sizeof(sendData)) {
		QString strErr = QString::fromLocal8Bit("Failed to write all the data to port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}
	else if (!m_Serial->waitForBytesWritten(5000)) {
		QString strErr = QString::fromLocal8Bit("Operation timed out or an error "
			"occurred for port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}

	// 读取数据
	QByteArray readData;
	if (m_Serial->waitForReadyRead(5000)) {
		readData.append(m_Serial->readAll());
	}

	//收到数据长度不对 跳出
	if (readData.length() != sizeof(AckDate10Struct)) {
		return std::make_tuple(false, QString::fromLocal8Bit("收到长度不对"));
	}

	AckDate10Struct  ackData;
	SetZeroMem(ackData);
	std::memcpy((unsigned char*)&ackData, readData.data(), sizeof(AckDate10Struct));
	if (!Check_CRC16((unsigned char*)&ackData, sizeof(ackData) - 2))
	{
		return std::make_tuple(false, QString::fromLocal8Bit("CRC校验有问题"));
	}

	//检查返回的数据和设置的数据是否一致
	if (expectAddress[0] != ackData.address[0] || expectAddress[1] != ackData.address[1]
		 || expectAddress[2] != ackData.address[2] || expectAddress[3] != ackData.address[3]
		)
	{
		return std::make_tuple(false, QString("收到数据与期望的数据不一致"));
	}
	else {
		return std::make_tuple(true, QString(""));
	}
}

//同步查询设备的地址 和版本
std::tuple<bool, QString> CTurnTableCommunication::GetDevAddressSync(QString& strCOM, std::array<char, 4>& ackAddress, char& version)
{

	//如果打开串口失败，则返回
	if (!openSerialPort(strCOM)) {
		QString strErr = QString::fromLocal8Bit("打开串口失败 %1, error: %2").arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}

	//组装查询地址的协议，发送
	SendDataStruct  sendData;
	SetZeroMem(sendData);
	sendData.address[0] = 0x00;
	sendData.address[1] = 0x00;
	sendData.address[2] = 0x00;
	sendData.address[3] = 0x00;
	sendData.funKey = static_cast<char>(FunCodeValue::QueryAddress);
	auto crc = Get_CRC16(reinterpret_cast<unsigned char*>(&sendData), sizeof(sendData) - 2);
	sendData.crcLow = std::get<0>(crc);
	sendData.crcHight = std::get<1>(crc);

	// 发送数据
	const qint64 bytesWritten = m_Serial->write(reinterpret_cast<char*>(&sendData) , sizeof(sendData));
	if (bytesWritten == -1) {
		QString strErr = QString::fromLocal8Bit("Failed to write the data to port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString()) ;
		return std::make_tuple(false, strErr);
	}
	else if (bytesWritten != sizeof(sendData)) {
		QString strErr = QString::fromLocal8Bit("Failed to write all the data to port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString()) ;
		return std::make_tuple(false, strErr);
	}
	else if (!m_Serial->waitForBytesWritten(5000)) {
		QString strErr = QString::fromLocal8Bit("Operation timed out or an error "
			"occurred for port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString()) ;
		return std::make_tuple(false, strErr);
	}

	// 读取数据
	QByteArray readData;
	if(m_Serial->waitForReadyRead(5000)) {
		readData.append(m_Serial->readAll());
	}

	//收到数据长度不对 跳出
	if (readData.length() != sizeof(AckDate10Struct)){
		return std::make_tuple(false, QString::fromLocal8Bit("收到长度不对"));
	}
	
	AckDate10Struct  ackData;
	SetZeroMem(ackData);
	std::memcpy((unsigned char*)&ackData, readData.data(), sizeof(AckDate10Struct));
	if ( ! Check_CRC16((unsigned char*)&ackData, sizeof(ackData) - 2))
	{
		return std::make_tuple(false, QString::fromLocal8Bit("CRC校验有问题"));
	}
	 
	ackAddress[0] = ackData.address[0];
	ackAddress[1] = ackData.address[1];
	ackAddress[2] = ackData.address[2];
	ackAddress[3] = ackData.address[3];

	version = ackData.date[0];

	return std::make_tuple(true, QString(""));
}


// 设置电机的运动方式
std::tuple<bool, QString> CTurnTableCommunication::setRunModle_xy(int direction, int xyModel)
{
	char fun_cmd;
	if (direction > 0 )  // X方向
	{  
		if (xyModel > 0)  {  // 顺时针
			fun_cmd = 0x31;
		}
		else if (xyModel < 0 )  // 逆时针
		{
			fun_cmd = 0x32;
		}
		else {
			fun_cmd = 0x30;   // 停止
		}
	}
	else if (direction  < 0 ) // Y方向
	{
		if (xyModel > 0) {    //向上
			fun_cmd = 0x42;
		}
		else if (xyModel < 0)  //向下
		{
			fun_cmd = 0x41;   
		}
		else {               // 停止
			fun_cmd = 0x40;   
		}
	}

	if (! m_Serial->isOpen())
	{
		if (!openSerialPort(m_strCOM)) {
			QString strErr = QString::fromLocal8Bit("打开串口失败 %1, error: %2").arg(m_strCOM).arg(m_Serial->errorString());
			return std::make_tuple(false, strErr);
		}
	}
	

	//组装查询地址的协议，发送
	SendDataStruct  sendData;
	SetZeroMem(sendData);
	sendData.address[0] = m_address[0];
	sendData.address[1] = m_address[1];
	sendData.address[2] = m_address[2];
	sendData.address[3] = m_address[3];
	sendData.len = 0x07;
	sendData.funKey = static_cast<char>(fun_cmd);
	auto crc = Get_CRC16(reinterpret_cast<unsigned char*>(&sendData), sizeof(sendData) - 2);
	sendData.crcLow = std::get<0>(crc);
	sendData.crcHight = std::get<1>(crc);

	// 发送数据
	const qint64 bytesWritten = m_Serial->write(reinterpret_cast<char*>(&sendData), sizeof(sendData));
	if (bytesWritten == -1) {
		QString strErr = QString::fromLocal8Bit("Failed to write the data to port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}
	else if (bytesWritten != sizeof(sendData)) {
		QString strErr = QString::fromLocal8Bit("Failed to write all the data to port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}
	else if (!m_Serial->waitForBytesWritten(5000)) {
		QString strErr = QString::fromLocal8Bit("Operation timed out or an error "
			"occurred for port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}



	// 读取数据
	QByteArray readData;
	if (m_Serial->waitForReadyRead(5000)) {
		readData.append(m_Serial->readAll());
	}

	//收到数据长度不对 跳出
	if (readData.length() != sizeof(AckDate10Struct)) {
		return std::make_tuple(false, QString::fromLocal8Bit("收到长度不对"));
	}

	AckDate10Struct  ackData;
	SetZeroMem(ackData);
	std::memcpy((unsigned char*)&ackData, readData.data(), sizeof(AckDate10Struct));
	if (!Check_CRC16((unsigned char*)&ackData, sizeof(ackData) - 2))
	{
		return std::make_tuple(false, QString::fromLocal8Bit("CRC校验有问题"));
	}

	//根据协议 检验数据的对错
	if (ackData.funKey != fun_cmd 
		|| ackData.date[2] != 0x55)
	{
		return std::make_tuple(false, QString::fromLocal8Bit("收到数据内部错误"));
	}

	return std::make_tuple(true, QString(""));
}



// 设置日镜电机的运动角度
std::tuple<bool, QString> CTurnTableCommunication::setRunDegree_xy(double xDegree, double yDegree)
{
	if (!m_Serial->isOpen())
	{
		if (!openSerialPort(m_strCOM)) {
			QString strErr = QString::fromLocal8Bit("打开串口失败 %1, error: %2").arg(m_strCOM).arg(m_Serial->errorString());
			return std::make_tuple(false, strErr);
		}
	}


	//组装查询地址的协议，发送
	SendDataStruct  sendData;
	SetZeroMem(sendData);
	sendData.address[0] = m_address[0];
	sendData.address[1] = m_address[1];
	sendData.address[2] = m_address[2];
	sendData.address[3] = m_address[3];
	sendData.funKey = static_cast<char>(0x08);
	sendData.len = 0x07;
	sendData.data[0] = 0x00;

	short xInt = (int)xDegree; // X度数的整数部分
	char xFloat = char (((short)xDegree - xInt) * 100);
	sendData.data[1] = (xInt >> 8) & 0x00FF;
	sendData.data[2] = xInt & 0x00FF;
	sendData.data[3] = xFloat;

	short yInt = (int)yDegree; // Y度数的整数部分
	char yFloat = char(((short)yDegree - yInt) * 100);
	sendData.data[4] = (yInt >> 8) & 0x00FF;
	sendData.data[5] = yInt & 0x00FF;
	sendData.data[6] = yFloat;

	auto crc = Get_CRC16(reinterpret_cast<unsigned char*>(&sendData), sizeof(sendData) - 2);
	sendData.crcLow = std::get<0>(crc);
	sendData.crcHight = std::get<1>(crc);


	// 发送数据
	const qint64 bytesWritten = m_Serial->write(reinterpret_cast<char*>(&sendData), sizeof(sendData));
	if (bytesWritten == -1) {
		QString strErr = QString::fromLocal8Bit("Failed to write the data to port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}
	else if (bytesWritten != sizeof(sendData)) {
		QString strErr = QString::fromLocal8Bit("Failed to write all the data to port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}
	else if (!m_Serial->waitForBytesWritten(5000)) {
		QString strErr = QString::fromLocal8Bit("Operation timed out or an error "
			"occurred for port %1, error: %2")
			.arg(m_strCOM).arg(m_Serial->errorString());
		return std::make_tuple(false, strErr);
	}



	// 读取数据
	QByteArray readData;
	if (m_Serial->waitForReadyRead(5000)) {
		readData.append(m_Serial->readAll());
	}

	//收到数据长度不对 跳出
	if ( readData.length() != sizeof(AckDate10Struct) && 
		readData.length() != 2 * sizeof(AckDate10Struct)) {
		return std::make_tuple(false, QString::fromLocal8Bit("收到长度不对"));
	}

	//校验数据包
	AckDate11Struct  ackData;
	SetZeroMem(ackData);
	std::memcpy((unsigned char*)&ackData, readData.data(), sizeof(AckDate11Struct));
	if (!Check_CRC16((unsigned char*)&ackData, sizeof(ackData) - 2))
	{
		return std::make_tuple(false, QString::fromLocal8Bit("CRC校验有问题"));
	}
	

	//仔细分析包数据的内容



	// 如果收到是2个包
	if (readData.length() == 2 * sizeof(AckDate11Struct))
	{
		//校验数据包
		AckDate11Struct  ackData2;
		SetZeroMem(ackData2);
		std::memcpy((unsigned char*)&ackData2, readData.data() + sizeof(AckDate11Struct), sizeof(AckDate11Struct));
		if (!Check_CRC16((unsigned char*)&ackData2, sizeof(ackData2) - 2))
		{
			return std::make_tuple(false, QString::fromLocal8Bit("CRC校验有问题"));
		}

		//仔细分析包数据的内容 

	}

}


void CTurnTableCommunication::test()
{
	//组装查询地址的协议，发送
	SendDataStruct  sendData;
	SetZeroMem(sendData);
	sendData.address[0] = 0x00;
	sendData.address[1] = 0x00;
	sendData.address[2] = 0x00;
	sendData.address[3] = 0x00;
	sendData.funKey = static_cast<char>(FunCodeValue::QueryAddress);
	auto len = sizeof(sendData);
	auto crc = Get_CRC16(reinterpret_cast<unsigned char*>(&sendData), sizeof(sendData) - 2);
	sendData.crcLow = std::get<0>(crc);
	sendData.crcHight = std::get<1>(crc);

	return;
}
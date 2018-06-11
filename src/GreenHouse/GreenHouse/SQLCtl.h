#pragma once
#include "mysql.h"
#include <vector>

using namespace std;

enum DATA_TYPE 
{
	DATA_TYPE_LIGHT = 1,
	DATA_TYPE_TEMP = 2,
	DATA_TYPE_HUMIDITY = 3,
	DATA_TYPE_CO2 = 4,
	DATA_TYPE_SOIL_TEMP = 5,
	DATA_TYPE_SOIL_HUMIDITY = 6,
	DATA_TYPE_WIND_SPEED = 7,
	DATA_TYPE_WIND_DIRECTION = 8,
};

typedef struct tagBaseInfo
{
	CString time;
	CString info;
}BaseInfo, *pBaseInfo;

typedef struct tagSelectInfo
{
	CString startTime;
	CString endTime;
	vector<BaseInfo> infoList;
}SelectInfo, *pSelectInfo;

class CSQLCtl
{
public:
	CSQLCtl(void);
	~CSQLCtl(void);

public:
	int ConnectSQL();
	int InsertData(pBaseInfo info, DATA_TYPE type);
	int SelectData(pSelectInfo info, DATA_TYPE type);

private:
	MYSQL mysql; //数据库连接句柄
	bool m_connect;
};


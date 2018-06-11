#include "StdAfx.h"
#include "SQLCtl.h"
//#include "mysql.h"

CSQLCtl::CSQLCtl(void)
{
	m_connect = false;
}


CSQLCtl::~CSQLCtl(void)
{
}

int CSQLCtl::ConnectSQL()
{
	if( mysql_init(&mysql) == NULL )
	{
		OutputDebugString("Is Connected MySQL!\n");
		return 0;
	}

	if(!mysql_real_connect(&mysql,"127.0.0.1","root","","greenhouse",3306,NULL,0))
	{
		OutputDebugString("Connect MySQL Error!\n");
		m_connect = false;
		return -1;
	}
	else
	{
		OutputDebugString("Connect MySQL OK!\n");
		m_connect = true;
		return 0;
	}

	return 0;
}

int CSQLCtl::InsertData(pBaseInfo info, DATA_TYPE type)
{
	if (m_connect == false)
	{
		//if (ConnectSQL() != 0) return false;
		return false;
	}
	CString sql = "";

	switch(type)
	{
	case DATA_TYPE_LIGHT:
		sql = "INSERT INTO light VALUES (NULL, '";
		break;
	case DATA_TYPE_TEMP:
		sql = "INSERT INTO temp VALUES (NULL, '";
		break;
	case DATA_TYPE_HUMIDITY:
		sql = "INSERT INTO hum VALUES (NULL, '";
		break;
	case DATA_TYPE_CO2:
		sql = "INSERT INTO co2 VALUES (NULL, '";
		break;
	case DATA_TYPE_SOIL_TEMP:
		sql = "INSERT INTO soil_tmp VALUES (NULL, '";
		break;
	case DATA_TYPE_SOIL_HUMIDITY:
		sql = "INSERT INTO soil_hum VALUES (NULL, '";
		break;
	case DATA_TYPE_WIND_SPEED:
		sql = "INSERT INTO wind_speed VALUES (NULL, '";
		break;
	case DATA_TYPE_WIND_DIRECTION:
		sql = "INSERT INTO wind_direction VALUES (NULL, '";
		break;
	default:
		break;
	}

	sql += info->time;
	sql += "', '";
	sql += info->info;
	sql += "')";

	OutputDebugString(sql);
	OutputDebugString("\n");

	if(0==mysql_query(&mysql, sql.GetBuffer()))
	{
		OutputDebugString("InsertData OK!\n");
	}
	else
	{
		OutputDebugString("InsertData error!\n");
		return -1;
	}
	return 0;
}

int CSQLCtl::SelectData(pSelectInfo info, DATA_TYPE type)
{
	if (m_connect == false)
	{
		//if (ConnectSQL() != 0) return false;
		return false;
	}

	CString loginfo="";
	MYSQL_RES *result = NULL;
	CString sql = "";
	int timeflag = 0;

	switch(type)
	{
	case DATA_TYPE_LIGHT:
		sql = "SELECT TIME,DATA FROM light ";
		break;
	case DATA_TYPE_TEMP:
		sql = "SELECT TIME,DATA FROM temp ";
		break;
	case DATA_TYPE_HUMIDITY:
		sql = "SELECT TIME,DATA FROM hum ";
		break;
	case DATA_TYPE_CO2:
		sql = "SELECT TIME,DATA FROM co2 ";
		break;
	case DATA_TYPE_SOIL_TEMP:
		sql = "SELECT TIME,DATA FROM soil_tmp ";
		break;
	case DATA_TYPE_SOIL_HUMIDITY:
		sql = "SELECT TIME,DATA FROM soil_hum ";
		break;
	case DATA_TYPE_WIND_SPEED:
		sql = "SELECT TIME,DATA FROM wind_speed ";
		break;
	case DATA_TYPE_WIND_DIRECTION:
		sql = "SELECT TIME,DATA FROM wind_direction ";
		break;
	default:
		break;
	}

	if (info->startTime.GetLength() > 0)
	{
		timeflag++;
		sql += "WHERE TIME > '";
		sql += info->startTime;
		sql += "' ";
	}

	if (info->endTime.GetLength() > 0)
	{
		if (timeflag > 0)
		{
			sql += "AND TIME < '";
		}
		else
		{
			sql += "WHERE TIME < '";
		}
		sql += info->endTime;
		sql += "' ";
	}

	sql += "ORDER BY TIME ASC";

	OutputDebugString(sql);
	OutputDebugString("\n");
	
	if(0==mysql_query(&mysql, sql.GetBuffer()))
	{
		loginfo="select data succeed\n";
		OutputDebugString(loginfo);

		//一次性取得数据集
		result=mysql_store_result(&mysql);

		//取得并打印行数
		int rowcount=mysql_num_rows(result);

		loginfo.Format("row count=%d\n",rowcount);
		OutputDebugString(loginfo);

		//取得并打印各字段的名称
		unsigned int fieldcount=mysql_num_fields(result);

		//打印各行
		MYSQL_ROW row=NULL;
		row=mysql_fetch_row(result);
		loginfo="";

		while(NULL!=row)
		{
			BaseInfo base;
			for(int i=0; i<fieldcount;i++)
			{
				loginfo=loginfo+(row[i])+",";
				if (i == 0)
					base.time = row[i];
				else
					base.info = row[i];
			}
			info->infoList.push_back(base);
			
			loginfo=loginfo+"\n";
			row=mysql_fetch_row(result);
		}
		OutputDebugString(loginfo);
	}
	else 
	{
		OutputDebugString("select error!\n");
		return -1;
	}

	return 0;
}
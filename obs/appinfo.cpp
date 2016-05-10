#include "appinfo.h"
#include <QtCore/QCoreApplication>

AppInfo *AppInfo::m_instance = 0;

AppInfo::AppInfo() :
QObject(QCoreApplication::instance())
{
}

QString AppInfo::getAccessToken()
{
	return m_accessToken;
}
void AppInfo::setAccessToken(QString accessToken)
{
	m_accessToken = accessToken;
}

int AppInfo::getCategoryId()
{
	return m_categoryId;
}
void AppInfo::setCategoryId(int categoryId)
{
	m_categoryId = categoryId;
}
QString AppInfo::getDevSn()
{
	return m_devSn;
}
void AppInfo::setDevSn(QString devSn)
{
	m_devSn = devSn;
}

QString AppInfo::getUdid()
{
	return m_udid;
}
void AppInfo::setUdid(QString udid)
{
	m_udid = udid;
}
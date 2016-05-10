#ifndef APPINFO_H
#define APPINFO_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

class AppInfo : public QObject
{
    Q_OBJECT

		Q_PROPERTY(QString accessToken READ getAccessToken WRITE setAccessToken)
		Q_PROPERTY(int categoryId READ getCategoryId WRITE setCategoryId)
		Q_PROPERTY(QString devSn READ getDevSn WRITE setDevSn)
		Q_PROPERTY(QString udid READ getUdid WRITE setUdid)

public:
	static AppInfo* instance()
	{
		static QMutex mutex;
		if (!m_instance) {
			QMutexLocker locker(&mutex);
			if (!m_instance)
				m_instance = new AppInfo;
		}

		return m_instance;
	}

	QString getAccessToken();
	void setAccessToken(QString accessToken);
	int getCategoryId();
	void setCategoryId(int categoryId);
	QString getDevSn();
	void setDevSn(QString devSn);
	QString getUdid();
	void setUdid(QString udid);
private:
	AppInfo();
	static AppInfo* m_instance;
	QString m_accessToken;
	QString m_devSn;
	int m_categoryId;
	QString m_udid;
signals:

public slots:
};

#endif // APPINFO_H
#ifndef MBOSERVICE_H
#define MBOSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include "appinfo.h"

#define MBOServer "http://api.mbo.homca.com"
#define MBOServer_Swagger "http://api.mbo.homca.com/swagger-ui/"
#define MBOAppId "1002"
#define MBOSecretKey "fb9b68cd7b564320a20ff96f05347c3e"

#define MBOCheckAccessToken "/api/checkaccesstoken"
#define MBOForgetPassword "/api/forgetpassword"
#define MBOGetCategory "/api/getcategory"
#define MBOGetDevice "/api/getdevice"
#define MBOLogin "/api/login"
#define MBOLogout "/api/logout"
#define MBORegister "/api/register"
#define MBOSms "/api/sms"
#define MBOStartLive "/api/startlive"
#define MBOStopLive "/api/stoplive"
#define MBOUpload "/api/upload"

#define korganization "com.dyne.homca"
#define kapplication "MBO"

class MBOService : public QObject
{
    Q_OBJECT
public:
    explicit MBOService(QObject *parent = 0);
    void requestUrlGet(const QString &url,QMap<QString,QString> params);
	void requestUrlGetAuth(const QString &url, QMap<QString, QString> params);
	void sms(QString PhoneNo, int MsgType, QString UnionId);
	void regUser(QString UserName, QString Password, QString SmsCode);
	void resetPassword(QString UserName, QString Password, QString SmsCode);
	void login(QString UserName, QString Password);
	void getDevice();
	void getCategory();
	void startLive(QString Name,int CategoryId);
	void stopLive();
private:
	bool isHttpResultSuccess(QNetworkReply &reply);
	QString getMACAdress();
signals:
    void callbackSignal(int,QString,QJsonValue);
public slots:
	void queryFinished(QNetworkReply*);
};

#endif // MBOSERVICE_H

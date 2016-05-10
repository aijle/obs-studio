#include "mboservice.h"
#include<QNetworkInterface>
#include<QList>
#include "obs-app.hpp"

MBOService::MBOService(QObject *parent) : QObject(parent)
{

}

void MBOService::requestUrlGet(const QString &url,QMap<QString,QString> params)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl webUrl = QUrl(url);

    QUrlQuery query;
    query.addQueryItem("format","json");

    QString enc = QString("");

    params.insert("AppId",MBOAppId);

    QList<QString> keys = params.keys();
    qSort(keys.begin(), keys.end());
    QList<QString>::iterator it;

    for(it = keys.begin();it != keys.end();it++)
    {
        query.addQueryItem(*it,params.value(*it));
        enc.append(*it).append("=").append(params.value(*it));
    }
    enc.append("AppSecretKey=").append(MBOSecretKey);

    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash (QByteArray().append(enc), QCryptographicHash::Md5);
    md5.append(bb.toHex());

    query.addQueryItem("Sign",md5);

    webUrl.setQuery(query);

    qDebug()<<"httpReq:"<<webUrl.toString();
    QNetworkRequest request = QNetworkRequest(webUrl);

	connect(manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(queryFinished(QNetworkReply*)));
	QNetworkReply* reply = manager->get(request);
	reply->setParent(this);
}

void MBOService::queryFinished(QNetworkReply* reply){
    if (isHttpResultSuccess(*reply)){
        QString responseStr = QString(reply->readAll());
        qDebug()<<"httpReq Return:"<<responseStr;
		QJsonDocument doc = QJsonDocument::fromJson(responseStr.toUtf8());

        if(!doc.isNull())
        {
            if(doc.isObject())
            {
                QJsonObject obj = doc.object();
                emit callbackSignal(obj.value("Code").toInt(),obj.value("Message").toString(),obj.value("Data"));
            }
            else
            {
                qDebug() << "Document is not an object" << endl;
				emit callbackSignal(-1, QTStr("Error.UnKnown"), QJsonValue());
            }
        }
        else
        {
            qDebug() << "Invalid JSON...\n" << endl;
			emit callbackSignal(-1, QTStr("Error.UnKnown"), QJsonValue());
        }
    }else{
		emit callbackSignal(-1, QTStr("Error.UnKnown"), QJsonValue());
    }

    this->deleteLater();
}

bool MBOService::isHttpResultSuccess(QNetworkReply &reply)
{
	QVariant statusCodeV = reply.attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (reply.error() != QNetworkReply::NoError || statusCodeV.toInt() != 200)
	{
		qDebug() << "webService Error:" << reply.error() << " Status:" << statusCodeV.toInt();
		return false;
	}
	return true;
}

void MBOService::sms(QString PhoneNo, int MsgType, QString UnionId)
{
	QMap<QString, QString> params = QMap<QString, QString>();
	params.insert("MsgType", QString::number(MsgType));
	params.insert("PhoneNo", PhoneNo);
	params.insert("UnionId", getMACAdress());

	requestUrlGet(QString(MBOServer).append(MBOSms), params);
}

void MBOService::regUser(QString UserName, QString Password, QString SmsCode)
{
	QMap<QString, QString> params = QMap<QString, QString>();
	params.insert("UserName", UserName);
	params.insert("Password", QString(QByteArray().append(Password).toBase64()));
	params.insert("SmsCode", SmsCode);
	params.insert("TrueName", "Fake");

	requestUrlGet(QString(MBOServer).append(MBORegister), params);
}

void MBOService::resetPassword(QString UserName, QString Password, QString SmsCode)
{
	QMap<QString, QString> params = QMap<QString, QString>();
	params.insert("UserName", UserName);
	params.insert("Password", QString(QByteArray().append(Password).toBase64()));
	params.insert("SmsCode", SmsCode);

	requestUrlGet(QString(MBOServer).append(MBOForgetPassword), params);
}

void MBOService::login(QString UserName, QString Password)
{
	QMap<QString, QString> params = QMap<QString, QString>();
	params.insert("UserName", UserName);
	params.insert("Password", QString(QByteArray().append(Password).toBase64()));

	requestUrlGet(QString(MBOServer).append(MBOLogin), params);
}

void MBOService::requestUrlGetAuth(const QString &url, QMap<QString, QString> params)
{
	QString accessToken = AppInfo::instance()->getAccessToken();
	params.insert("AccessToken", accessToken);

	requestUrlGet(url, params);
}

void MBOService::getDevice(){
	QMap<QString, QString> params = QMap<QString, QString>();

	requestUrlGetAuth(QString(MBOServer).append(MBOGetDevice), params);
}

void MBOService::getCategory()
{
	QMap<QString, QString> params = QMap<QString, QString>();

	requestUrlGetAuth(QString(MBOServer).append(MBOGetCategory), params);
}

void MBOService::startLive(QString Name,int CategoryId)
{
	QMap<QString, QString> params = QMap<QString, QString>();
	params.insert("Name", Name);
	
	AppInfo * app = AppInfo::instance();
	params.insert("CategoryId", QString::number(CategoryId));
	params.insert("DevSn", app->getDevSn());

	requestUrlGetAuth(QString(MBOServer).append(MBOStartLive), params);
}

void MBOService::stopLive()
{
	QMap<QString, QString> params = QMap<QString, QString>();
	AppInfo * app = AppInfo::instance();
	params.insert("Udid", app->getUdid());

	requestUrlGetAuth(QString(MBOServer).append(MBOStopLive), params);
}

QString MBOService::getMACAdress()
{
	QList<QNetworkInterface>  NetList;
	int NetCount = 0; 
	int Neti = 0;
	QNetworkInterface thisNet;  
	NetList = QNetworkInterface::allInterfaces();
	NetCount = NetList.count();
	for (Neti = 0; Neti < NetCount; Neti++){ 
		if (NetList[Neti].isValid()){ 
			thisNet = NetList[Neti]; 
			break;
		}
	}
	return (thisNet.hardwareAddress());
}

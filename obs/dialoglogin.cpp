#include "dialoglogin.hpp"
#include "ui_dialoglogin.h"
#include <QMessageBox>
#include "obs-app.hpp"
#include "dialogreguser.hpp"
#include "dialogresetpassword.hpp"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

	ui->frame->setStyleSheet("background-color: white;border-style:outset;border-width:1px");

	QFont font;
	font.setPointSize(20);
	ui->labelTitle->setFont(font);
	ui->lineEditPassword->setEchoMode(QLineEdit::Password);

	ui->labelLogo->setPixmap(QPixmap(":/res/images/obs.png"));
	ui->labelLogo->setScaledContents(true);
	ui->labelLogo->setStyleSheet("background-color: transparent;border-style:none;");

	ui->lineEditUser->setFocus();

	connect(ui->toolButtonReg, SIGNAL(clicked()), SLOT(regUser()));
	connect(ui->toolButtonReset, SIGNAL(clicked()), SLOT(resetPassword()));
	connect(ui->checkBoxPassword, SIGNAL(clicked()), SLOT(rememberPassword()));

	m_settings = new QSettings(korganization, kapplication, this);
	QString setValue = m_settings->value(ksetsavePwd, "0").toString();
	if (!setValue.compare("1"))
	{
		ui->lineEditUser->setText(m_settings->value(ksetusercelid, "").toString());
		QString pwd = QString(QByteArray::fromBase64(m_settings->value(ksetpassword, QString(QByteArray("").toBase64())).toString().toLatin1()));
		ui->lineEditPassword->setText(pwd);
		ui->checkBoxPassword->setChecked(true);
	}

	
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::done(int code){
	if (QDialog::Accepted == code){
		QRegExp telReg("(\\d{11})");
		QRegExp passwordReg(".+");
		if (!telReg.exactMatch(ui->lineEditUser->text())){
			QMessageBox::information(this,
				QTStr("Prompt"),
				QTStr("Error.UserName"));
		}
		else if (!passwordReg.exactMatch(ui->lineEditPassword->text())){
			QMessageBox::information(this,
				QTStr("Prompt"),
				QTStr("Error.Password"));
		}
		else{
			MBOService* mbo = new MBOService(this);
			connect(mbo, SIGNAL(callbackSignal(int, QString, QJsonValue)), SLOT(sendResult(int, QString, QJsonValue)));

			progressDialog = new WaitDialog(this);
			progressDialog->show();

			mbo->login(ui->lineEditUser->text(), ui->lineEditPassword->text());
		}
	}
	else{
		QDialog::done(code);
	}
}

void DialogLogin::regUser(){
	DialogRegUser dialog;
	dialog.exec();
}

void DialogLogin::resetPassword()
{
	DialogResetPassword dialog;
	dialog.exec();
}

void DialogLogin::sendResult(int code, QString message, QJsonValue data)
{
	progressDialog->close();

	QMessageBox::information(this,
		QTStr("Prompt"),
		message);

	if (code == 0){
		QJsonObject ret = data.toObject();
		//httpReq Return: "{\"Code\":0,\"Message\":\"³É¹¦\",\"Data\":{\"AccessToken\":\"c62d0923-9eee-4d81-b0cc-79cf297b3419\",\"ExpiredIn\":1462529154}}"
		AppInfo::instance()->setAccessToken(ret.value("AccessToken").toString());

		if (ui->checkBoxPassword->isChecked()){
			m_settings->setValue(ksetusercelid, ui->lineEditUser->text());
			QString pwd = QString(QByteArray(ui->lineEditPassword->text().toLatin1()).toBase64());
			m_settings->setValue(ksetpassword, pwd);
		}

		QDialog::done(1);
	}
}

void DialogLogin::rememberPassword(){
	if (ui->checkBoxPassword->isChecked())
	{
		m_settings->setValue(ksetsavePwd, "1");
	}
	else{
		m_settings->setValue(ksetsavePwd, "0");
		m_settings->setValue(ksetusercelid, "");
		QString pwd = QString(QByteArray("").toBase64());
		m_settings->setValue(ksetpassword, pwd);
	}
}
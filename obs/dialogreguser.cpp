#include "dialogreguser.hpp"
#include "ui_dialogreguser.h"
#include <QMessageBox>
#include "obs-app.hpp"

DialogRegUser::DialogRegUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRegUser)
{
    ui->setupUi(this);

	ui->frame->setStyleSheet("background-color: white;border-style:outset;border-width:1px");

	QFont font;
	font.setPointSize(20);
	ui->labelTitle->setFont(font);
	ui->lineEditPassword->setEchoMode(QLineEdit::Password);
	ui->lineEditPassword_2->setEchoMode(QLineEdit::Password);

	ui->labelLogo->setPixmap(QPixmap(":/res/images/obs.png"));
	ui->labelLogo->setScaledContents(true);
	ui->labelLogo->setStyleSheet("background-color: transparent;border-style:none;");

	ui->lineEditUser->setFocus();

	connect(ui->toolButtonCode, SIGNAL(clicked()), SLOT(sms()));
}

DialogRegUser::~DialogRegUser()
{
    delete ui;
}

void DialogRegUser::done(int code){
	if (QDialog::Accepted == code){
		QRegExp telReg("(\\d{11})");
		QRegExp passwordReg(".+");
		if (!telReg.exactMatch(ui->lineEditUser->text())){
			QMessageBox::information(this,
				QTStr("Prompt"),
				QTStr("Error.UserName"));
		}
		else if (!passwordReg.exactMatch(ui->lineEditPassword->text()) || ui->lineEditPassword->text().compare(ui->lineEditPassword_2->text()) != 0 ){
			QMessageBox::information(this,
				QTStr("Prompt"),
				QTStr("Error.Password"));
		}
		else if (!passwordReg.exactMatch(ui->lineEditCode->text())){
			QMessageBox::information(this,
				QTStr("Prompt"),
				QTStr("Error.Sms"));
		}
		else{
			MBOService* mbo = new MBOService(this);
			connect(mbo, SIGNAL(callbackSignal(int, QString, QJsonValue)), SLOT(registerResult(int, QString, QJsonValue)));

			progressDialog = new WaitDialog(this);
			progressDialog->show();

			mbo->regUser(ui->lineEditUser->text(), ui->lineEditPassword->text(), ui->lineEditCode->text());
		}
	}
	else{
		QDialog::done(code);
	}
}

void DialogRegUser::sms(){
	QRegExp telReg("(\\d{11})");
	if (!telReg.exactMatch(ui->lineEditUser->text())){
		QMessageBox::information(this,
			QTStr("Prompt"),
			QTStr("Error.UserName"));
	}
	else{
        MBOService* mbo = new MBOService(this);
		connect(mbo, SIGNAL(callbackSignal(int, QString, QJsonValue)), SLOT(smsResult(int, QString, QJsonValue)));

        progressDialog = new WaitDialog(this);
        progressDialog->show();

        mbo->sms(ui->lineEditUser->text(), 1, "");
	}
}

void DialogRegUser::smsResult(int code, QString message, QJsonValue data)
{
	progressDialog->close();

	QMessageBox::information(this,
		QTStr("Prompt"),
		message);
}

void DialogRegUser::registerResult(int code, QString message, QJsonValue data)
{
	progressDialog->close();

	QMessageBox::information(this,
		QTStr("Prompt"),
		message);

	if (code == 0)
		close();
}
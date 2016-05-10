#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QJsonObject>
#include "mboservice.h"
#include "waitdialog.h"
#include <QSettings>

#define ksetsavePwd "savePwd"
#define ksetusercelid "usercelid"
#define ksetpassword "password"

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = 0);
    ~DialogLogin();

public slots:
	void done(int);
	void regUser();
	void resetPassword();
	void sendResult(int code, QString message, QJsonValue data);
	void rememberPassword();
private:
    Ui::DialogLogin *ui;
	WaitDialog* progressDialog;
	QSettings * m_settings;
};

#endif // DIALOGLOGIN_H

#ifndef DIALOGRESETPASSWORD_H
#define DIALOGRESETPASSWORD_H

#include <QDialog>
#include <QJsonObject>
#include "mboservice.h"
#include "waitdialog.h"

namespace Ui {
class DialogResetPassword;
}

class DialogResetPassword : public QDialog
{
    Q_OBJECT

public:
    explicit DialogResetPassword(QWidget *parent = 0);
    ~DialogResetPassword();

public slots:
	void done(int);
	void sms();
	void smsResult(int code, QString message, QJsonValue data);
	void sendResult(int code, QString message, QJsonValue data);
private:
    Ui::DialogResetPassword *ui;
	WaitDialog* progressDialog;
};

#endif // DIALOGRESETPASSWORD_H

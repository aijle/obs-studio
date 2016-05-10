#ifndef DIALOGREGUSER_H
#define DIALOGREGUSER_H

#include <QDialog>
#include <QJsonObject>
#include "mboservice.h"
#include "waitdialog.h"

namespace Ui {
class DialogRegUser;
}

class DialogRegUser : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRegUser(QWidget *parent = 0);
    ~DialogRegUser();

public slots:
	void done(int);
	void sms();
	void smsResult(int code, QString message, QJsonValue data);
	void registerResult(int code, QString message, QJsonValue data);
private:
    Ui::DialogRegUser *ui;
    WaitDialog* progressDialog;
};

#endif // DIALOGREGUSER_H

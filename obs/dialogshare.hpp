#ifndef DIALOGSHARE_H
#define DIALOGSHARE_H

#include <QDialog>
#include <QJsonObject>
#include "mboservice.h"
#include "waitdialog.h"
#include <QSettings>

#define ksetsavePwd "savePwd"
#define ksetusercelid "usercelid"
#define ksetpassword "password"

namespace Ui {
class DialogShare;
}

class DialogShare : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShare(QWidget *parent = 0);
    ~DialogShare();
	void showShare(QString url);
public slots:

private:
    Ui::DialogShare *ui;
	WaitDialog* progressDialog;
	QSettings * m_settings;
};

#endif // DIALOGSHARE_H

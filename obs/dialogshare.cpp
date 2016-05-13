#include "dialogshare.hpp"
#include "ui_dialogshare.h"
#include <QMessageBox>
#include "obs-app.hpp"
#include "dialogreguser.hpp"
#include "dialogresetpassword.hpp"
#include "appinfo.h"
//#include <QWebEngineView>

DialogShare::DialogShare(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShare)
{
    ui->setupUi(this);

	
}

DialogShare::~DialogShare()
{
    delete ui;
}

void DialogShare::showShare(QString url){
	//QWebEngineView *view = new QWebEngineView(this);
	//view->load(QUrl(url));
	//view->show();
	//ui->verticalLayout->addWidget(view);
	this->exec();
}
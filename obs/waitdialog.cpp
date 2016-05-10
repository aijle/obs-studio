#include "waitdialog.h"
#include "ui_waitdialog.h"
#include <Qmovie>

WaitDialog::WaitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitDialog)
{
    ui->setupUi(this);

	//this->setFixedSize(200, 200);
	setWindowOpacity(0.8); //ÉèÖÃÍ¸Ã÷ÓÃ£» 
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	//this->setContentsMargins(0, 0, 0, 0);

	QMovie* movie = new QMovie(":/res/images/loading.gif");
	ui->label->setScaledContents(true);
	ui->label->setStyleSheet("background-color: transparent;border-style:none;");
	ui->label->setMovie(movie);
	movie->start();
}

WaitDialog::~WaitDialog()
{
    delete ui;
}

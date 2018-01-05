#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QPixmap>
#include <QImage>
#include <QFile>

#include <QScopedPointer>

#include "optionsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_window_style();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_window_style()
{
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,
                    *(new QBrush(*(new QPixmap(":/images/Splash.png")))));

    this->setPalette(*palette);

    ui->centralWidget->setPalette(*palette);
}

void MainWindow::on_pushButtonQUIT_clicked()
{
    HoldButtons();
    this->close();
}

void MainWindow::on_pushButtonOPTIONS_clicked()
{
    HoldButtons();

    QScopedPointer<OptionsDialog> oDialog(new OptionsDialog(this));

    oDialog->showNormal();
    oDialog->exec();
}

void MainWindow::HoldButtons()
{
    ui->cbShowLog->setEnabled(false);

    ui->pushButtonPLAY->setEnabled(false);
    ui->pushButtonQUIT->setEnabled(false);
    ui->pushButtonOPTIONS->setEnabled(false);
}

void MainWindow::ReleaseButtons()
{
    ui->cbShowLog->setEnabled(true);

    ui->pushButtonPLAY->setEnabled(true);
    ui->pushButtonQUIT->setEnabled(true);
    ui->pushButtonOPTIONS->setEnabled(true);
}

void MainWindow::ReturnControl(){
    ReleaseButtons();
}

void MainWindow::on_pushButtonPLAY_clicked()
{
    HoldButtons();

    QProcess *process = new QProcess(this);
    QString app_ = "Game.exe ";//put your game bin file name here

    app_ += showLogWindow ? " -log" : "";

    try
    {
        if(process->startDetached(app_))
        {

        }
        else
        {
            //Something went wrong
        }
    } catch (...) {

    }

    ReleaseButtons();
    this->close();
}

void MainWindow::on_cbShowLog_toggled(bool checked)
{
    showLogWindow = checked;
}

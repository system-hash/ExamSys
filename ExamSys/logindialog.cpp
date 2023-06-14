#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QRegExp>
#include <QFile>
#include <QTextStream>

logindialog::logindialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::logindialog)
{
    ui->setupUi(this);
    ui->imgLabel->setScaledContents(true);
    resize(ui->imgLabel->width(),ui->imgLabel->height());
    setWindowTitle("驾校科目一考试登录");
    //linux默认
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    setFixedSize(width(),height());

}

logindialog::~logindialog()
{
    delete ui;
}


void logindialog::on_loginPushButton_clicked()
{
    QRegExp rx("^[A-Za-z0-9]+([_\.][A-Za-z0-9]+)*@([A-Za-z0-9\-]+\.)+[A-Za-z]{2,6}$");
    bool res = rx.exactMatch(ui->accountLineEdit->text());
    if(!res)
    {
        QMessageBox::information(this,"提示","邮箱地址格式错误，请检查邮箱地址!");
        ui->accountLineEdit->clear();
        ui->codeLineEdit->clear();
        ui->accountLineEdit->setFocus();
        return;
    }
    else
    {
        QString filename;
        QString strAccInput;
        QString strCode;
        QString strLine;
        QStringList strList;

        filename = "../account.txt";
        strAccInput = ui->accountLineEdit->text();
        strCode = ui->codeLineEdit->text();

        QFile file(filename);
        QTextStream stream(&file);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while (!stream.atEnd())
            {
                strLine = stream.readLine();
                strList = strLine.split(",");
                if(strAccInput == strList.at(0))
                    if(strCode == strList.at(1))
                    {
                        QMessageBox::information(this,"提示","欢迎进入科目一考试系统!");
                        file.close();
                        return;
                    }
                    else
                    {
                        QMessageBox::information(this,"提示","您输入的密码错误，请重新输入!");
                        ui->codeLineEdit->clear();
                        ui->codeLineEdit->setFocus();
                        file.close();
                        return;
                    }
            }
            QMessageBox::information(this,"提示","您输入的帐号错误，请重新输入!");
            ui->accountLineEdit->clear();
            ui->codeLineEdit->clear();
            ui->accountLineEdit->setFocus();
            file.close();
            return;
        }
        else
        {
            QMessageBox::information(this,"提示","读取帐号数据失败!");
            return;
        }
    }
}


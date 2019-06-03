#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    db(QSqlDatabase::addDatabase("QMYSQL"))
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(400,300);
    //设置标题
    this->setWindowTitle("教务管理系统");

    ui->rbtnStudent->setChecked(true);

    if(!database_connection())
    {
        QMessageBox::warning(this,"错误","打开数据库失败",QMessageBox::Ok,QMessageBox::NoButton);
    }

}

Login::~Login()
{
    delete ui;
}

bool Login::database_connection()
{
    db.setHostName(DB_HOSTNAME);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USERNAME);
    db.setPassword(DB_PASSWORD);


    if(db.open())
        return true;
    else
        return false;

}

//退出按钮
void Login::on_btnQuit_clicked()
{
    this->close();
}

//重置按钮
void Login::on_btnReset_clicked()
{
    ui->editPassword->clear();
    ui->editUsername->clear();
}

//登陆按钮
void Login::on_btnLogin_clicked()
{
    QString Id=ui->editUsername->text();
    QString Password=ui->editPassword->text();

    //管理员登陆
    if(ui->rbtnAdmin->isChecked())
    {
        if(match_name_password(Id,Password,"admin"))
        {
            qDebug()<<"管理员登陆成功";
            QMessageBox::information(this, "提示", "管理员登陆成功");
            this->hide();
            StuWindows *stu=new StuWindows;
            stu->show();
        }
        else
            QMessageBox::information(this, "警告", "用户名或密码错误");
    }

    //教师登陆
    if(ui->rbtnTeacher->isChecked())
    {
        if(match_name_password(Id,Password,"teacher"))
        {
            qDebug()<<"教师登陆成功";
            QMessageBox::information(this, "提示", "老师登陆成功");

            //暂时用学生的代替
            this->hide();
            StuWindows *stu=new StuWindows;
            stu->show();
            //接着做其他的事情
        }
        else
            QMessageBox::information(this, "警告", "用户名或密码错误");
    }

    //学生登陆
    if(ui->rbtnStudent->isChecked())
    {
        if(match_name_password(Id,Password,"student"))
        {
            qDebug()<<"学生登陆成功";
            QMessageBox::information(this, "提示", "学生登陆成功");

            //暂时用学生的代替
            this->hide();
            StuWindows *stu=new StuWindows;
            stu->show();
            //接着做其他的事情
        }
        else
            QMessageBox::information(this, "警告", "用户名或密码错误");
    }

}

bool Login::match_name_password(QString ID,QString PASSWORD,QString table)
{
    QString select="select id,password from ";
    QSqlQuery query(db);

    query.exec(select+table);
    bool flag=false;
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString password = query.value(1).toString();
        //qDebug() << id << password ;
        if(ID.compare(id)==0 && PASSWORD.compare(password)==0)
            flag=true;
    }
    return flag;
}







































#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/logo.png"));
    tcpsocket=nullptr;

    tcpsocket=new QTcpSocket(this);
    connect(tcpsocket,&QTcpSocket::connected,[=](){
        ui->TE_R->setText("服务器连接成功！");
    });

    connect(tcpsocket,&QTcpSocket::readyRead,[=](){
       //获取通信套接字的内容
        QString str=tcpsocket->readAll();
        //在显示编辑区域显示
       ui->TE_R->append("服务器端："+str);//不用settext 这样会覆盖之前的消息
    });
}

client::~client()
{
    delete ui;
}

void client::on_btn_connect_clicked()
{
    if(nullptr==ui->lE_IP || nullptr==ui->lE_Port)
        return ;
    //获取IP地址和端口号
    QString IP=ui->lE_IP->text();
    quint16 Port=ui->lE_Port->text().toInt();

    //与服务器连接
    tcpsocket->connectToHost(IP,Port);
}

void client::on_btn_send_clicked()
{
    if(nullptr==tcpsocket)//连接失败则不发送
        return;

    //获取发送的信息
    QString str=ui->TE_W->toPlainText();

    //将信息写入到通信套接字
    tcpsocket->write(str.toUtf8().data());

    //将自己的信息显示在聊天窗口
    ui->TE_R->append("客服端："+str);//不用settext 这样会覆盖之前的消息
}

void client::on_btn_close_clicked()
{
    if(nullptr==tcpsocket)
        return;
    tcpsocket->disconnectFromHost();//断开与服务器的连接
    tcpsocket->close();//关闭通信套接字
}

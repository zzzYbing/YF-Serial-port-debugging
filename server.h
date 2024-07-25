#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include<QTcpServer>//监听套接字
#include<QTcpSocket>//通信套接字

#include <QObject>

namespace Ui {
class server;
}

class server : public QWidget
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();

    QString str1;

private slots:
    void on_btn_send_clicked();

    void on_btn_close_clicked();

    void on_btn_ok_clicked();

private:
    Ui::server *ui;
    //声明两种套接字
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;

signals:
    void newMessageReceived(const QString &message);

};

#endif // SERVER_H

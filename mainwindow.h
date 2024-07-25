#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>			//访问串口的库
#include <QSerialPortInfo>		//查询串口信息的库
#include <QDebug>				//用于调试打印输出的库
#include <QTimer>				//定时器的库
#include <QTime>				//时间的库
#include <QDate>				//日期的库
#include <QMessageBox>			//一个小的弹窗库

#include <synchapi.h>
#include <QThread>

#include "client.h"
#include "server.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int btn_on_off = 0;

    int btn_state = 0;

private slots:

    void serialPortReadyRead();

    void serialPortWrite();

    //打开关闭串口
    void on_btn_open_close_clicked();
    //扫描串口
    void on_btn_scan_clicked();

    void on_btn_clear_rx_clicked();

    void on_btn_clear_tx_clicked();

    void on_btn_sent_clicked();

    //快捷指令：
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_19_clicked();

    void on_btn_M01_clicked();

    void on_btn_M02_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_btn_M07_clicked();

    //循环指令
    void on_pushButton_14_clicked();
    //停止循环
    void on_pushButton_15_clicked();

    void sendRepeatedCommand();


    void on_btn_server_clicked();

    void on_btn_client_clicked();

    void on_pushButton_16_clicked();

    void handleNewMessage(const QString &message);

    void on_pushButton_20_clicked();

private:
    Ui::MainWindow *ui;

    //定时器
    QTimer *timer;
    // 串口对象
    QSerialPort *serialport;

    //初始化
    void serialPortInit();

    QTimer *sendTimer;

    client c1;
    server s1;
};

#endif // MAINWINDOW_H

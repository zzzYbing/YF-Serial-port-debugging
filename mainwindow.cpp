#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //对象实例化
    serialport = new QSerialPort(this);
    this->setWindowIcon(QIcon(":/logo.png"));
    timer = new QTimer(this);

    on_btn_scan_clicked();

    connect(serialport,SIGNAL(readyRead()),this,SLOT(serialPortReadyRead()));
    //SIGNAL 是信号函数，QT的串口自带了
    //SLOT是自己定义的槽函数

    sendTimer = new QTimer(this);
    connect(sendTimer, &QTimer::timeout, this, &MainWindow::sendRepeatedCommand);

    connect(&s1, &server::newMessageReceived, this, &MainWindow::handleNewMessage);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialPortInit()
{
    //设置串口名称
   serialport->setPortName(ui->cbx_setPortName->currentText());
   qDebug()<<"串口名称:"<<serialport->portName();

   if (!serialport->open(QIODevice::ReadWrite))
   {
        qDebug()<<"错误，串口无法打开，可能被占用！";
        QMessageBox::about(this,"错误","串口无法打开，可能被占用！");
        serialport->close();
        return ;
   }

    //波特率
    serialport->setBaudRate(ui->cbx_setBaudRate->currentText().toInt());
    qDebug()<<"波特率:"<<ui->cbx_setBaudRate->currentText().toInt();
    //停止位
    switch (ui->cbx_setStopBits->currentText().toInt())
    {
    case 1 :  serialport->setStopBits(QSerialPort::OneStop); break;
    case 2 :  serialport->setStopBits(QSerialPort::TwoStop); break;
        default: break;
    }
    qDebug()<<"停止位:"<<serialport->stopBits();
    //数据位
    switch (ui->cbx_setDataBits->currentText().toInt())
    {
    case 5 :  serialport->setDataBits(QSerialPort::Data5); break;
    case 6 :  serialport->setDataBits(QSerialPort::Data6); break;
    case 7 :  serialport->setDataBits(QSerialPort::Data7); break;
    case 8 :  serialport->setDataBits(QSerialPort::Data8); break;
        default: break;
    }
    //奇偶位
     switch (ui->cbx_setParity->currentIndex())
    {
    case 0 :  serialport->setParity(QSerialPort::NoParity); break;
    case 1 :  serialport->setParity(QSerialPort::OddParity); break;
    case 2 :  serialport->setParity(QSerialPort::EvenParity); break;
        default: break;
    }
    qDebug()<<"奇偶位:"<<serialport->parity();

    serialport->setFlowControl(QSerialPort::NoFlowControl) ;


}

void MainWindow::on_btn_open_close_clicked()
{
    if (btn_on_off == 0)
    {

        ui->cbx_setPortName->setEnabled(false);
        ui->cbx_setBaudRate->setEnabled(false);
        ui->cbx_setDataBits->setEnabled(false);
        ui->cbx_setStopBits->setEnabled(false);
        ui->cbx_setParity->setEnabled(false);
        ui->btn_open_close->setText("关闭串口");
        qDebug()<<"打开串口:";
        serialPortInit();
    }

   if (btn_on_off == 1)
   {

       serialport->close();
       ui->cbx_setPortName->setEnabled(true);
       ui->cbx_setBaudRate->setEnabled(true);
       ui->cbx_setDataBits->setEnabled(true);
       ui->cbx_setStopBits->setEnabled(true);
       ui->cbx_setParity->setEnabled(true);
       ui->btn_open_close->setText("打开串口");
       qDebug()<<"串口关闭";
   }
   btn_on_off = !btn_on_off;
}

void MainWindow::on_btn_scan_clicked()
{

    ui->cbx_setPortName->clear();//清除选择串口下拉栏添加的所有项目
    //查询可用的串口信息
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        {
            //添加串口到下拉菜单
             ui->cbx_setPortName->addItem(info.portName());
        }
        qDebug()<<"已发现串口："<<ui->cbx_setPortName->currentText();
    }
}

void MainWindow::serialPortReadyRead()
{
    QByteArray temp = serialport->readAll();
    QString str = ui->textEdit_rx->toPlainText();
    str =  QString::fromLocal8Bit(temp);//显示中文
    ui->textEdit_rx->append(str);
}

void MainWindow::serialPortWrite()
{
    QByteArray buff;
    //判断是否非空
    if(!ui->textEdit_tx->toPlainText().isEmpty())
    {
        buff = ui->textEdit_tx->toPlainText().toLocal8Bit() + "\r\n";//可以写中文
        serialport->write(buff);
    }
}

void MainWindow::on_btn_clear_rx_clicked()
{
    ui->textEdit_rx->clear();
}

void MainWindow::on_btn_clear_tx_clicked()
{
    ui->textEdit_tx->clear();
}

void MainWindow::on_btn_sent_clicked()
{
    serialPortWrite();
}


void MainWindow::on_pushButton_19_clicked()
{
    QByteArray buff;
    buff = "Q01\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray buff;
    buff = "Q02\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_2_clicked()
{
    QByteArray buff;
    buff = "Q04\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_4_clicked()
{
    QByteArray buff;
    buff = "Q05\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_3_clicked()
{
    QByteArray buff;
    buff = "Q06\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_6_clicked()
{
    QByteArray buff;
    buff = "S04\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_7_clicked()
{
    QByteArray buff;
    buff = "S07 0\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_18_clicked()
{
    QByteArray buff;
    buff = "M03\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_5_clicked()
{
    QByteArray buff;
    buff = "M04\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_17_clicked()
{
    QByteArray buff;
    buff = "M05\r\n";
    serialport->write(buff);
}

void MainWindow::on_pushButton_20_clicked()
{
    QByteArray buff;
    buff = "S15 2\r\n";
    serialport->write(buff);
}

void MainWindow::on_btn_M02_clicked()
{
    QByteArray buff;
    //判断是否非空
    if(!ui->textEdit_M01_X->toPlainText().isEmpty()&&!ui->textEdit_M01_Y->toPlainText().isEmpty()&&!ui->textEdit_M01_Z->toPlainText().isEmpty())
    {
        QByteArray X = ui->textEdit_M01_X->toPlainText().toLocal8Bit();
        QByteArray Y = ui->textEdit_M01_Y->toPlainText().toLocal8Bit();
        QByteArray Z = ui->textEdit_M01_Z->toPlainText().toLocal8Bit();

        buff = "M02 " + X + " " + Y + " " + Z + " 0 0 0\r\n";
        serialport->write(buff);
    }
}



void MainWindow::on_pushButton_8_clicked()
{
    QByteArray buff;

    if(!ui->textEdit_joint_1->toPlainText().isEmpty())
    {
        double a = ui->textEdit_joint_1->toPlainText().toLocal8Bit().toDouble();
        a = a * 100;
        QByteArray joint = QByteArray::number(a);
        buff = "M06 0 " + joint + " 0 0 0 0\r\n";
        serialport->write(buff);
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    QByteArray buff;

    if(!ui->textEdit_joint_2->toPlainText().isEmpty())
    {
        double a = ui->textEdit_joint_2->toPlainText().toLocal8Bit().toDouble();
        a = a * 100;
        QByteArray joint = QByteArray::number(a);
        buff = "M06 1 " + joint + " 0 0 0 0\r\n";
        serialport->write(buff);
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    QByteArray buff;

    if(!ui->textEdit_joint_3->toPlainText().isEmpty())
    {
        double a = ui->textEdit_joint_3->toPlainText().toLocal8Bit().toDouble();
        a = a * 100;
        QByteArray joint = QByteArray::number(a);
        buff = "M06 2 " + joint + " 0 0 0 0\r\n";
        serialport->write(buff);
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    QByteArray buff;

    if(!ui->textEdit_joint_4->toPlainText().isEmpty())
    {
        double a = ui->textEdit_joint_4->toPlainText().toLocal8Bit().toDouble();
        a = a * 100;
        QByteArray joint = QByteArray::number(a);
        buff = "M06 3 " + joint + " 0 0 0 0\r\n";
        serialport->write(buff);
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    QByteArray buff;

    if(!ui->textEdit_joint_5->toPlainText().isEmpty())
    {
        double a = ui->textEdit_joint_5->toPlainText().toLocal8Bit().toDouble();
        a = a * 100;
        QByteArray joint = QByteArray::number(a);
        buff = "M06 4 " + joint + " 0 0 0 0\r\n";
        serialport->write(buff);
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    QByteArray buff;

    if(!ui->textEdit_joint_6->toPlainText().isEmpty())
    {
        double a = ui->textEdit_joint_6->toPlainText().toLocal8Bit().toDouble();
        a = a * 100;
        QByteArray joint = QByteArray::number(a);
        buff = "M06 5 " + joint + " 0 0 0 0\r\n";
        serialport->write(buff);
    }
}


void MainWindow::on_btn_M01_clicked()
{
    QByteArray buff;
    if(!ui->textEdit_joint_1->toPlainText().isEmpty()&&!ui->textEdit_joint_2->toPlainText().isEmpty()&&!ui->textEdit_joint_3->toPlainText().isEmpty()/*&&!ui->textEdit_joint_4->toPlainText().isEmpty()&&!ui->textEdit_joint_5->toPlainText().isEmpty()&&!ui->textEdit_joint_6->toPlainText().isEmpty()*/)
    {
        double a = ui->textEdit_joint_1->toPlainText().toLocal8Bit().toDouble();
        double b = ui->textEdit_joint_2->toPlainText().toLocal8Bit().toDouble();
        double c = ui->textEdit_joint_3->toPlainText().toLocal8Bit().toDouble();

        a *= 100;
        b *= 100;
        c *= 100;

        QByteArray A = QByteArray::number(a);
        QByteArray B = QByteArray::number(b);
        QByteArray C = QByteArray::number(c);

        buff = "M01 " + A + " " + B + " " + C + " 4 5 6\r\n";
        serialport->write(buff);
    }

}

void MainWindow::on_btn_M07_clicked()
{
    QByteArray buff;
    //判断是否非空
    if(!ui->textEdit_M07_end_X->toPlainText().isEmpty()&&!ui->textEdit_M07_end_Y->toPlainText().isEmpty()&&!ui->textEdit_M07_end_Z->toPlainText().isEmpty()&&!ui->textEdit_M07_mid_X->toPlainText().isEmpty()&&!ui->textEdit_M07_mid_Y->toPlainText().isEmpty()&&!ui->textEdit_M07_mid_Z->toPlainText().isEmpty())
    {
        QByteArray end_X = ui->textEdit_M07_end_X->toPlainText().toLocal8Bit();
        QByteArray end_Y = ui->textEdit_M07_end_Y->toPlainText().toLocal8Bit();
        QByteArray end_Z = ui->textEdit_M07_end_Z->toPlainText().toLocal8Bit();
        QByteArray mid_X = ui->textEdit_M07_mid_X->toPlainText().toLocal8Bit();
        QByteArray mid_Y = ui->textEdit_M07_mid_Y->toPlainText().toLocal8Bit();
        QByteArray mid_Z = ui->textEdit_M07_mid_Z->toPlainText().toLocal8Bit();

        buff = "M07 " + mid_X + " " + mid_Y + " " + mid_Z + " " + end_X + " " + end_Y + " " +end_Z + "\r\n";
        serialport->write(buff);
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    qDebug() << "loopsend start";
    int interval = 100; // 发送间隔，单位毫秒
    sendTimer->start(interval);

}

void MainWindow::sendRepeatedCommand()
{
    qDebug() << "write data";
    serialport->write("M16\r\n");
    if(!serialport->waitForBytesWritten())
    {
        qDebug() << "serial write error";
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    sendTimer->stop();
    qDebug() << "loopsend stop";
}



void MainWindow::on_btn_server_clicked()
{
    s1.show();
}

void MainWindow::on_btn_client_clicked()
{
    c1.show();
}

void MainWindow::on_pushButton_16_clicked()
{
    QByteArray buff = s1.str1.toUtf8() + "\r\n";

    serialport->write(buff);
}

void MainWindow::handleNewMessage(const QString &message)
{

//    QByteArray buff = message.toUtf8() + "\r\n";
//    serialport->write(buff);

    QStringList parts = message.split(',');
    if (parts.size() == 4) {
        double X = parts.at(0).toDouble()*100;
        double Y = parts.at(1).toDouble()*100;
        double Z = parts.at(2).toDouble()*100;
        double RZ = parts.at(3).toDouble()*100;
        qDebug()<<X<<Y<<Z<<RZ;

        QByteArray x = QByteArray::number(X);
        QByteArray y = QByteArray::number(Y);
        QByteArray z = QByteArray::number(Z);
        QByteArray rz = QByteArray::number(RZ);

        QByteArray buff = "M02 " + x + " " + y + " " + z + " " + rz + " 0 0\r\n";

        serialport->write(buff);
        qDebug() << "串口发送消息：" << buff;
    }
    else{
        qDebug() << "Received message does not contain exactly 4 parts.";
    }
}



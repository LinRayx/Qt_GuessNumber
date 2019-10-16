#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QStackedWidget>
#include <QKeyEvent>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->grabKeyboard();
    this->setStyleSheet("#MyWidget{border-image:url(:/new/prefix1/bimageblack.jpg);}");
    ui->stackedWidget->setStyleSheet("#stackedWidget{border-image:url(:/new/prefix1/bimageblack.jpg);}");
    ui->stackedWidget->setCurrentIndex(0);
    // 设置标题
    ui->Titlelabel->setText("<center><h1>猜数字游戏</h1></center>");

    // 设置时间选择文本
    ui->TimeSelectlabel->setText("<center><h3>选择时间:</h3></center>");

    // 设置时间复选框
    for(int i = 10; i <= 100; i += 10) {
        ui->TimecomboBox->addItem(QString(QString::number(i)));
    }
    // 进入游戏按钮事件
    connect(ui->EnterpushButton, &QPushButton::clicked, this, &MyWidget::enterSlot);
    // 退出游戏按钮事件
    connect(ui->QuitpushButton, &QPushButton::clicked, this, &QWidget::close);

    // 设置游戏界面
    ui->Residuelabel->setText(QString("<center><h3>剩余时间:</h3></center>"));

    // 输入数字事件
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MyWidget::addStr);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MyWidget::addStr);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MyWidget::addStr);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MyWidget::addStr);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MyWidget::addStr);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MyWidget::addStr);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MyWidget::addStr);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MyWidget::addStr);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MyWidget::addStr);



    // 退格事件
    connect(ui->CancelpushButton_, &QPushButton::clicked, this, &MyWidget::deloneChar);
    // 提交事件
    connect(ui->SubmitpushButton, &QPushButton::clicked, this, &MyWidget::judge);


}

MyWidget::~MyWidget()
{
    delete ui;
}
// 初始化游戏
void MyWidget::enterSlot() {
//    qDebug() << "...." ;
    // 获取所选的时间
    this->gameTime = ui->TimecomboBox->currentText().toInt();

    // 设置剩余秒数
    ui->Secondlabel->setText(QString("%1秒").arg(gameTime));
    // 设置进度条
    ui->TimeprogressBar->setMaximum(gameTime);
    ui->TimeprogressBar->setMinimum(0);
    ui->TimeprogressBar->setValue(gameTime);
    // 1s启动一次定时器
    barTimerId = this->startTimer(1000);
    qsrand(time(0));
    int num = 0;
    ui->Infolabel->clear();
    ui->stackedWidget->setCurrentIndex(1);
    while((num = qrand())% 10000 < 999);
    randStr = QString::number(num);

    qDebug() << randStr;
}

void MyWidget::timerEvent(QTimerEvent *e) {
    if(e->timerId() == barTimerId) {
        gameTime--;
        if(gameTime == 0) {
            ui->TimeprogressBar->setValue(gameTime);
            ui->Secondlabel->setText(QString("%1秒").arg(gameTime));
            this->killTimer(barTimerId);
            enterLoseImage();

        } else {
            ui->TimeprogressBar->setValue(gameTime);
            ui->Secondlabel->setText(QString("%1秒").arg(gameTime));
        }
    }
    if(e->timerId() == imageTimerId) {
        this->imageTime -= 1000;
        if(this->imageTime == 0) {
            ui->stackedWidget->setCurrentIndex(0);
            this->killTimer(this->imageTimerId);
        }
//        qDebug() << imageTime;
    }
}

void MyWidget::addStr() {
    QPushButton* ev = static_cast<QPushButton*>(sender());
    QString button = ev->objectName();
    if(guessStr.size() == 0 && button[button.size()-1] == '0')
        return;
    this->guessStr += button[button.size()-1];
//    qDebug() << this->guessStr;
    ui->Infolabel->setText("<center><h3>"+guessStr+"</h3></center>");
}

void MyWidget::deloneChar() {
    if(this->guessStr.size() > 0)
        this->guessStr.chop(1);
//    qDebug() << this->guessStr;
    ui->Infolabel->setText("<center><h3>"+guessStr+"</h3></center>");
}

void MyWidget::judge() {
    if(guessStr.size() == 0) {
        ui->Infolabel->setText("<center><h3>请先输入数字！</h3></center>");
        return;
    }
    // 猜大了
    if(randStr.size() < guessStr.size() ) {
        Bigger();
    } else if(randStr.size() > guessStr.size()) {

        Smaller();
    } else {
        if(randStr == guessStr) {
            Match();
        } else if(randStr < guessStr) {
            Bigger();
        } else {
            Smaller();

        }
    }
}

void MyWidget::Smaller() {
    QString info("<center><h2>%1猜的太小啦！</h2></center>");
    info = info.arg(guessStr);
    ui->Infolabel->setText(info);
}

void MyWidget::Bigger() {
    QString info("<center><h2>%1猜的太大啦！</h2></center>");
    info = info.arg(guessStr);
    ui->Infolabel->setText(info);
}

void MyWidget::Match() {
    this->killTimer(barTimerId);
    int ret = QMessageBox::question(this, "恭喜","恭喜你猜对啦！", QMessageBox::Ok);
    if(ret == QMessageBox::Ok) {
        enterWinImage();
    }

}

void MyWidget::enterWinImage() {

    ui->stackedWidget->setCurrentIndex(2);
    ui->imageLabel->setPixmap(QPixmap(":/new/prefix1/win.jpeg"));
    ui->imageLabel->setScaledContents(true);
    this->imageTime = 3000;
    this->imageTimerId = this->startTimer(1000);
}

void MyWidget::enterLoseImage() {
    ui->stackedWidget->setCurrentIndex(2);
    ui->imageLabel->setPixmap(QPixmap(":/new/prefix1/lose.jpeg"));
    ui->imageLabel->setScaledContents(true);
//    ui->imageLabel->resize(ui->stackedWidget->width(), ui->stackedWidget->height());
    this->imageTime = 3000;
    this->imageTimerId = this->startTimer(1000);
}
void MyWidget::keyAddStr(int val) {
    if(guessStr.size() == 0 && val == 0)
        return;
    guessStr += QString::number(val);
    ui->Infolabel->setText("<center><h3>"+guessStr+"</h3></center>");
}
void MyWidget::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_0) {
       keyAddStr(0);
    }
    if(e->key() == Qt::Key_1) {
        keyAddStr(1);
    }
    if(e->key() == Qt::Key_2) {
        keyAddStr(2);
    }
    if(e->key() == Qt::Key_3) {
        keyAddStr(3);
    }
    if(e->key() == Qt::Key_4) {
        keyAddStr(4);
    }
    if(e->key() == Qt::Key_5) {
        keyAddStr(5);
    }
    if(e->key() == Qt::Key_6) {
        keyAddStr(6);
    }
    if(e->key() == Qt::Key_7) {
        keyAddStr(7);
    }
    if(e->key() == Qt::Key_8) {
        keyAddStr(8);
    }
    if(e->key() == Qt::Key_9) {
        keyAddStr(9);
    }
    if(e->key() == Qt::Key_Backspace) {
        deloneChar();
    }
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
//        qDebug() << 111;
        judge();
    }
}

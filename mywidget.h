#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
protected:
    void enterSlot();
    void timerEvent(QTimerEvent*);
    void addStr();
    void deloneChar();
    void judge();
    void Smaller();
    void Bigger();
    void Match();
    void enterWinImage();
    void enterLoseImage();
    void keyPressEvent(QKeyEvent *event);
    void keyAddStr(int val);
private:
    Ui::MyWidget *ui;
    int gameTime;
    int barTimerId;
    int imageTimerId;
    int imageTime;
    QString guessStr;
    QString randStr;
};
#endif // MYWIDGET_H

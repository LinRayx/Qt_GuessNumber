# 猜数字游戏
dmg下载地址: [https://github.com/LinRayx/Qt_GuessNumber/raw/master/GuessNumber.dmg](https://github.com/LinRayx/Qt_GuessNumber/raw/master/GuessNumber.dmg)

代码地址: [https://github.com/LinRayx/Qt_GuessNumber](https://github.com/LinRayx/Qt_GuessNumber)

博客地址: http://106.15.249.102/cai-shu-zi-you-xi/
![-w800](http://106.15.249.102/wp-content/uploads/2019/10/15712386125962.jpg)
![-w800](http://106.15.249.102/wp-content/uploads/2019/10/15712386202735.jpg)
![-w800](http://106.15.249.102/wp-content/uploads/2019/10/15712386307329.jpg)


## 主要功能：
登陆界面选择游戏时间，然后进入游戏界面，首先随机产生一个数字，游戏界面有一个进度条代表剩余多少时间。同时游戏界面还有一个信息窗口，表示每次猜测的结果。并显示每次猜测的数字。同时也需要按钮来输入每次猜测的数字。
猜测正确或者游戏结束跳到相应的界面。

## 界面结构
一个StackWidget的界面容器，包含三个页
1. 开始页 0
2. 游戏页 1
3. 结果页 2
    1. 胜利画面
    2. 失败画面

## 头文件参数和方法
游戏时间，进度条计时器，结果图片计时器，结果图片，猜测数字，随机产生的数字

参数:
```cpp
    int gameTime;
    int barTimerId;
    int imageTimerId;
    int imageTime;
    QString guessStr;
    QString randStr;
    
```
槽函数/方法
```cpp
    void enterSlot();                // 开始游戏
    void timerEvent(QTimerEvent*);   // 计时器事件
    void addStr();                   // 输入数字添加进字符串
    void deloneChar();               // 从字符串删除一个数字
    void judge();                    // 判断猜测数字
    void Smaller();                  // 猜小了
    void Bigger();                   // 猜大了
    void Match();                    // 猜对了
    void enterWinImage();            // 胜利画面
    void enterLoseImage();           // 失败画面
    void keyPressEvent(QKeyEvent *event); // 键盘事件
    void keyAddStr(int val);         // 键盘输入
```
## 流程:
进入游戏->开始倒计时->进行输入猜测->时间到|猜测正确->结果画面    
    
## 键盘输入
重载 void keyPressEvent(QKeyEvent *event);
## 定义计时器
重载 void timerEvent(QTimerEvent*);
int timerId = this->startTimer(1000);

设置唤醒间隔是1000ms，会触发timerEvent函数，返回一个计时器id。
使用完需要this->killTimer(timerId)

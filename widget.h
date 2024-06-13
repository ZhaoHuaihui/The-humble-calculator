#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void setNum(QString n);
    void setOpt(QString opt);
    void clickedBackButton();

private:
    Ui::Widget *ui;

    //第一个操作数
    QString num1;
    // 保存运算符
    QString opt;
    // 第二个操作数
    QString num2;
    // 运算结果
    double result;
};

#endif // WIDGET_H

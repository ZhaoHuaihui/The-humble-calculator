#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("计算器");
    this->setFixedSize(506, 640);

    // 数字按钮
    connect(ui->btn0, &QPushButton::clicked, [this](){this->setNum("0");});
    connect(ui->btn1, &QPushButton::clicked, [this](){this->setNum("1");});
    connect(ui->btn2, &QPushButton::clicked, [this](){this->setNum("2");});
    connect(ui->btn3, &QPushButton::clicked, [this](){this->setNum("3");});
    connect(ui->btn4, &QPushButton::clicked, [this](){this->setNum("4");});
    connect(ui->btn5, &QPushButton::clicked, [this](){this->setNum("5");});
    connect(ui->btn6, &QPushButton::clicked, [this](){this->setNum("6");});
    connect(ui->btn7, &QPushButton::clicked, [this](){this->setNum("7");});
    connect(ui->btn8, &QPushButton::clicked, [this](){this->setNum("8");});
    connect(ui->btn9, &QPushButton::clicked, [this](){this->setNum("9");});
    connect(ui->pointBtn, &QPushButton::clicked, [this](){this->setNum(".");});

    // 加减乘除
    connect(ui->addBtn, &QPushButton::clicked, [this](){this->setOpt("+");});
    connect(ui->subBtn, &QPushButton::clicked, [this](){this->setOpt("-");});
    connect(ui->mulBtn, &QPushButton::clicked, [this](){this->setOpt("*");});
    connect(ui->divBtn, &QPushButton::clicked, [this](){this->setOpt("÷");});

    // 删除
    connect(ui->backBtn, &QPushButton::clicked, [this](){this->clickedBackButton();});

    // 清空
    connect(ui->clsBtn, &QPushButton::clicked, [this](){
        this->num1 = "";
        this->num2 = "";
        this->opt = "";
        ui->lineEdit->setText("");
    });

    // 等号
    connect(ui->equalBtn, &QPushButton::clicked, [this](){
        if (this->opt == "+")
        {
            this->result = this->num1.toDouble() + this->num2.toDouble();
        }
        else if (this->opt == "-")
        {
            this->result = this->num1.toDouble() - this->num2.toDouble();
        }
        else if (this->opt == "*")
        {
            this->result = this->num1.toDouble() * this->num2.toDouble();
        }
        else if (this->opt == "÷")
        {
            this->result = this->num1.toDouble() / this->num2.toDouble();
        }

        ui->lineEdit->setText(QString::number(this->result));

        // 为了能实现连续运算，将结果转存到num1中；同时要将num2清空
        this->num1 = QString::number(this->result);
        this->num2 = "";
    });
}

// 对.的特殊处理
// 1.当屏幕为空时，不能输入.
// 2.当屏幕中已经有.的时候就不能再输入.
// 使用字符串相关的函数即可
void Widget::setNum(QString n)
{
    if (n == "." && (ui->lineEdit->text().indexOf(".") != -1 || ui->lineEdit->text().isEmpty()))
    {
        return;
    }
    if (n == "0" && ui->lineEdit->text().isEmpty())
    {
        return;
    }
    if (this->opt.isEmpty())
    {
        // 为空，设置第一个操作数
        this->num1 += n;
        ui->lineEdit->setText(this->num1);
    }
    else
    {
        // 不为空，设置第二个操作数
        this->num2 += n;
        ui->lineEdit->setText(this->num2);
    }
}

void Widget::clickedBackButton()
{
    if (this->opt.isEmpty())
    {
        this->num1.chop(1);
        ui->lineEdit->setText(num1);
    }
    else
    {
        this->num2.chop(1);
         ui->lineEdit->setText(num2);
    }
}

void Widget::setOpt(QString opt)
{
    // 保存运算符
    this->opt = opt;
    // 清空屏幕
    ui->lineEdit->setText("");
}

Widget::~Widget()
{
    delete ui;
}

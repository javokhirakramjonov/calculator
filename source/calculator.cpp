#include "calculator.h"
#include "ui_calculator.h"

double fulval = 0;
bool divTrigger = false;
bool mulTrigger = false;
bool subTrigger = false;
bool addTrigger = false;
bool perTrigger = false;
bool eq = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(fulval));

    QPushButton *numButtons[11];

    numButtons[10] = Calculator::findChild<QPushButton *>("dot");
    connect(numButtons[10], SIGNAL(released()), this, SLOT(numpr()));

    for(int i = 0; i < 10; ++ i)
    {
        QString butName = "num" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(numpr()));
    }
    connect(ui->plus, SIGNAL(released()), this,
            SLOT(mathpr()));
    connect(ui->minus, SIGNAL(released()), this,
            SLOT(mathpr()));
    connect(ui->multiple, SIGNAL(released()), this,
            SLOT(mathpr()));
    connect(ui->divide, SIGNAL(released()), this,
            SLOT(mathpr()));
    connect(ui->percent, SIGNAL(released()), this,
            SLOT(perpr()));
    connect(ui->equal, SIGNAL(released()), this,
            SLOT(equalpr()));
    connect(ui->back, SIGNAL(released()), this,
            SLOT(delpr()));
    connect(ui->clear, SIGNAL(released()), this,
            SLOT(delpr()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numpr()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if(eq)
    {
        eq = false;
        displayVal = "0";
    }
    if((displayVal == "0" || displayVal == "0.0") && butVal != ".")
    {
        ui->Display->setText(butVal);
    }
    else
    {
        bool isDot = false;
        QString newValue = displayVal + butVal;
        for(QChar c : qAsConst(displayVal))
            if(c == '.')
                isDot = true;
        if((isDot == true && butVal == ".") == false)
            ui->Display->setText(newValue);
    }
}

void Calculator::mathpr()
{
    QString displayVal = ui->Display->text();
    if(!(divTrigger || mulTrigger || subTrigger || addTrigger))
    {
        fulval = displayVal.toDouble();
    }
    gofalse();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        mulTrigger = true;
    }
    else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::equalpr()
{
    bool iszero = false;
    double sol = fulval;
    QString diVal = ui->Display->text();
    double curval = diVal.toDouble();
    if(addTrigger || subTrigger || divTrigger || mulTrigger)
    {
        if(addTrigger)
        {
            sol = fulval + curval;
        }
        else if(subTrigger)
        {
            sol = fulval - curval;
        }
        else if(divTrigger)
        {
            if(curval == 0)
                iszero = true;
            else
                sol = fulval / curval;
        }
        else if(mulTrigger)
        {
            sol = fulval * curval;
        }
    }
    fulval = sol;
    if(iszero)
    {
        ui->Display->setText("ERROR");
        fulval = 0;
    }
    else
    {
        ui->Display->setText(QString::number(sol));
    }
    eq = true;
    gofalse();
}

void Calculator::perpr()
{
    QString disv = ui->Display->text();
    double sol = 0;
    if(disv == "")
        sol = fulval / 100.0;
    else
        sol = disv.toDouble() / 100.0;
    ui->Display->setText(QString::number(sol));
}

void Calculator::delpr()
{
    QPushButton *button = (QPushButton *)sender();
    QString name = button->text();
    QString num = QString::number(fulval);
    if(QString::compare(name, "C", Qt::CaseInsensitive) == 0)
        num = "0";
    else
        num.remove(num.size() - 1, 1);
    if(QString::compare(num, "", Qt::CaseInsensitive) == 0)
        num = "0";
    fulval = num.toDouble();
    ui->Display->setText(num);
}

void Calculator::gofalse()
{
    divTrigger = false;
    mulTrigger = false;
    subTrigger = false;
    addTrigger = false;
}

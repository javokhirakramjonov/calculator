#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
private slots:
    void numpr();
    void mathpr();
    void equalpr();
    void perpr();
    void delpr();
    void gofalse();
    void on_save_triggered();
};
#endif // CALCULATOR_H

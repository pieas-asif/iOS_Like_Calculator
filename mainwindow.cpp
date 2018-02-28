#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNum;
double lastNum;
bool secNumTyping = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_zero,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_one,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_two,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_three,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_four,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_five,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_six,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_seven,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_eight,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_nine,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_plusMinus,SIGNAL(released()),this,SLOT(unary_oparetor_pressed()));
    connect(ui->pushButton_percentage,SIGNAL(released()),this,SLOT(unary_oparetor_pressed()));

    connect(ui->pushButton_plus,SIGNAL(released()),this,SLOT(binary_oparetion_pressed()));
    connect(ui->pushButton_minus,SIGNAL(released()),this,SLOT(binary_oparetion_pressed()));
    connect(ui->pushButton_product,SIGNAL(released()),this,SLOT(binary_oparetion_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_oparetion_pressed()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_product->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() || ui->pushButton_product->isChecked() || ui->pushButton_divide->isChecked()) && !secNumTyping) {
        labelNumber = (button->text()).toDouble();
        secNumTyping = true;
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    else {
        if(ui->label->text().contains(".") && button->text() == "0") {
            newLabel = ui->label->text() + button->text();
        }
        else {
            labelNumber = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
        }
    }

    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_dot_released()
{
    if(!ui->label->text().count(QLatin1Char('.'))) {
        ui->label->setText(ui->label->text() + ".");
    }
}

void MainWindow::unary_oparetor_pressed()
{
    double labelNumber;
    QPushButton * button = (QPushButton*)sender();
    QString newLabel;

    if(button->text() == "+/-") {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }

    if(button->text() == "%") {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
}

void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_product->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    secNumTyping = false;
    ui->label->setText("0");
}

void MainWindow::on_pushButton_equal_released()
{
    double labelNumber;
    QString newLabel;

    lastNum = ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked()) {
        labelNumber = firstNum + lastNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }

    else if(ui->pushButton_minus->isChecked()) {
        labelNumber = firstNum - lastNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_minus->setChecked(false);
    }

    else if(ui->pushButton_product->isChecked()) {
        labelNumber = firstNum * lastNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_product->setChecked(false);
    }

    else if(ui->pushButton_divide->isChecked()) {
        labelNumber = firstNum / lastNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
    }

    secNumTyping = false;
}

void MainWindow::binary_oparetion_pressed()
{
    QPushButton * button = (QPushButton*)sender();


    firstNum = ui->label->text().toDouble();


    button->setChecked(true);
}

#include "mainwindow.h"
#include <QSignalMapper>
#include <QMessageBox>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow){
        ui->setupUi(this);

        this->setWindowTitle("Ведомость приема и отгрузки товаров");
        QRect rect = frameGeometry();
        rect.moveCenter(QDesktopWidget().availableGeometry().center());
        move(rect.topLeft());
        this->setGeometry(rect);

        // Переопределение сигнала окончания ввода, связывание с функцией поиска
        QSignalMapper *pSigMap = new QSignalMapper(this);
        connect(pSigMap, SIGNAL(mapped(QWidget*)), this, SLOT(showSignal(QWidget*)));
        connect(ui->lineEdit_in, SIGNAL(returnPressed()), pSigMap, SLOT(map()));
        connect(ui->lineEdit_out, SIGNAL(returnPressed()), pSigMap, SLOT(map()));
        pSigMap->setMapping(ui->lineEdit_in, ui->lineEdit_in);
        pSigMap->setMapping(ui->lineEdit_out, ui->lineEdit_out);

        // Установка верхнего регистра ввода
        QFont f;
        f.setCapitalization(QFont::AllUppercase);

        // ограничение формата ввода - 24-значные HEX-символы разделенные пробелом
        // либо только символы без пробела, либо с пробела начинается новое слово
        QRegExp rExp("("
                         "([0-9,a-f,A-F]{24})|"
                         "(([0-9,a-f,A-F]{24})(\\s([0-9,a-f,A-F]{24}))+)"
                         ")");
        QValidator *vld = new QRegExpValidator(rExp, this);

        initWindow(ui->treeWidget_in, ui->lineEdit_in, f, vld);
        initWindow(ui->treeWidget_out, ui->lineEdit_out, f, vld);
}

void MainWindow::initWindow(QTreeWidget *treeWidget, QLineEdit *lineEdit, QFont &f, QValidator *vld){
    // установка сортировки по возрастанию столбец "Наименование"
        treeWidget->setSortingEnabled(true);
        treeWidget->sortByColumn(0, Qt::AscendingOrder);
    //  установка ширины столбцов
        treeWidget->header()->setStretchLastSection(false);
        treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);
        treeWidget->header()->setSectionResizeMode(1, QHeaderView::Custom);
        treeWidget->setColumnWidth(1, 90);
    // Установка верхнего регистра ввода
        lineEdit->setFont(f);
    // установка подсказки для формата ввода данных
        lineEdit->setPlaceholderText("304DB75F196000180001C13A");
    // установка правил ввода
        lineEdit->setValidator(vld);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clear_pressed(){
     ui->treeWidget_in->clear();
     ui->treeWidget_out->clear();
     ui->lineEdit_in->clear();
     ui->lineEdit_out->clear();
}

void MainWindow::showSignal(QWidget *wgt){
    if(wgt->objectName() == "lineEdit_in")
        emit beginSearch(ui->treeWidget_in, ui->treeWidget_out, ui->lineEdit_in);
    else
        emit beginSearch(ui->treeWidget_out, ui->treeWidget_in, ui->lineEdit_out);

}

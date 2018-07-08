#include "mainwindow.h"
#include "parser.h"
#include "search.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Parser pr;
    //Если не удалось считать каталог, выходим из приложения
     if(!pr.initKeyName()) return 1;

    //создаем объекты Search, связываем с указателем на Parser
    Search se(&pr);
    MainWindow w;
    w.show();

    //Соединение согнала от формы с обработчиком объекта Search, выполняющего поиск
    QObject::connect(&w, SIGNAL(beginSearch(QTreeWidget*,QTreeWidget*,QLineEdit*)), &se, SLOT(sltSearchId(QTreeWidget*,QTreeWidget*,QLineEdit*)));

    return a.exec();
}

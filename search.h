#ifndef SEARCH_H
#define SEARCH_H
#include "ui_mainwindow.h"
#include "parser.h"

/// Производит операцию поиска строк в каталоге номенклатуры
class Search : public QWidget
{
    Q_OBJECT
    public:
    // инициализация указателя на объект Parser
        explicit Search(Parser *pp, QWidget *parent = 0);
    private:
        Parser *pParser;
    private slots:
    //	поиск введенных идентификаторов в каталоге номенклатуры
    void sltSearchId(QTreeWidget *pFirstWgt, QTreeWidget *pSecondWgt, QLineEdit *pLineEdt);
};

inline Search::Search(Parser *pp, QWidget *parent): QWidget(parent)
{
    pParser = pp;
}
#endif // SEARCH_H

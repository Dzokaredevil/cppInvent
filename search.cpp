#include "search.h"
#include "changetwitm.h"

void Search::sltSearchId(QTreeWidget *pFirstWgt, QTreeWidget *pSecondWgt, QLineEdit *pLineEdt)
{
    // разбить текст на слова разделенные пробелом
    QStringList field = pLineEdt->text().split(" ");
    for(auto t: field)
    // если такого ключа нет, то возвращает значение ""
        if(pParser->getNameForKey(t) != "" ){
        // при нахождении в базе ключа добавляем запись в виджет
            ChangeTWItm::insertTreeWgtItm(pFirstWgt, pSecondWgt, pParser->getNameForKey(t));
        }
    pLineEdt->clear();
}


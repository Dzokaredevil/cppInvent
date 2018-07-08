#include "changetwitm.h"

void ChangeTWItm::insertTreeWgtItm(QTreeWidget *toWidget, QTreeWidget *secondWidget, const QString &textAdd)
{
    QTreeWidgetItem *item, *child;

    //выделяем первое обобщающее слово из номенклатуты -> textTopWidget
    QRegExp rx("(\\b\\w+\\b)");
    int pos = rx.indexIn(textAdd);
    QString textTopWidget;
    if(pos >-1)
        textTopWidget = rx.cap(1);

    //ищем совпадения по обобщающему слову в виджете добавления
    //найденный список элементов -> foundTo
    QList<QTreeWidgetItem *> foundTo = toWidget->findItems(
                textTopWidget, Qt::MatchRecursive | Qt::MatchStartsWith);

    //аналогично для виджета вычитания
    //найденный список элементов -> foundFromSecond
    QList<QTreeWidgetItem *> foundFromSecond = secondWidget->findItems(
                textTopWidget, Qt::MatchRecursive | Qt::MatchStartsWith);

    //проверяем наличие в другом виджете и вычитаем количество из него
    ChangeTWItm::decrementFromWgt(foundFromSecond, textAdd);

    //если совпадений нет создаем новую запись с вложенным элементом
    //иначе, ищем точное соответствие в этом виджете,
    //а если есть совпадения в виджете вычитания вычитаем количество из него и прибавляем к добавлению
    //если в текущем таких элементов не было добавляем новый вложенный элемент
    if(foundTo.isEmpty()){
        //создаем верхний элемент
        item = new QTreeWidgetItem(QStringList() << textTopWidget);

        //объявляем вложенный элемент с текстом
        child = new QTreeWidgetItem(QStringList() <<textAdd << QString::number(1));
        //для созданного указываем вложенный элемент
        item->addChild(child);

        toWidget->addTopLevelItem(item);
        item->setExpanded(true);
    }else{
        //если такие элементы уже есть в таблице
        int isFound = 0;
        for(auto item: foundTo)
            if(item->text(0) == textAdd){
                int c = item->text(1).toInt() + 1;
                item->setText(1, QString::number(c));
                isFound = 1; //нашли точное соответствие, выходим
                break;
            }
        //не нашли точного соответствия, создаем вложенный элемент
        if(!isFound){
        //берем первое элемент из списка он будет топовым для остальных
        //добавляем к нему вложенный
        item = foundTo.first();
        child = new QTreeWidgetItem(item, QStringList() <<textAdd << QString::number(1));
        item->addChild(child);
        toWidget->addTopLevelItem(item);
        item->setExpanded(true);
        }
    }
}

void ChangeTWItm::decrementFromWgt(const QList<QTreeWidgetItem *> &found, const QString &text)
{
    if(!found.isEmpty()){
        for(auto itm: found){
            if(itm->text(0) == text){
                //проверка на остаток после вычитания
                //если остаток есть то записываем
                //если ничего не осталось удаляем элемент из дерева
                if(int c = itm->text(1).toInt() - 1){
                    itm->setText(1, QString::number(c));
                    break;
                }else{
                    //определяем родительский элемент в дереве
                    QTreeWidgetItem *prn;
                    prn = itm->parent();
                    //удаляем элемент, предварительно взяв его индекс
                    delete prn->takeChild(prn->indexOfChild(itm));
                    //если вложенных элементов больше нет, удаляем родительский
                    if(!prn->childCount()){
                        QTreeWidget *remowWgt = prn->treeWidget();
                        delete remowWgt->takeTopLevelItem(remowWgt->indexOfTopLevelItem(prn));
                    }
                }
            }
        }
    }
}

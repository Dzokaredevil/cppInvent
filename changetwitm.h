#ifndef CHANGETWITM_H
#define CHANGETWITM_H
#include "ui_mainwindow.h"

// Производит операции добавления, удаления и изменения в виджете
namespace ChangeTWItm
{
    //	Добавление текста в виджет toWidget (виджет добавления)
    void insertTreeWgtItm(QTreeWidget *toWidget, QTreeWidget *secondWidget, const QString &textAdd);
    //	декремент значения второго столбца в переданных записях
    void decrementFromWgt(const QList<QTreeWidgetItem*> &found, const QString &text);
}
#endif // CHANGETWITM_H

#ifndef PARSER_H
#define PARSER_H
#include "ui_mainwindow.h"

// Считывание каталога номенклатуры из файла xml
// формирование из него структуры данных в памяти
class Parser : public QWidget
{
    Q_OBJECT
    public:
        Parser(QWidget *parent = 0);
        // Считывание каталога номенклатцры из файла и формирование структуры данных
        int initKeyName();
        // Возвращает значение соответствующее ключу либо пустую строку, если ключа нет
        QString getNameForKey(const QString &key) const;
    private:
        // хранит пары идентификатра и номенклатуры
        QHash<QString,QString> keyName;
};

#endif // PARSER_H

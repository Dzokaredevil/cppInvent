#include "parser.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>

Parser::Parser(QWidget *parent) :
     QWidget(parent) {}

int Parser::initKeyName()
{
    QMessageBox::information(0,"Обратите внимание:",
                             "Для работы программы необходимо указать файл с каталогом номенклатуры товаров.\n"
                             "Выберете файл в следующем окне:",
                             QMessageBox::Ok);

// открываем файл для чтения
    QString fileAddr = QFileDialog::getOpenFileName(0, "Выберите файл", "data.xml", "*.xml");
    QFile file(fileAddr);
// если открыть не удалось, завершаем выполнение программы
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,
                                    "Ошибка файла",
                                    "Не удалось открыть файл",
                                    QMessageBox::Ok);

        return 0;
    } else {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();   // Переходит к первому элементу в файле

        //Крутимся в цикле до тех пор, пока не достигнем конца документа
        while(!xmlReader.atEnd()){
            //Проверяем, является ли элемент началом тега
            if(xmlReader.isStartElement())
                //  Проверяем, относится ли тег к продукту.
                //  Если "ДА", то выполняем проверку атрибута id
                if(xmlReader.name() == "product")
                    //  Забираем все атрибуты тега и перебираем их для проверки на соответствие
                    //  нужному нам атрибуту
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                        //  Если найден нужный атрибут, то записываем в контейнер
                        //  его значение в качестве ключа, текст в качестве значения
                        if (attr.name().toString() == "id") {
                            QString attribute_value = attr.value().toString();
                            keyName[attribute_value] = xmlReader.readElementText();
                        }
            xmlReader.readNext(); // Переходим к следующему элементу файла
        }
        file.close(); // Закрываем файл
        return 1;
    }
}

QString Parser::getNameForKey(const QString &key) const
{
    return keyName.value(key,"");
}

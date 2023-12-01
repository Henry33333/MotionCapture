
#ifndef EXCELREAD_H
#define EXCELREAD_H


#include <QString>
#include <QVector>
#include "xlsxdocument.h"

class ExcelReader
{
public:
    ExcelReader();
    ~ExcelReader();
    void Read();



private:
    QString m_str_filepath;
    QXlsx::Document* m_xlsx;
    QVector< QVector<int> > m_result;

};

#endif // EXCELREAD_H

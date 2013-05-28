#include "csvwriter.h"
#include <QTextStream>
#include <QDebug>

CSVwriter::CSVwriter()
{
}
bool CSVwriter::WriteCSV(QIODevice * device, CSVTable &table,QString saporator,QString stringEnd)
{
    QTextStream stream(device);
    foreach(QVariantList line,table)
    {
        const int c = line.count();
        for(int i=0; i<c ; i++)
        {
            stream << stringEnd << line.at(i).toString() << stringEnd;
            if(i!=c-1)
                stream << saporator;

            stream << "\n";
        }
    }
    return true;
}

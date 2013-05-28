#include "csvreader.h"
#include <QTextStream>
#include <QStringList>
#include <QDebug>



CSVreader::CSVreader()
{
}
bool CSVreader::ReadCSV(QIODevice* device,CSVTable& table,QString saporator,QString stringEnd)
{
    bool succes=false;
    // clearing current tables
    table.clear();

    QTextStream stream(device);
    while(!stream.atEnd())
    {
        QString line = stream.readLine();
        QStringList tokens = ParceCSVLine(line,saporator,stringEnd);
        QVariantList tableline;
        foreach(QString token,tokens)
        {
            tableline.append(token);
        }
        table.append(tableline);
    }


    succes = true;

    return succes;
}
QStringList CSVreader::ParceCSVLine(QString line,QString saporator,QString stringEnd)
{
    QStringList list;
    int pos2 = 0;
    //QRegExp rx2("(?:\"([^\"]*)\";?)|(?:([^;]*);?)");
    QRegExp rx2(PrepareRegExp(saporator,stringEnd));
    if(line.size()<1)
    {
        list << "";
    }else while (line.size()>pos2 && (pos2 = rx2.indexIn(line, pos2)) != -1)
    {
        QString col;
        if(rx2.cap(1).size()>0)
            col = rx2.cap(1);
        else if(rx2.cap(2).size()>0)
            col = rx2.cap(2);

        list << col;

        if(col.size())
            pos2 += rx2.matchedLength();
        else
            pos2++;
    }
    return list;
}
// not implimented.
QString CSVreader::EscRegExpTokens(QString string)
{
    foreach(QString csvtoken,RegExpTokens())
    {
        string.replace(csvtoken,"\\"+csvtoken);
    }

    return string;
}
QString CSVreader::PrepareRegExp(QString saporator,QString stringEnd)
{
    saporator = EscRegExpTokens(saporator);
    stringEnd = EscRegExpTokens(stringEnd);
    QString exp = QString("(?:%0([^%0]*)%0%1?)|(?:([^%1]*)%1?)")
            .arg(stringEnd)
            .arg(saporator);
    return exp;
}

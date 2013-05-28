#ifndef CSVREADER_H
#define CSVREADER_H

#include "Utilities_global.h"
#include "CSVcommon.h"
#include <QIODevice>
#include <QStringList>


// known bug: saporator within two stringEnds will not be skiped

class UTILITIESSHARED_EXPORT CSVreader
{
public:
    CSVreader();
    static bool ReadCSV(QIODevice* device,CSVTable& table,QString saporator=",",QString stringEnd="");
private:
    static QStringList ParceCSVLine(QString line,QString saporator,QString stringEnd);
    static QString EscRegExpTokens(QString string);
    static QString PrepareRegExp(QString saporator,QString stringEnd);
};

#endif // CSVREADER_H

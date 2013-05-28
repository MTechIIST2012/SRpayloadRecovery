#ifndef CSVWRITER_H
#define CSVWRITER_H

#include "Utilities_global.h"
#include "CSVcommon.h"
#include <QIODevice>


class UTILITIESSHARED_EXPORT CSVwriter
{
public:
    CSVwriter();
    static bool WriteCSV(QIODevice* device,CSVTable& table,QString saporator=",",QString stringEnd="");
};

#endif // CSVWRITER_H

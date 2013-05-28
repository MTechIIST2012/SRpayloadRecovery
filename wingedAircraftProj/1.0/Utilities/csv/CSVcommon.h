#ifndef CSVCOMMON_H
#define CSVCOMMON_H

#include <QVariant>
#include <QStringList>

typedef QList<QVariantList> CSVTable;

static QStringList RegExpTokens()
{
    QStringList tokens;
    tokens << "\\" << "*" << "^" << "." << "[" << "]" << ":"
           << "(" << ")" << "{" << "}" << "+" << "$" << "?";
    return tokens;
}

#endif // CSVCOMMON_H

#ifndef OBJECTVIEWINFO_H
#define OBJECTVIEWINFO_H

#include "ControlLib_global.h"
#include <QString>
#include <QHash>
#include <QColor>

#define STR_VIEWTYPE_LINES      "Lines"
#define STR_VIEWTYPE_SURFACE    "Surface"
#define STR_VIEWTYPE_HIDDEN     "Hidden"

class CONTROLLIBSHARED_EXPORT ObjectViewInfo
{
public:
    enum ViewType
    {
        SURFACE,
        LINES,
        HIDDEN
    };

    ObjectViewInfo();
    bool isVisible();
    void setViewType(ViewType type);
    ViewType getViewType();
    void setColor(QColor color);
    QColor getColor();
    static ViewType toViewType(QString typeStr);
    static QString toString(ViewType type);

    bool operator==(ObjectViewInfo& other);
private:
    ViewType mViewType;
    QColor mColor;
};

typedef QHash<QString,ObjectViewInfo> ObjectInfoHash;

#endif // OBJECTVIEWINFO_H

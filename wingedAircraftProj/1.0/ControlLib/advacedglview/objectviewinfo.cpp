#include "objectviewinfo.h"

ObjectViewInfo::ObjectViewInfo()
{
    mViewType = SURFACE;
    mColor = Qt::gray;
}

bool ObjectViewInfo::isVisible()
{
    return mViewType != HIDDEN;
}

void ObjectViewInfo::setViewType(ViewType type)
{
    mViewType = type;
}

ObjectViewInfo::ViewType ObjectViewInfo::getViewType()
{
    return mViewType;
}

void ObjectViewInfo::setColor(QColor color)
{
    mColor = color;
}

QColor ObjectViewInfo::getColor()
{
    return mColor;
}

ObjectViewInfo::ViewType ObjectViewInfo::toViewType(QString typeStr)
{
    ObjectViewInfo::ViewType type;
    if(typeStr == STR_VIEWTYPE_LINES)
    {
        type = ObjectViewInfo::LINES;
    }
    else if(typeStr == STR_VIEWTYPE_HIDDEN)
    {
        type = ObjectViewInfo::HIDDEN;
    }
    else // STR_VIEWTYPE_SURFACE
    {
        type = ObjectViewInfo::SURFACE;
    }
    return type;
}

QString ObjectViewInfo::toString(ObjectViewInfo::ViewType type)
{
    QString typeStr;
    switch(type)
    {
    case ObjectViewInfo::LINES:
        typeStr = STR_VIEWTYPE_LINES;
        break;
    case ObjectViewInfo::HIDDEN:
        typeStr = STR_VIEWTYPE_HIDDEN;
        break;
    default:
        typeStr = STR_VIEWTYPE_SURFACE;
    }
    return typeStr;
}

bool ObjectViewInfo::operator==(ObjectViewInfo& other)
{
    bool bEqual = false;
    if(mViewType == other.getViewType() &&
       mColor == other.getColor())
    {
        bEqual = true;
    }
    return bEqual;
}

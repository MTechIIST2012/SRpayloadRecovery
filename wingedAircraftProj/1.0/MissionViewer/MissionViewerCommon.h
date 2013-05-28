#ifndef MISSIONVIEWERCOMMON_H
#define MISSIONVIEWERCOMMON_H

#include <QStringList>


#define VIEWNAME_3DVIEW         "3d view"
#define VIEWNAME_METERPANNEL    "Meter pannel"

const QStringList glstViewTypes = QStringList() << VIEWNAME_3DVIEW
                              << VIEWNAME_METERPANNEL;

////////////////////////////////////////////////////////////////////////////////

// configfile fields.
#define GROUP_GE            "GE"
#define GROUP_FILES         "files"
#define GROUP_OUTDIR        "outdir"
#define GROUP_ORIENTAION    "OrientationCorrection"
#define GROUP_SCALE         "scale"

#define FIELD_GEAPP         "GE_app"
#define FIELD_TEMPLATE      "template"
#define FIELD_MODEL         "model"
#define FIELD_RUNTIMEFILE   "GE_runtimefile"
#define FIELD_GEOUTDIR      "GE_outdir"
#define FIELD_ROTX          "rot_x"
#define FIELD_ROTY          "rot_y"
#define FIELD_ROTZ          "rot_z"
#define FIELD_ROT_ORDER      "rot_order"
#define FIELD_SCALEX        "scale_x"
#define FIELD_SCALEY        "scale_y"
#define FIELD_SCALEZ        "scale_z"

////////////////////////////////////////////////////////////////////////////////

#define PLANEVIEWER_SETTINGS      "../../settings/planeviewer_settings.ini"
#define GOOGLE_EARTH_SETTINGS   "../../settings/googleearth_settings.ini"

#endif // MISSIONVIEWERCOMMON_H

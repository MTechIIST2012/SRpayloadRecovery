#ifndef PROJECTCORE_GLOBAL_H
#define PROJECTCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PROJECTCORE_LIBRARY)
#  define PROJECTCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define PROJECTCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PROJECTCORE_GLOBAL_H

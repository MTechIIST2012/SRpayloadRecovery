#ifndef PLANESIMULATIONCORE_GLOBAL_H
#define PLANESIMULATIONCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLANESIMULATIONCORE_LIBRARY)
#  define PLANESIMULATIONCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLANESIMULATIONCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLANESIMULATIONCORE_GLOBAL_H

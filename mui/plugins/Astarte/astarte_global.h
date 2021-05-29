#ifndef ASTARTE_GLOBAL_H 
#define  ASTARTE_GLOBAL_H 

#include <QtCore/qglobal.h>

#if defined(ASTARTE_LIBRARY)
#  define ASTARTESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ASTARTESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ASTARTE_GLOBAL_H
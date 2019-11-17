#ifndef CONTROLLER_VERSION_H
#define CONTROLLER_VERSION_H

#include "src/utils/util_build_number.h"

#include <QDateTime>
#include <QLocale>

class VersionController {

public:
    static QString getVersion();
    static QString getBulidDateTime();

private:
    static const QString VERSION_NUMBER;
    static const QDate BUILD_DATE;
    static const QTime BUILD_TIME;
    static const bool RELEASE_STATE;
};

#endif // CONTROLLER_VERSION_H

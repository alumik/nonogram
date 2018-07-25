#ifndef VERSION_H
#define VERSION_H

#include "build_number.h"

#include <QDateTime>
#include <QLocale>

class Version {

public:
    static QString getVersion();
    static QString getBulidDateTime();

private:
    static const QString VERSION_NUMBER;
    static const QDate BUILD_DATE;
    static const QTime BUILD_TIME;
    static const bool RELEASE_STATE;
};

#endif // VERSION_H

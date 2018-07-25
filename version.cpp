#include "version.h"

const QString Version::VERSION_NUMBER = QString("2.7.5.0");

const QDate Version::BUILD_DATE = QLocale(QLocale::English).toDate(QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");

const QTime Version::BUILD_TIME = QTime::fromString(__TIME__, "hh:mm:ss");

const bool Version::RELEASE_STATE = false;

QString Version::getVersion() {
	const QString release_string = RELEASE_STATE ? "Release" : "Debug";
    return QString("%1 (build %2) %3").arg(VERSION_NUMBER).arg(BUILD_NUMBER).arg(release_string);
}

QString Version::getBulidDateTime() {
    return BUILD_DATE.toString("yyyy年M月d日") + " " + BUILD_TIME.toString();
}

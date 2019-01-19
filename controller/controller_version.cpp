#include "controller/controller_version.h"

/**
 * \brief 版本号
 */
const QString VersionController::VERSION_NUMBER = QString("2.8.1.0");

/**
 * \brief 编译日期
 */
const QDate VersionController::BUILD_DATE = QLocale(QLocale::English).toDate(QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");

/**
 * \brief 编译时间
 */
const QTime VersionController::BUILD_TIME = QTime::fromString(__TIME__, "hh:mm:ss");

/**
 * \brief 发布状态
 */
const bool VersionController::RELEASE_STATE = true;

/**
 * \brief 获取版本号和 Build 数
 * \return
 */
QString VersionController::getVersion() {
    const QString release_string = RELEASE_STATE ? "Release" : "Debug";
    return QString("%1 (build %2) %3").arg(VERSION_NUMBER).arg(BUILD_NUMBER).arg(release_string);
}

/**
 * \brief 获取编译日期和时间
 * \return
 */
QString VersionController::getBulidDateTime() {
    return BUILD_DATE.toString("yyyy年M月d日") + " " + BUILD_TIME.toString();
}

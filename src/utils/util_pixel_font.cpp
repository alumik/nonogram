#include "src/utils/util_pixel_font.h"

/**
 * \brief 像素字体构造函数
 * \param family 字体名称
 * \param point_size 字体大小
 * \param weight 字体粗细
 * \param italic 是否为斜体
 */
PixelFont::PixelFont(const QString &family,
                     const int point_size,
                     const int weight,
                     const bool italic)
		: QFont(family, point_size, weight, italic) {
    setPixelSize(point_size * 4 / 3);
}

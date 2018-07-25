#include "util_pixel_font.h"

PixelFont::PixelFont(const QString &family,
                     const int point_size,
                     const int weight,
                     const bool italic)
    : QFont(family, point_size, weight, italic) {
    setPixelSize(point_size * 4 / 3);
}

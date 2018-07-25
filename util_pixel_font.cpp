#include "util_pixel_font.h"

PixelFont::PixelFont(const QString &family,
                     const int point_size,
                     const int weight,
                     const bool italic)
	: QFont(family, point_size, weight, italic) {
	const auto pixel_size = point_size * 4 / 3;
	setPixelSize(pixel_size);
}

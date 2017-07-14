#include "pixelfont.h"

PixelFont::PixelFont(const QString &family, int pointSize, int weight, bool italic)
	: QFont(family, pointSize, weight, italic) {
	int pixelSize = pointSize * 4 / 3;
	setPixelSize(pixelSize);
}

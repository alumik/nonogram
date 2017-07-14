#ifndef PIXELFONT_H
#define PIXELFONT_H

#include <QFont>

class PixelFont : public QFont {

public:
	PixelFont(const QString &family, int pixelSize = -1, int weight = -1, bool italic = false);
};

#endif // PIXELFONT_H

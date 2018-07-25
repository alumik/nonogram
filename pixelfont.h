#ifndef PIXELFONT_H
#define PIXELFONT_H

#include <QFont>

class PixelFont : public QFont {

public:
    explicit PixelFont(const QString &family,
                       int point_size = -1,
                       int weight = -1,
                       bool italic = false);
};

#endif // PIXELFONT_H

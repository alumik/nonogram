#ifndef NONOGRAM_PREVIEW_H
#define NONOGRAM_PREVIEW_H

#include "util_pvector.h"

#include <QTableWidget>
#include <QResizeEvent>

class NonogramPreview : public QTableWidget {
    Q_OBJECT

public:
    NonogramPreview(PVector _game_grid,
                    PVector _hint_grid,
                    PVector _separator,
                    QWidget* parent = nullptr);
    void updatePreview(PVector pos, const QColor& color) const;

private:
    PVector hint_grid;

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // NONOGRAM_PREVIEW_H

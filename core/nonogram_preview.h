#ifndef NONOGRAM_PREVIEW_H
#define NONOGRAM_PREVIEW_H

#include "util/util_pvector.h"

#include <QTableWidget>
#include <QResizeEvent>

class NonogramPreview : public QTableWidget {
    Q_OBJECT

public:
	static const bool PRV_FILL = true;
	static const bool PRV_NOFILL = false;

    NonogramPreview(PVector game_grid,
                    PVector hint_grid,
                    PVector separator,
                    QWidget* parent = nullptr);
    void updatePreview(PVector pos, bool fill) const;

private:
    PVector private_hint_grid;

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // NONOGRAM_PREVIEW_H

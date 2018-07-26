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
	void updatePreview(int r, int c, const QColor& color) const;

private:
	int c_hint_row;
	int c_hint_column;

protected:
	void resizeEvent(QResizeEvent* event) override;
};

#endif // NONOGRAM_PREVIEW_H

#ifndef NONOGRAM_PREVIEW_H
#define NONOGRAM_PREVIEW_H

#include <QTableWidget>
#include <QResizeEvent>

class NonogramPreview : public QTableWidget {
	Q_OBJECT

public:
	NonogramPreview(int p_game_row,
					int p_game_column,
					int p_hint_row,
					int p_hint_column,
					int p_spliter_row,
					int p_spliter_column,
					QWidget* parent = nullptr);
	void updatePreview(int r, int c, const QColor& color) const;

private:
	int c_hint_row;
	int c_hint_column;

protected:
	void resizeEvent(QResizeEvent* event) override;
};

#endif // NONOGRAM_PREVIEW_H

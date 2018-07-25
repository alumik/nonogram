#ifndef NONOGRAM_H
#define NONOGRAM_H

#include "nonogram_preview.h"

#include <QTableWidget>
#include <QVector>
#include <QColor>
#include <QLabel>
#include <QMouseEvent>

struct GameMove {
	int row;
	int column;
	QColor new_background_color;
	QString new_text;
	QColor old_background_color;
	QString old_text;
};

class Nonogram : public QTableWidget {
	Q_OBJECT

public:
	int index;
	int game_row;
	int game_column;
	int hint_row;
	int hint_column;
	int table_width;
	int table_height;
	NonogramPreview* nonogram_preview;
	void checkLineComplete(int r, int c);
	bool complete;
	explicit Nonogram(QWidget* parent = nullptr);

private:
	int last_r;
	int last_c;
	int current_r;
	int current_c;
	int record_r;
	int record_c;
	int drag_r;
	int drag_c;
	bool mouse_pressed;
	QLabel* preview;
	QLabel* drag_size;
	QVector<GameMove> undos;
	QVector<GameMove> redos;
	bool canAct(int r, int c) const;
	bool crossHighlight(int r, int c) const;
	void eraseCrossHighlight() const;
	void areaHighlight();
	void eraseAreaHighlight();
    void record(int r,
                int c,
                const QColor& new_background_color,
                const QString& new_text);
	void checkGameComplete();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
    void undo();
    void redo();
    void resetGame();

private slots:
	void getBlock(const QModelIndex& index);
};

#endif // NONOGRAM_H

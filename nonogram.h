#ifndef NONOGRAM_H
#define NONOGRAM_H

#include "nonogram_preview.h"

#include <QTableWidget>
#include <QVector>
#include <QColor>
#include <QLabel>
#include <QMouseEvent>

struct GameMove {
    QPoint position;
    QString old_text;
	QString new_text;
	QColor old_background_color;
    QColor new_background_color;
};

class Nonogram : public QTableWidget {
	Q_OBJECT

public:
	NonogramPreview* nonogram_preview;

	explicit Nonogram(QWidget* parent = nullptr);

    QPoint getTableSize();
    QPoint getHintGrid();
    void save();
    void load(std::ifstream& loader);
    bool isComplete();

private:
    int index;
    bool complete;
    bool mouse_pressed;
    QPoint game_grid;
    QPoint hint_grid;
    QPoint table_size;
    QPoint last_position;
    QPoint current_position;
    QPoint record_position;
    QPoint drag_position;
    QLabel* label_preview;
    QLabel* label_drag_size;
	QVector<GameMove> undos;
	QVector<GameMove> redos;

    bool canAct(QPoint position) const;
    bool crossHighlight(QPoint position) const;
	void eraseCrossHighlight() const;
	void areaHighlight();
	void eraseAreaHighlight();
    void record(QPoint position, const QColor& new_background_color, const QString& new_text);
    void checkLineComplete(QPoint position);
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

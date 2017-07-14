#ifndef NONOGRAM_H
#define NONOGRAM_H

#include "nonogrampreview.h"

#include <QTableWidget>
#include <QVector>
#include <QColor>
#include <QLabel>
#include <QMouseEvent>

struct gameMove {
	int row;
	int column;
	QColor newBackgroundColor;
	QString newText;
	QColor oldBackgroundColor;
	QString oldText;
};

class Nonogram : public QTableWidget {
	Q_OBJECT

public:
	int index;
	int gameRow;
	int gameColumn;
	int hintRow;
	int hintColumn;
	int tableSizeW;
	int tableSizeH;
	NonogramPreview* nonogramPreview;
	void checkLineComplete(int r, int c);
	bool complete;

public:
	Nonogram(QWidget* parent = nullptr);

private:
	int lastR;
	int lastC;
	int currentR;
	int currentC;
	int recordR;
	int recordC;
	int dragR;
	int dragC;
	bool mousePressed;
	QLabel* preview;
	QLabel* dragSize;
	QVector<gameMove> undos;
	QVector<gameMove> redos;
	bool canAct(int r, int c);
	bool crossHighlight(int r, int c);
	void eraseCrossHighlight();
	void areaHighlight();
	void eraseAreaHighlight();
	void record(int r, int c, QColor newBackgroundColor, QString newText);
	void checkGameComplete();

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

private slots:
	void getBlock(const QModelIndex& index);

public slots:
	void undo();
	void redo();
	void resetGame();
};

#endif // NONOGRAM_H

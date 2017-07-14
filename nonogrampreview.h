#ifndef NONOGRAMPREVIEW_H
#define NONOGRAMPREVIEW_H

#include <QTableWidget>
#include <QResizeEvent>
#include <QColor>

class NonogramPreview : public QTableWidget {
	Q_OBJECT

public:
	NonogramPreview(int pGameRow,
					int pGameColumn,
					int pHintRow,
					int pHintColumn,
					int pSpliterRow,
					int pSpliterColumn,
					QWidget* parent = nullptr);
	void updatePreview(int r, int c, QColor color);

private:
	int cHintRow;
	int cHintColumn;

protected:
	void resizeEvent(QResizeEvent* event);
};

#endif // NONOGRAMPREVIEW_H

#ifndef LINEREADER_H
#define LINEREADER_H

#include "nonogram.h"

#include <QVector>

class LineReader {

private:
	Nonogram* nonogram;

public:
	LineReader(Nonogram* nonogram);
	QVector<int> readRow(int r);
	QVector<int> readColumn(int c);
	QVector<int> readHintRow(int r);
	QVector<int> readHintColumn(int c);
};

#endif // LINEREADER_H

#ifndef NONOGRAMDATA_H
#define NONOGRAMDATA_H

#include <QString>

struct NonogramData {
	int index;
	QString name;
	int gameRow;
	int gameColumn;
	int hintRow;
	int hintColumn;
	int hintH[10][50];
	int hintV[10][50];
};

#endif // NONOGRAMDATA_H

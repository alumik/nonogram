#include "nonogram.h"
#include "define.h"

#include <fstream>

using namespace std;

void saveGame(Nonogram* nonogram) {
	ofstream saver;
	saver.open("save.nonogram");
	saver << nonogram->index << endl;
	for (int r = nonogram->hintRow + 1; r < nonogram->rowCount(); r++) {
		for (int c = nonogram->hintColumn + 1; c < nonogram->columnCount(); c++) {
			QColor cColor = nonogram->item(r, c)->backgroundColor();
			QString cText = nonogram->item(r, c)->text();
			if ((cColor == PRIMARY_COLOR || cColor == CROSS_HIGHLIGHT_COLOR) && cText == QString("")) {
				saver << 0 << " ";
			} else if (cColor == DARK_COLOR) {
				saver << 1 << " ";
			} else if ((cColor == PRIMARY_COLOR || cColor == CROSS_HIGHLIGHT_COLOR) && cText == QString("╳")) {
				saver << 2 << " ";
			} else if (cColor == SECONDARY_SPLITER_COLOR) {
				saver << -1 << " ";
			}
		}
		saver << endl;
	}
	saver.close();
}

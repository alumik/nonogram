#include "nonogram.h"
#include "util_generic_define.h"

#include <fstream>

using namespace std;

void saveGame(Nonogram* nonogram) {
	ofstream saver;
	saver.open("save.nonogram");
	saver << nonogram->index << endl;
	for (auto r = nonogram->hint_row + 1; r < nonogram->rowCount(); r++) {
		for (auto c = nonogram->hint_column + 1; c < nonogram->columnCount(); c++) {
			const auto c_color = nonogram->item(r, c)->backgroundColor();
			const auto c_text = nonogram->item(r, c)->text();
			if ((c_color == PRIMARY_COLOR || c_color == CROSS_HIGHLIGHT_COLOR) && c_text == QString("")) {
				saver << 0 << " ";
			} else if (c_color == DARK_COLOR) {
				saver << 1 << " ";
			} else if ((c_color == PRIMARY_COLOR || c_color == CROSS_HIGHLIGHT_COLOR) && c_text == QString("╳")) {
				saver << 2 << " ";
			} else if (c_color == SECONDARY_SPLITER_COLOR) {
				saver << -1 << " ";
			}
		}
		saver << endl;
	}
	saver.close();
}

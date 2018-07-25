#include "button_menu.h"
#include "define.h"
#include "util_pixel_font.h"

MenuButton::MenuButton(const QString& caption, QWidget* parent, const bool no_accent_color)
	: QPushButton(caption, parent) {
	setFont(PixelFont("Microsoft YaHei UI", BUTTON_FONT_SIZE, 75));
	setFocusPolicy(Qt::NoFocus);
	setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	if (no_accent_color) {
		setStyleSheet("QPushButton {"
						  "color: rgb(43, 43, 43);"
						  "border: 2px solid #555555;"
						  "background-color: rgb(214, 214, 214);"
						  "border-radius:1px;"
					  "}"
					  "QPushButton:hover {"
						  "border: 2px solid #FF7800;"
						  "background-color: rgb(240, 230, 190);"
					  "}"
					  "QPushButton:pressed {"
						  "border: 2px solid #FF7800;"
						  "background-color: rgb(205, 170, 140);"
					  "}"
					  "QPushButton:default {"
						  "border: 2px solid #FF7800;"
						  "background-color: rgb(214, 214, 214);"
					  "}"
					  "QPushButton:default:hover {"
						  "border: 2px solid #FF7800;"
						  "background-color: rgb(240, 230, 190);"
					  "}"
					  "QPushButton:default:pressed {"
						  "border: 2px solid #FF7800;"
						  "background-color: rgb(205, 170, 140);"
					  "}");
	} else {
		setStyleSheet("QPushButton {"
						  "color: rgb(43, 43, 43);"
						  "border: 2px solid #555555;"
						  "background-color: qconicalgradient(cx:0.1, cy:0.5, angle:92, stop:0.49999 rgb(255, 150, 0), stop:0.50001 rgb(214, 214, 214));"
						  "border-radius:1px;"
					  "}"
					  "QPushButton:hover {"
						  "border: 2px solid #FF7800;"
						  "background-color: qconicalgradient(cx:0.1, cy:0.5, angle:92, stop:0.49999 rgb(255, 160, 70), stop:0.50001 rgb(240, 230, 190));"
					  "}"
					  "QPushButton:disabled {"
						  "background-color: qconicalgradient(cx:0.1, cy:0.5, angle:92, stop:0.49999 rgb(154, 154, 154), stop:0.50001 rgb(174, 174, 174));"
					  "}"
					  "QPushButton:pressed {"
						  "border: 2px solid #FF7800;"
						  "background-color: qconicalgradient(cx:0.1, cy:0.5, angle:92, stop:0.49999 rgb(200, 125, 60), stop:0.50001 rgb(205, 170, 140));"
					  "}");
		}
}

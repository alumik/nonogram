#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>

class MenuButton : public QPushButton {
	Q_OBJECT

public:
	MenuButton(QString caption,
			   QWidget* parent = nullptr,
			   bool noAccentColor = false);
};

#endif // MENUBUTTON_H

#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <QPushButton>

class MenuButton : public QPushButton {
	Q_OBJECT

public:
    explicit MenuButton(const QString& caption,
                        QWidget* parent = nullptr,
                        bool no_accent_color = false);
};

#endif // MENU_BUTTON_H

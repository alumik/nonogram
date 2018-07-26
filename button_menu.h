#ifndef BUTTON_MENU_H
#define BUTTON_MENU_H

#include <QPushButton>

class MenuButton : public QPushButton {
    Q_OBJECT

public:
    explicit MenuButton(const QString& caption,
                        QWidget* parent = nullptr,
                        bool accent_color = true);
};

#endif // BUTTON_MENU_H

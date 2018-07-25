#ifndef BUTTON_TOOL_H
#define BUTTON_TOOL_H

#include <QPushButton>

class ToolButton : public QPushButton {
	Q_OBJECT

public:
    ToolButton(const QIcon& icon,
               const QString& tip,
               QWidget* parent = nullptr,
               bool checkable = false,
               bool no_accent_color = false);
};

#endif // BUTTON_TOOL_H

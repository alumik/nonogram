#ifndef TOOL_BUTTON_H
#define TOOL_BUTTON_H

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

#endif // TOOL_BUTTON_H

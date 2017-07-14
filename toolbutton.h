#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QPushButton>
#include <QIcon>

class ToolButton : public QPushButton {
	Q_OBJECT

public:
	ToolButton(QIcon icon, QString tip, QWidget* parent = nullptr, bool checkable = false, bool noAccentColor = false);
};

#endif // TOOLBUTTON_H

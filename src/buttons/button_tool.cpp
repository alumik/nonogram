#include "button_tool.h"
#include "src/utils/util_generic_define.h"

/**
 * \brief 工具按钮构造函数
 * \param icon 按钮图标
 * \param tip 按钮提示
 * \param parent 父部件指针
 * \param checkable 是否可切换
 * \param accent_color 是否上高亮色
 */
ToolButton::ToolButton(const QIcon& icon,
                       const QString& tip,
                       QWidget* parent,
                       const bool checkable,
                       const bool accent_color)
		: QPushButton(parent) {
    setFixedSize(TOOL_BUTTON_SIZE);
    setFocusPolicy(Qt::NoFocus);
    setIcon(icon);
    setToolTip(tip);
    setIconSize(QSize(TOOL_BUTTON_ICON_SIZE));
    if (checkable) {
        setCheckable(true);
    }
    if (accent_color) {
        setStyleSheet(
            "QPushButton {"
                "border: 3px solid #2b2b2b;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.149999 rgb(255, 150, 0), stop:0.150000 rgb(214, 214, 214));"
                "border-radius:0px;"
            "}"
            "QPushButton:hover {"
                "border: 2px solid #FF7800;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.149999 rgb(255, 160, 70), stop:0.150000 rgb(240, 230, 190));"
            "}"
            "QPushButton:disabled {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.149999 rgb(154, 154, 154), stop:0.150000 rgb(174, 174, 174));"
            "}"
            "QPushButton:pressed {"
                "border: 2px solid #FF7800;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.149999 rgb(200, 125, 60), stop:0.150000 rgb(205, 170, 140));"
            "}"
        );
    } else {
        setStyleSheet(
            "QPushButton {"
                "border: 3px solid #2b2b2b;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.149999 rgb(120, 120, 120), stop:0.150000 rgb(214, 214, 214));"
                "border-radius:0px;"
            "}"
            "QPushButton:hover {"
                "border: 2px solid #FF7800;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.149999 rgb(255, 160, 70), stop:0.150000 rgb(240, 230, 190));"
            "}"
            "QPushButton:pressed {"
                "border: 2px solid #FF7800;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.149999 rgb(200, 125, 60), stop:0.150000 rgb(205, 170, 140));"
            "}"
            "QPushButton:checked {"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0.149999 rgb(255, 160, 70), stop:0.150000 rgb(240, 230, 190));"
            "}"
        );
    }
}

#ifndef WINDOW_INFO_H
#define WINDOW_INFO_H

#include "button_menu.h"

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

class InfoWindow : public QDialog {
	Q_OBJECT

public:
	InfoWindow(const QString& content, int btn_count, QWidget *parent = nullptr);
    ~InfoWindow() override;

private:
	QLabel* label_content;
	QLabel* label_game_name;
	MenuButton* btn_control_1;
	MenuButton* btn_control_2;
	MenuButton* btn_control_3;
	QHBoxLayout* layout_btn;
	QVBoxLayout* layout_this;

protected:
	void mousePressEvent(QMouseEvent* event) override;
    bool nativeEvent(const QByteArray& event_type, void* message, long* result) override;
	void showEvent(QShowEvent* event) override;

private slots:
    void btnControl1Clicked();
    void btnControl2Clicked();
    void btnControl3Clicked();
    void flashWindow(bool active);

signals:
	void ncActive(bool active);
};

#endif // WINDOW_INFO_H

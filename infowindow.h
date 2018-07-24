#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "menubutton.h"

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>

class InfoWindow : public QDialog {
	Q_OBJECT

public:
	InfoWindow(QString content, int btnCount, QWidget *parent = nullptr);
	~InfoWindow();

private:
	QLabel* lbContent;
	QLabel* lbGameName;
	MenuButton* cBtn1;
	MenuButton* cBtn2;
	MenuButton* cBtn3;
	QHBoxLayout* layoutBtn;
	QVBoxLayout* layoutDialog;

private slots:
	void cBtn1Clicked();
	void cBtn2Clicked();
	void cBtn3Clicked();
	void flashWindow(bool active);

protected:
	void mousePressEvent(QMouseEvent* event);
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	void showEvent(QShowEvent* event);

signals:
	void ncActive(bool active);
};

#endif // INFOWINDOW_H

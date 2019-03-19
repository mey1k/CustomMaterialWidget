#pragma once
#include <qlabel.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <Theme.h>

class CustomToothLabel : public QLabel
{
public:
	explicit CustomToothLabel(QWidget* parent = nullptr);
	virtual ~CustomToothLabel();

	void setSelectedTooth(QVector<int>);

	void setTheme(Theme *singletonTheme)
	{
		theme = singletonTheme;
	}

protected:
	virtual void paintEvent(QPaintEvent* e) override;

private:
	bool selectedTooth[31];
	void printMark();
	QPixmap m_pixmap;
	QString m_text;

	QRect rec = QApplication::desktop()->availableGeometry();
	int screenWidth = rec.width();
	int screenHeight = rec.height();

	Theme *theme = nullptr;
};

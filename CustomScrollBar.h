#ifndef CustomSCROLLBAR_H
#define CustomSCROLLBAR_H

#include <QtWidgets/QScrollBar>

class CustomScrollBarPrivate;

class CustomScrollBar : public QScrollBar
{
	Q_OBJECT

		Q_PROPERTY(QColor canvasColor WRITE setCanvasColor READ canvasColor)
		Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
		Q_PROPERTY(QColor sliderColor WRITE setSliderColor READ sliderColor)

public:
	explicit CustomScrollBar(QWidget *parent = 0);
	~CustomScrollBar();

	QSize sizeHint() const Q_DECL_OVERRIDE;

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setCanvasColor(const QColor &color);
	QColor canvasColor() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

	void setSliderColor(const QColor &color);
	QColor sliderColor() const;

	void setHideOnMouseOut(bool value);
	bool hideOnMouseOut() const;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	const QScopedPointer<CustomScrollBarPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomScrollBar)
		Q_DECLARE_PRIVATE(CustomScrollBar)
};

#endif // CustomSCROLLBAR_H

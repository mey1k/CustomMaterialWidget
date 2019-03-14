#ifndef CustomBADGE_H
#define CustomBADGE_H

#include "Customoverlaywidget.h"

class CustomBadgePrivate;

class CustomBadge : public CustomOverlayWidget
{
	Q_OBJECT

		Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
		Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
		Q_PROPERTY(QPointF relativePosition WRITE setRelativePosition READ relativePosition)

public:
	explicit CustomBadge(QWidget *parent = 0);
	explicit CustomBadge(const QIcon &icon, QWidget *parent = 0);
	explicit CustomBadge(const QString &text, QWidget *parent = 0);
	~CustomBadge();

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setTextColor(const QColor &color);
	QColor textColor() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

	void setRelativePosition(const QPointF &pos);
	void setRelativePosition(qreal x, qreal y);
	QPointF relativePosition() const;

	void setRelativeXPosition(qreal x);
	qreal relativeXPosition() const;

	void setRelativeYPosition(qreal y);
	qreal relativeYPosition() const;

	QSize sizeHint() const Q_DECL_OVERRIDE;
	void setSIze(int);

	void setIcon(const QIcon &icon);
	QIcon icon() const;

	void setText(const QString &text);
	QString text() const;

	int iconSize = 24;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	int getDiameter() const;

	const QScopedPointer<CustomBadgePrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomBadge)
		Q_DECLARE_PRIVATE(CustomBadge)
};

#endif // CustomBADGE_H

#ifndef CustomCHECKABLE_INTERNAL_H
#define CustomCHECKABLE_INTERNAL_H

#include <QtWidgets/QWidget>
#include <QColor>
#include <QIcon>

class CustomCheckable;

class CustomCheckableIcon : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(QColor color READ color WRITE setColor)
		Q_PROPERTY(qreal iconSize READ iconSize WRITE setIconSize)
		Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
	CustomCheckableIcon(const QIcon &icon, CustomCheckable *parent);
	~CustomCheckableIcon();

	QSize sizeHint() const Q_DECL_OVERRIDE;

	inline void setIcon(const QIcon &icon);
	inline QIcon icon() const;

	inline void setColor(const QColor &color);
	inline QColor color() const;

	inline void setIconSize(qreal size);
	inline qreal iconSize() const;

	inline void setOpacity(qreal opacity);
	inline qreal opacity() const;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomCheckableIcon)

		CustomCheckable *const m_checkable;
	QColor                     m_color;
	QIcon                      m_icon;
	qreal                      m_iconSize;
	qreal                      m_opacity;
};

inline void CustomCheckableIcon::setIcon(const QIcon &icon)
{
	m_icon = icon;
	update();
}

inline QIcon CustomCheckableIcon::icon() const
{
	return m_icon;
}

inline void CustomCheckableIcon::setColor(const QColor &color)
{
	m_color = color;
	update();
}

inline QColor CustomCheckableIcon::color() const
{
	return m_color;
}

inline void CustomCheckableIcon::setIconSize(qreal size)
{
	m_iconSize = size;
	update();
}

inline qreal CustomCheckableIcon::iconSize() const
{
	return m_iconSize;
}

inline void CustomCheckableIcon::setOpacity(qreal opacity)
{
	m_opacity = opacity;
	update();
}

inline qreal CustomCheckableIcon::opacity() const
{
	return m_opacity;
}

#endif // CustomCHECKABLE_INTERNAL_H

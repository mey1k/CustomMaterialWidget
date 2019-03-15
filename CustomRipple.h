#ifndef CustomRIPPLE_H
#define CustomRIPPLE_H

#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QPoint>
#include <QBrush>

class CustomRippleOverlay;

class CustomRipple : public QParallelAnimationGroup
{
	Q_OBJECT

		Q_PROPERTY(qreal radius WRITE setRadius READ radius)
		Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
	explicit CustomRipple(const QPoint &center, QObject *parent = 0);
	CustomRipple(const QPoint &center, CustomRippleOverlay *overlay, QObject *parent = 0);
	~CustomRipple();

	inline void setOverlay(CustomRippleOverlay *overlay);

	void setRadius(qreal radius);
	inline qreal radius() const;

	void setOpacity(qreal opacity);
	inline qreal opacity() const;

	void setColor(const QColor &color);
	inline QColor color() const;

	void setBrush(const QBrush &brush);
	inline QBrush brush() const;

	inline QPoint center() const;

	inline QPropertyAnimation *radiusAnimation() const;
	inline QPropertyAnimation *opacityAnimation() const;

	inline void setOpacityStartValue(qreal value);
	inline void setOpacityEndValue(qreal value);
	inline void setRadiusStartValue(qreal value);
	inline void setRadiusEndValue(qreal value);
	inline void setDuration(int msecs);

protected slots:
	void destroy();

private:
	Q_DISABLE_COPY(CustomRipple)

		QPropertyAnimation *animate(const QByteArray &property,
			const QEasingCurve &easing = QEasingCurve::OutQuad,
			int duration = 800);

	void init();

	CustomRippleOverlay  *m_overlay;
	QPropertyAnimation *const m_radiusAnimation;
	QPropertyAnimation *const m_opacityAnimation;
	qreal                     m_radius;
	qreal                     m_opacity;
	QPoint                    m_center;
	QBrush                    m_brush;
};

inline void CustomRipple::setOverlay(CustomRippleOverlay *overlay)
{
	m_overlay = overlay;
}

inline qreal CustomRipple::radius() const
{
	return m_radius;
}

inline qreal CustomRipple::opacity() const
{
	return m_opacity;
}

inline QColor CustomRipple::color() const
{
	return m_brush.color();
}

inline QBrush CustomRipple::brush() const
{
	return m_brush;
}

inline QPoint CustomRipple::center() const
{
	return m_center;
}

inline QPropertyAnimation *CustomRipple::radiusAnimation() const
{
	return m_radiusAnimation;
}

inline QPropertyAnimation *CustomRipple::opacityAnimation() const
{
	return m_opacityAnimation;
}

inline void CustomRipple::setOpacityStartValue(qreal value)
{
	m_opacityAnimation->setStartValue(value);
}

inline void CustomRipple::setOpacityEndValue(qreal value)
{
	m_opacityAnimation->setEndValue(value);
}

inline void CustomRipple::setRadiusStartValue(qreal value)
{
	m_radiusAnimation->setStartValue(value);
}

inline void CustomRipple::setRadiusEndValue(qreal value)
{
	m_radiusAnimation->setEndValue(value);
}

inline void CustomRipple::setDuration(int msecs)
{
	m_radiusAnimation->setDuration(msecs);
	m_opacityAnimation->setDuration(msecs);
}

#endif // CustomRIPPLE_H

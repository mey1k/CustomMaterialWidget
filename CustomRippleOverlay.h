#ifndef CustomRIPPLEOVERLAY_H
#define CustomRIPPLEOVERLAY_H

#include <QPainterPath>
#include "Customoverlaywidget.h"

class CustomRipple;

class CustomRippleOverlay : public CustomOverlayWidget
{
	Q_OBJECT

public:
	explicit CustomRippleOverlay(QWidget *parent = 0);
	~CustomRippleOverlay();

	void addRipple(CustomRipple *ripple);
	void addRipple(const QPoint &position, qreal radius = 300);

	void removeRipple(CustomRipple *ripple);

	inline void setClipping(bool enable);
	inline bool hasClipping() const;

	inline void setClipPath(const QPainterPath &path);

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	inline QList<CustomRipple *> ripples() const;

private:
	Q_DISABLE_COPY(CustomRippleOverlay)

		void paintRipple(QPainter *painter, CustomRipple *ripple);

	QList<CustomRipple *> m_ripples;
	QPainterPath              m_clipPath;
	bool                      m_useClip;
};

inline void CustomRippleOverlay::setClipping(bool enable)
{
	m_useClip = enable;
	update();
}

inline bool CustomRippleOverlay::hasClipping() const
{
	return m_useClip;
}

inline void CustomRippleOverlay::setClipPath(const QPainterPath &path)
{
	m_clipPath = path;
	update();
}

inline QList<CustomRipple *> CustomRippleOverlay::ripples() const
{
	return m_ripples;
}

#endif // CustomRIPPLEOVERLAY_H

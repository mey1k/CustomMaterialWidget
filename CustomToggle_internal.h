#ifndef CustomTOGGLE_INTERNAL_H
#define CustomTOGGLE_INTERNAL_H

#include <QtWidgets/QWidget>
#include "Customrippleoverlay.h"

class CustomToggle;
class CustomToggleThumb;
class CustomToggleTrack;

class CustomToggleRippleOverlay : public CustomRippleOverlay
{
	Q_OBJECT

public:
	CustomToggleRippleOverlay(CustomToggleThumb *thumb,
		CustomToggleTrack *track,
		CustomToggle *parent);
	~CustomToggleRippleOverlay();

protected slots:
	void addToggleRipple();

protected:
	bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
	QRect overlayGeometry() const Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomToggleRippleOverlay)

		CustomToggle      *const m_toggle;
	CustomToggleThumb *const m_thumb;
	CustomToggleTrack *const m_track;
};

class CustomToggleThumb : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(qreal shift WRITE setShift READ shift)
		Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
	CustomToggleThumb(CustomToggle *parent);
	~CustomToggleThumb();

	void setShift(qreal shift);
	inline qreal shift() const;

	inline qreal offset() const;

	inline void setThumbColor(const QColor &color);
	inline QColor thumbColor() const;

protected:
	bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomToggleThumb)

		void updateOffset();

	CustomToggle *const m_toggle;
	QColor                  m_thumbColor;
	qreal                   m_shift;
	qreal                   m_offset;
};

inline qreal CustomToggleThumb::shift() const
{
	return m_shift;
}

inline qreal CustomToggleThumb::offset() const
{
	return m_offset;
}

inline void CustomToggleThumb::setThumbColor(const QColor &color)
{
	m_thumbColor = color;
	update();
}

inline QColor CustomToggleThumb::thumbColor() const
{
	return m_thumbColor;
}

class CustomToggleTrack : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
	CustomToggleTrack(CustomToggle *parent);
	~CustomToggleTrack();

	void setTrackColor(const QColor &color);
	inline QColor trackColor() const;

protected:
	bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomToggleTrack)

		CustomToggle *const m_toggle;
	QColor                  m_trackColor;
};

inline QColor CustomToggleTrack::trackColor() const
{
	return m_trackColor;
}

#endif // CustomTOGGLE_INTERNAL_H

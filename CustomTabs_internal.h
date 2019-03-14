#ifndef CustomTABS_INTERNAL_H
#define CustomTABS_INTERNAL_H

#include "Customoverlaywidget.h"
#include "Customflatbutton.h"

class QPropertyAnimation;
class CustomTabs;

class CustomTabsInkBar : public CustomOverlayWidget
{
	Q_OBJECT

		Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
	CustomTabsInkBar(CustomTabs *parent);
	~CustomTabsInkBar();

	inline void setTweenValue(qreal value);
	inline qreal tweenValue() const;

	void refreshGeometry();
	void animate();

protected:
	bool eventFilter(QObject *obj, QEvent *event)  Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomTabsInkBar)

		CustomTabs     *const m_tabs;
	QPropertyAnimation *const m_animation;
	QRect                     m_geometry;
	QRect                     m_previousGeometry;
	qreal                     m_tween;
};

inline void CustomTabsInkBar::setTweenValue(qreal value)
{
	m_tween = value;
	refreshGeometry();
}

inline qreal CustomTabsInkBar::tweenValue() const
{
	return m_tween;
}

class CustomTab : public CustomFlatButton
{
	Q_OBJECT

public:
	explicit CustomTab(CustomTabs *parent);
	~CustomTab();

	inline void setActive(bool state);
	inline bool isActive() const;

	QSize sizeHint() const Q_DECL_OVERRIDE;

protected slots:
	void activateTab();

protected:
	void paintForeground(QPainter *painter) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomTab)

		CustomTabs *const m_tabs;
	bool                  m_active;
};

inline void CustomTab::setActive(bool state)
{
	m_active = state;
	update();
}

inline bool CustomTab::isActive() const
{
	return m_active;
}

#endif // CustomTABS_INTERNAL_H

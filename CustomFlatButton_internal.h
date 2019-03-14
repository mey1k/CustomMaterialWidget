#ifndef CustomFLATBUTTON_INTERNAL_H
#define CustomFLATBUTTON_INTERNAL_H

#include <QStateMachine>
#include <QColor>

class CustomFlatButton;
class QSequentialAnimationGroup;

class CustomFlatButtonStateMachine : public QStateMachine
{
	Q_OBJECT

		Q_PROPERTY(qreal overlayOpacity WRITE setOverlayOpacity READ overlayOpacity)
		Q_PROPERTY(qreal checkedOverlayProgress WRITE setCheckedOverlayProgress READ checkedOverlayProgress)
		Q_PROPERTY(qreal haloOpacity WRITE setHaloOpacity READ haloOpacity)
		Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
		Q_PROPERTY(qreal haloScaleFactor WRITE setHaloScaleFactor READ haloScaleFactor)

public:
	explicit CustomFlatButtonStateMachine(CustomFlatButton *parent);
	~CustomFlatButtonStateMachine();

	void setOverlayOpacity(qreal opacity);
	inline qreal overlayOpacity() const;

	void setCheckedOverlayProgress(qreal progress);
	inline qreal checkedOverlayProgress() const;

	void setHaloOpacity(qreal opacity);
	inline qreal haloOpacity() const;

	void setHaloSize(qreal size);
	inline qreal haloSize() const;

	void setHaloScaleFactor(qreal factor);
	inline qreal haloScaleFactor() const;

	void startAnimations();
	void setupProperties();
	void updateCheckedStatus();

signals:
	void buttonPressed();
	void buttonChecked();
	void buttonUnchecked();

protected:
	bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomFlatButtonStateMachine)

		void addTransition(QObject *object, QEvent::Type eventType, QState *fromState, QState *toState);
	void addTransition(QAbstractTransition *transition, QState *fromState, QState *toState);

	CustomFlatButton *const m_button;
	QState               *const m_topLevelState;
	QState               *const m_configState;
	QState               *const m_checkableState;
	QState               *const m_checkedState;
	QState               *const m_uncheckedState;
	QState               *const m_neutralState;
	QState               *const m_neutralFocusedState;
	QState               *const m_hoveredState;
	QState               *const m_hoveredFocusedState;
	QState               *const m_pressedState;
	QSequentialAnimationGroup
		*const m_haloAnimation;
	qreal                       m_overlayOpacity;
	qreal                       m_checkedOverlayProgress;
	qreal                       m_haloOpacity;
	qreal                       m_haloSize;
	qreal                       m_haloScaleFactor;
	bool                        m_wasChecked;
};

inline qreal CustomFlatButtonStateMachine::overlayOpacity() const
{
	return m_overlayOpacity;
}

inline qreal CustomFlatButtonStateMachine::checkedOverlayProgress() const
{
	return m_checkedOverlayProgress;
}

inline qreal CustomFlatButtonStateMachine::haloOpacity() const
{
	return m_haloOpacity;
}

inline qreal CustomFlatButtonStateMachine::haloSize() const
{
	return m_haloSize;
}

inline qreal CustomFlatButtonStateMachine::haloScaleFactor() const
{
	return m_haloScaleFactor;
}

#endif // CustomFLATBUTTON_INTERNAL_H

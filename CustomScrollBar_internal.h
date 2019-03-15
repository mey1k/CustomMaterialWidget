#ifndef CustomSCROLLBAR_INTERNAL_H
#define CustomSCROLLBAR_INTERNAL_H

#include <QStateMachine>
#include "Customscrollbar.h"

class CustomScrollBarStateMachine : public QStateMachine
{
	Q_OBJECT

		Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
	CustomScrollBarStateMachine(CustomScrollBar *parent);
	~CustomScrollBarStateMachine();

	inline void setOpacity(qreal opacity);
	inline qreal opacity() const;

private:
	Q_DISABLE_COPY(CustomScrollBarStateMachine)

		CustomScrollBar *const m_scrollBar;
	QState              *const m_focusState;
	QState              *const m_blurState;
	qreal                m_opacity;
};

inline void CustomScrollBarStateMachine::setOpacity(qreal opacity)
{
	m_opacity = opacity;
	m_scrollBar->update();
}

inline qreal CustomScrollBarStateMachine::opacity() const
{
	return m_opacity;
}

#endif // CustomSCROLLBAR_INTERNAL_H

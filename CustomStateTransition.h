#ifndef CustomSTATETRANSITION_H
#define CustomSTATETRANSITION_H

#include <QAbstractTransition>
#include "Library/CustomWidget/CustomStateTransitionEvent.h"

class CustomStateTransition : public QAbstractTransition
{
	Q_OBJECT

public:
	CustomStateTransition(CustomStateTransitionType type);

protected:
	virtual bool eventTest(QEvent *event);
	virtual void onTransition(QEvent *);

private:
	CustomStateTransitionType m_type;
};

#endif // CustomSTATETRANSITION_H

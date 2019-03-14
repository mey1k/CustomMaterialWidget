#ifndef CustomRAISEDBUTTON_P_H
#define CustomRAISEDBUTTON_P_H

#include "Customflatbutton_p.h"

class QStateMachine;
class QState;
class QGraphicsDropShadowEffect;
class CustomRaisedButton;

class CustomRaisedButtonPrivate : public CustomFlatButtonPrivate
{
	Q_DISABLE_COPY(CustomRaisedButtonPrivate)
		Q_DECLARE_PUBLIC(CustomRaisedButton)

public:
	CustomRaisedButtonPrivate(CustomRaisedButton *q);
	~CustomRaisedButtonPrivate();

	void init();

	QStateMachine             *shadowStateMachine;
	QState                    *normalState;
	QState                    *pressedState;
	QGraphicsDropShadowEffect *effect;
};

#endif // CustomRAISEDBUTTON_P_H

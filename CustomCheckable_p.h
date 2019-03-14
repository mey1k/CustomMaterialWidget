#ifndef CustomCHECKABLE_P_H
#define CustomCHECKABLE_P_H

#include <QtGlobal>
#include "Customcheckable.h"

class QStateMachine;
class QState;
class QSignalTransition;
class CustomRippleOverlay;
class CustomCheckableIcon;

class CustomCheckablePrivate
{
	Q_DISABLE_COPY(CustomCheckablePrivate)
		Q_DECLARE_PUBLIC(CustomCheckable)

public:
	CustomCheckablePrivate(CustomCheckable *q);
	virtual ~CustomCheckablePrivate();

	void init();

	CustomCheckable                *const q_ptr;
	CustomRippleOverlay            *rippleOverlay;
	CustomCheckableIcon            *checkedIcon;
	CustomCheckableIcon            *uncheckedIcon;
	QStateMachine                      *stateMachine;
	QState                             *uncheckedState;
	QState                             *checkedState;
	QState                             *disabledUncheckedState;
	QState                             *disabledCheckedState;
	QSignalTransition                  *uncheckedTransition;
	QSignalTransition                  *checkedTransition;
	CustomCheckable::LabelPosition  labelPosition;
	QColor                              checkedColor;
	QColor                              uncheckedColor;
	QColor                              textColor;
	QColor                              disabledColor;
	bool                                useThemeColors;
};

#endif // CustomCHECKABLE_P_H

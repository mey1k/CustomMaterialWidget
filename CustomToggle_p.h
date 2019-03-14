#ifndef CustomTOGGLE_P_H
#define CustomTOGGLE_P_H

#include <Qt>

class QStateMachine;
class QState;
class QColor;
class CustomToggle;
class CustomToggleTrack;
class CustomToggleThumb;
class CustomToggleRippleOverlay;

class CustomTogglePrivate
{
	Q_DISABLE_COPY(CustomTogglePrivate)
		Q_DECLARE_PUBLIC(CustomToggle)

public:
	CustomTogglePrivate(CustomToggle *q);
	~CustomTogglePrivate();

	void init();
	void setupProperties();

	CustomToggle              *const q_ptr;
	CustomToggleTrack         *track;
	CustomToggleThumb         *thumb;
	CustomToggleRippleOverlay *rippleOverlay;
	QStateMachine                 *stateMachine;
	QState                        *offState;
	QState                        *onState;
	Qt::Orientation                orientation;
	QColor                         disabledColor;
	QColor                         activeColor;
	QColor                         inactiveColor;
	QColor                         trackColor;
	bool                           useThemeColors;
};

#endif // CustomTOGGLE_P_H

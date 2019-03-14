#ifndef CustomSTATETRANSITIONEVENT_H
#define CustomSTATETRANSITIONEVENT_H

#include <QEvent>

enum CustomStateTransitionType {
	// Snackbar
	SnackbarShowTransition = 1,
	SnackbarHideTransition,
	SnackbarWaitTransition,
	SnackbarNextTransition,
	// FlatButton
	FlatButtonPressedTransition,
	FlatButtonCheckedTransition,
	FlatButtonUncheckedTransition,
	// CollapsibleMenu
	CollapsibleMenuExpand,
	CollapsibleMenuCollapse,
	// Slider
	SliderChangedToMinimum,
	SliderChangedFromMinimum,
	SliderNoFocusMouseEnter,
	SliderNoFocusMouseLeave,
	// Dialog
	DialogShowTransition,
	DialogHideTransition,
	//
	MaxTransitionType = 65535
};

struct CustomStateTransitionEvent : public QEvent
{
	CustomStateTransitionEvent(CustomStateTransitionType type)
		: QEvent(QEvent::Type(QEvent::User + 1)),
		type(type)
	{
	}

	CustomStateTransitionType type;
};

#endif // CustomSTATETRANSITIONEVENT_H

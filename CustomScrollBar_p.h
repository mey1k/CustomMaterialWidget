#ifndef CustomSCROLLBAR_P_H
#define CustomSCROLLBAR_P_H

#include <QtGlobal>
#include <QColor>

class CustomScrollBar;
class CustomScrollBarStateMachine;

class CustomScrollBarPrivate
{
	Q_DISABLE_COPY(CustomScrollBarPrivate)
		Q_DECLARE_PUBLIC(CustomScrollBar)

public:
	CustomScrollBarPrivate(CustomScrollBar *q);
	~CustomScrollBarPrivate();

	void init();

	CustomScrollBar             *const q_ptr;
	CustomScrollBarStateMachine *stateMachine;
	QColor                           backgroundColor;
	QColor                           sliderColor;
	QColor                           canvasColor;
	bool                             hideOnMouseOut;
	bool                             useThemeColors;
};

#endif // CustomSCROLLBAR_P_H

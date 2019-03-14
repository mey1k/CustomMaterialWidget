#ifndef CustomTEXTFIELD_P_H
#define CustomTEXTFIELD_P_H

#include <QtGlobal>
#include <QColor>

class CustomTextField;
class CustomTextFieldStateMachine;
class CustomTextFieldLabel;

class CustomTextFieldPrivate
{
	Q_DISABLE_COPY(CustomTextFieldPrivate)
		Q_DECLARE_PUBLIC(CustomTextField)

public:
	CustomTextFieldPrivate(CustomTextField *q);
	virtual ~CustomTextFieldPrivate();

	void init();

	CustomTextField             *const q_ptr;
	CustomTextFieldStateMachine *stateMachine;
	CustomTextFieldLabel        *label;
	QColor                           textColor;
	QColor                           labelColor;
	QColor                           inkColor;
	QColor                           inputLineColor;
	QString                          labelString;
	qreal                            labelFontSize;
	bool                             showLabel;
	bool                             showInputLine;
	bool                             useThemeColors;
};

#endif // CustomTEXTFIELD_P_H

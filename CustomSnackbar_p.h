#ifndef CustomSNACKBAR_P_H
#define CustomSNACKBAR_P_H

#include <QObject>
#include <QColor>

class CustomSnackbar;
class CustomSnackbarStateMachine;

class CustomSnackbarPrivate
{
	Q_DISABLE_COPY(CustomSnackbarPrivate)
		Q_DECLARE_PUBLIC(CustomSnackbar)

public:
	CustomSnackbarPrivate(CustomSnackbar *q);
	~CustomSnackbarPrivate();

	void init();

	CustomSnackbar             *const q_ptr;
	CustomSnackbarStateMachine *stateMachine;
	QColor                          backgroundColor;
	QColor                          textColor;
	qreal                           bgOpacity;
	QList<QString>                  messages;
	int                             duration;
	int                             boxWidth;
	bool                            clickDismiss;
	bool                            useThemeColors;
};

#endif // CustomSNACKBAR_P_H

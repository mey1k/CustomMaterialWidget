#ifndef CustomDIALOG_P_H
#define CustomDIALOG_P_H

#include <QtGlobal>

class QStateMachine;
class CustomDialog;
class QStackedLayout;
class CustomDialogWindow;
class CustomDialogProxy;

class CustomDialogPrivate
{
	Q_DISABLE_COPY(CustomDialogPrivate)
		Q_DECLARE_PUBLIC(CustomDialog)

public:
	CustomDialogPrivate(CustomDialog *q);
	~CustomDialogPrivate();

	void init();

	CustomDialog       *const q_ptr;
	CustomDialogWindow *dialogWindow;
	QStackedLayout         *proxyStack;
	QStateMachine          *stateMachine;
	CustomDialogProxy  *proxy;
};

#endif // CustomDIALOG_P_H

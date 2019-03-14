#ifndef CustomRAISEDBUTTON_H
#define CustomRAISEDBUTTON_H

#include "Customflatbutton.h"

class CustomRaisedButtonPrivate;

class CustomRaisedButton : public CustomFlatButton
{
	Q_OBJECT

public:
	explicit CustomRaisedButton(QWidget *parent = 0);
	explicit CustomRaisedButton(const QString &text, QWidget *parent = 0);
	~CustomRaisedButton();

protected:
	CustomRaisedButton(CustomRaisedButtonPrivate &d, QWidget *parent = 0);

	bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomRaisedButton)
		Q_DECLARE_PRIVATE(CustomRaisedButton)
};

#endif // CustomRAISEDBUTTON_H

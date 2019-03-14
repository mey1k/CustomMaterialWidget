#ifndef CustomCHECKBOX_H
#define CustomCHECKBOX_H

#include "Customcheckable.h"

class CustomCheckBoxPrivate;

class CustomCheckBox : public CustomCheckable
{
	Q_OBJECT

public:
	explicit CustomCheckBox(QWidget *parent = 0);
	~CustomCheckBox();

private:
	Q_DISABLE_COPY(CustomCheckBox)
		Q_DECLARE_PRIVATE(CustomCheckBox)
};

#endif // CustomCHECKBOX_H

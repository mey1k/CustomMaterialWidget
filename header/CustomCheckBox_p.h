#ifndef CustomCHECKBOX_P_H
#define CustomCHECKBOX_P_H

#include "Customcheckable_p.h"

class CustomCheckBox;

class CustomCheckBoxPrivate : public CustomCheckablePrivate
{
	Q_DISABLE_COPY(CustomCheckBoxPrivate)
		Q_DECLARE_PUBLIC(CustomCheckBox)

public:
	CustomCheckBoxPrivate(CustomCheckBox *q);
	~CustomCheckBoxPrivate();

	void init();
};

#endif // CustomCHECKBOX_P_H

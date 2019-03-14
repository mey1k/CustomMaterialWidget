#ifndef CustomSTYLE_P_H
#define CustomSTYLE_P_H

#include <QtGlobal>

class CustomStyle;
class CustomTheme;

class CustomStylePrivate
{
	Q_DISABLE_COPY(CustomStylePrivate)
		Q_DECLARE_PUBLIC(CustomStyle)

public:
	CustomStylePrivate(CustomStyle *q);
	~CustomStylePrivate();

	void init();

	CustomStyle *const q_ptr;
	CustomTheme *theme;
};

#endif // CustomSTYLE_P_H

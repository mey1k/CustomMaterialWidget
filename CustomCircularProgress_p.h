#ifndef CustomCIRCULARPROGRESS_P_H
#define CustomCIRCULARPROGRESS_P_H

#include <QtGlobal>
#include "Customtheme.h"

class CustomCircularProgress;
class CustomCircularProgressDelegate;

class CustomCircularProgressPrivate
{
	Q_DISABLE_COPY(CustomCircularProgressPrivate)
		Q_DECLARE_PUBLIC(CustomCircularProgress)

public:
	CustomCircularProgressPrivate(CustomCircularProgress *q);
	~CustomCircularProgressPrivate();

	void init();

	CustomCircularProgress         *const q_ptr;
	CustomCircularProgressDelegate *delegate;
	Material::ProgressType              progressType;
	QColor                              color;
	qreal                               penWidth;
	int                                 size;
	bool                                useThemeColors;
};

#endif // CustomCIRCULARPROGRESS_P_H

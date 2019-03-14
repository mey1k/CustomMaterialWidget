#ifndef CustomPROGRESS_P_H
#define CustomPROGRESS_P_H

#include <QtGlobal>
#include <QColor>
#include "Customtheme.h"

class CustomProgress;
class CustomProgressDelegate;

class CustomProgressPrivate
{
	Q_DISABLE_COPY(CustomProgressPrivate)
		Q_DECLARE_PUBLIC(CustomProgress)

public:
	CustomProgressPrivate(CustomProgress *q);
	~CustomProgressPrivate();

	void init();

	CustomProgress         *const q_ptr;
	CustomProgressDelegate *delegate;
	Material::ProgressType      progressType;
	QColor                      progressColor;
	QColor                      backgroundColor;
	bool                        useThemeColors;
};

#endif // CustomPROGRESS_P_H

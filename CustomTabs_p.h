#ifndef CustomTABS_P_H
#define CustomTABS_P_H

#include <QtGlobal>
#include "Customtheme.h"

class QHBoxLayout;
class CustomTabs;
class CustomTabsInkBar;

class CustomTabsPrivate
{
	Q_DISABLE_COPY(CustomTabsPrivate)
		Q_DECLARE_PUBLIC(CustomTabs)

public:
	CustomTabsPrivate(CustomTabs *q);
	~CustomTabsPrivate();

	void init();

	CustomTabs       *const q_ptr;
	CustomTabsInkBar *inkBar;
	QHBoxLayout          *tabLayout;
	Material::RippleStyle rippleStyle;
	QColor                inkColor;
	QColor                backgroundColor;
	QColor                textColor;
	int                   tab;
	bool                  showHalo;
	bool                  useThemeColors;
};

#endif // CustomTABS_P_H

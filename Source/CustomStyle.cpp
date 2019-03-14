#include "stdafx.h"
#include "CustomStyle.h"
#include <QFontDatabase>
#include "CustomTheme.h"

/*!
*  \class CustomStylePrivate
*  \internal
*/

CustomStylePrivate::CustomStylePrivate(CustomStyle *q)
	: q_ptr(q)
{
}

CustomStylePrivate::~CustomStylePrivate()
{
}

void CustomStylePrivate::init()
{
	Q_Q(CustomStyle);

	//QFontDatabase::addApplicationFont(":/font/res/fonts/Roboto/Roboto-Regular.ttf");
	//QFontDatabase::addApplicationFont(":/font/res/fonts/Roboto/Roboto-Medium.ttf");
	//QFontDatabase::addApplicationFont(":/font/res/fonts/Roboto/Roboto-Bold.ttf");
	//QFontDatabase::addApplicationFont(":/font/res/fonts/Notosans/NotoSans-Regular.ttf");

	q->setTheme(new CustomTheme);
}

/*!
*  \class CustomStyle
*  \internal
*/

void CustomStyle::setTheme(CustomTheme *theme)
{
	Q_D(CustomStyle);

	d->theme = theme;
	theme->setParent(this);
}

QColor CustomStyle::themeColor(const QString &key) const
{
	Q_D(const CustomStyle);

	Q_ASSERT(d->theme);

	return d->theme->getColor(key);
}

CustomStyle::CustomStyle()
	: QCommonStyle(),
	d_ptr(new CustomStylePrivate(this))
{
	d_func()->init();
}

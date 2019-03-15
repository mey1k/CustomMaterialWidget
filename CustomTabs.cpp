#include "Customtabs.h"
#include "Customtabs_p.h"
#include <QtWidgets/QHBoxLayout>
#include "Customtabs_internal.h"
#include "Customstyle.h"

/*!
*  \CustomTabsPrivate
*  \internal
*/

CustomTabsPrivate::CustomTabsPrivate(CustomTabs *q)
	: q_ptr(q)
{
}

CustomTabsPrivate::~CustomTabsPrivate()
{
}

void CustomTabsPrivate::CustomTabsPrivate::init()
{
	Q_Q(CustomTabs);

	inkBar = new CustomTabsInkBar(q);
	tabLayout = new QHBoxLayout;
	rippleStyle = Material::CenteredRipple;
	tab = -1;
	showHalo = true;
	useThemeColors = true;

	q->setLayout(tabLayout);
	q->setStyle(&CustomStyle::instance());

	tabLayout->setSpacing(0);
	tabLayout->setMargin(0);
}

/*!
*  \CustomTabs
*/

CustomTabs::CustomTabs(QWidget *parent)
	: QWidget(parent),
	d_ptr(new CustomTabsPrivate(this))
{
	d_func()->init();
}

CustomTabs::~CustomTabs()
{
}

void CustomTabs::setUseThemeColors(bool value)
{
	Q_D(CustomTabs);

	d->useThemeColors = value;
}

bool CustomTabs::useThemeColors() const
{
	Q_D(const CustomTabs);

	return d->useThemeColors;
}

void CustomTabs::setHaloVisible(bool value)
{
	Q_D(CustomTabs);

	d->showHalo = value;
	updateTabs();
}

bool CustomTabs::isHaloVisible() const
{
	Q_D(const CustomTabs);

	return d->showHalo;
}

void CustomTabs::setRippleStyle(Material::RippleStyle style)
{
	Q_D(CustomTabs);

	d->rippleStyle = style;
	updateTabs();
}

Material::RippleStyle CustomTabs::rippleStyle() const
{
	Q_D(const CustomTabs);

	return d->rippleStyle;
}

void CustomTabs::setInkColor(const QColor &color)
{
	Q_D(CustomTabs);

	d->inkColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		d->inkBar->update();
	update();
}

QColor CustomTabs::inkColor() const
{
	Q_D(const CustomTabs);

	if (d->useThemeColors || !d->inkColor.isValid()) {
		return CustomStyle::instance().themeColor("accent1");
	}
	else {
		return d->inkColor;
	}
}

void CustomTabs::setBackgroundColor(const QColor &color)
{
	Q_D(CustomTabs);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		updateTabs();
	update();
}

QColor CustomTabs::backgroundColor() const
{
	Q_D(const CustomTabs);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CustomStyle::instance().themeColor("primary1");
	}
	else {
		return d->backgroundColor;
	}
}

void CustomTabs::setTextColor(const QColor &color)
{
	Q_D(CustomTabs);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		updateTabs();
	update();
}

QColor CustomTabs::textColor() const
{
	Q_D(const CustomTabs);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CustomStyle::instance().themeColor("canvas");
	}
	else {
		return d->textColor;
	}
}

void CustomTabs::setCurrentTab(CustomTab *tab)
{
	Q_D(CustomTabs);

	setCurrentTab(d->tabLayout->indexOf(tab));
}

void CustomTabs::setCurrentTab(int index)
{
	Q_D(CustomTabs);

	setTabActive(d->tab, false);
	d->tab = index;
	setTabActive(index, true);
	d->inkBar->animate();

	emit currentChanged(index);
}

void CustomTabs::addTab(const QString &text, const QIcon &icon)
{
	Q_D(CustomTabs);

	CustomTab *tab = new CustomTab(this);
	tab->setText(text);
	tab->setHaloVisible(isHaloVisible());
	tab->setRippleStyle(rippleStyle());

	if (!icon.isNull()) {
		tab->setIcon(icon);
		tab->setIconSize(QSize(22, 22));
	}

	d->tabLayout->addWidget(tab);

	if (-1 == d->tab) {
		d->tab = 0;
		d->inkBar->refreshGeometry();
		d->inkBar->raise();
		tab->setActive(true);
	}
}

int CustomTabs::currentIndex() const
{
	Q_D(const CustomTabs);

	return d->tab;
}

void CustomTabs::setTabActive(int index, bool active)
{
	Q_D(CustomTabs);

	CustomTab *tab;

	if (index > -1) {
		tab = static_cast<CustomTab *>(d->tabLayout->itemAt(index)->widget());
		if (tab) {
			tab->setActive(active);
		}
	}
}

void CustomTabs::updateTabs()
{
	Q_D(CustomTabs);

	CustomTab *tab;
	for (int i = 0; i < d->tabLayout->count(); ++i) {
		QLayoutItem *item = d->tabLayout->itemAt(i);
		if ((tab = static_cast<CustomTab *>(item->widget()))) {
			tab->setRippleStyle(d->rippleStyle);
			tab->setHaloVisible(d->showHalo);
			tab->setBackgroundColor(backgroundColor());
			tab->setForegroundColor(textColor());
		}
	}
}

#include "stdafx.h"
#include "Customcheckbox.h"
#include "Customcheckbox_p.h"
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>
#include "Customcheckable_internal.h"

/*!
*  \class CustomCheckBoxPrivate
*  \internal
*/

/*!
*  \internal
*/
CustomCheckBoxPrivate::CustomCheckBoxPrivate(CustomCheckBox *q)
	: CustomCheckablePrivate(q)
{
}

/*!
*  \internal
*/
CustomCheckBoxPrivate::~CustomCheckBoxPrivate()
{
}

/*!
*  \internal
*/
void CustomCheckBoxPrivate::init()
{
	Q_Q(CustomCheckBox);

	checkedState->assignProperty(checkedIcon, "iconSize", 24);
	uncheckedState->assignProperty(checkedIcon, "iconSize", 0);

	QPropertyAnimation *animation;

	animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
	animation->setDuration(300);
	uncheckedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
	animation->setDuration(1300);
	checkedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(checkedIcon, "opacity", q);
	animation->setDuration(440);
	checkedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(checkedIcon, "opacity", q);
	animation->setDuration(440);
	uncheckedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
	animation->setDuration(440);
	checkedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
	animation->setDuration(440);
	uncheckedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(uncheckedIcon, "color", q);
	animation->setDuration(440);
	checkedTransition->addAnimation(animation);

	animation = new QPropertyAnimation(uncheckedIcon, "color", q);
	animation->setDuration(440);
	uncheckedTransition->addAnimation(animation);
}

/*!
*  \class CustomCheckBox
*/

CustomCheckBox::CustomCheckBox(QWidget *parent)
	: CustomCheckable(*new CustomCheckBoxPrivate(this), parent)
{
	d_func()->init();
}

CustomCheckBox::~CustomCheckBox()
{
}

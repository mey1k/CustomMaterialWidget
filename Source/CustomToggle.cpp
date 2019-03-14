#include "stdafx.h"
#include "Customtoggle.h"
#include "Customtoggle_p.h"
#include <QtWidgets/QApplication>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "Customtoggle_internal.h"
#include "Customstyle.h"


/*!
*  \class CustomTogglePrivate
*  \internal
*/

CustomTogglePrivate::CustomTogglePrivate(CustomToggle *q)
	: q_ptr(q)
{
}

CustomTogglePrivate::~CustomTogglePrivate()
{
}

void CustomTogglePrivate::init()
{
	Q_Q(CustomToggle);

	track = new CustomToggleTrack(q);
	thumb = new CustomToggleThumb(q);
	rippleOverlay = new CustomToggleRippleOverlay(thumb, track, q);
	stateMachine = new QStateMachine(q);
	offState = new QState;
	onState = new QState;
	orientation = Qt::Horizontal;
	useThemeColors = true;

	q->setCheckable(true);
	q->setChecked(false);
	q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	stateMachine->addState(offState);
	stateMachine->addState(onState);
	stateMachine->setInitialState(offState);

	offState->assignProperty(thumb, "shift", 0);
	onState->assignProperty(thumb, "shift", 1);

	QSignalTransition *transition;
	QPropertyAnimation *animation;

	//

	transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
	transition->setTargetState(onState);
	offState->addTransition(transition);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("shift");
	animation->setTargetObject(thumb);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::OutQuad);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("trackColor");
	animation->setTargetObject(track);
	animation->setDuration(150);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("thumbColor");
	animation->setTargetObject(thumb);
	animation->setDuration(150);
	transition->addAnimation(animation);

	//

	transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
	transition->setTargetState(offState);
	onState->addTransition(transition);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("shift");
	animation->setTargetObject(thumb);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::OutQuad);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("trackColor");
	animation->setTargetObject(track);
	animation->setDuration(150);
	transition->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("thumbColor");
	animation->setTargetObject(thumb);
	animation->setDuration(150);
	transition->addAnimation(animation);

	//

	setupProperties();

	stateMachine->start();
	QCoreApplication::processEvents();
}

void CustomTogglePrivate::setupProperties()
{
	Q_Q(CustomToggle);

	if (q->isEnabled()) {
		const qreal shift = thumb->shift();
		if (qFuzzyCompare(shift, 1)) {
			thumb->setThumbColor(q->activeColor());
			track->setTrackColor(q->activeColor().lighter(110));
		}
		else if (qFuzzyCompare(1 + shift, 1)) {
			thumb->setThumbColor(q->inactiveColor());
			track->setTrackColor(q->trackColor());
		}
	}

	offState->assignProperty(track, "trackColor", q->trackColor().lighter(110));
	onState->assignProperty(track, "trackColor", q->activeColor().lighter(110));

	offState->assignProperty(thumb, "thumbColor", q->inactiveColor());
	onState->assignProperty(thumb, "thumbColor", q->activeColor());

	q->update();
}

/*!
*  \class CustomToggle
*/

CustomToggle::CustomToggle(QWidget *parent)
	: QAbstractButton(parent),
	d_ptr(new CustomTogglePrivate(this))
{
	d_func()->init();
}

CustomToggle::~CustomToggle()
{
}

void CustomToggle::setUseThemeColors(bool value)
{
	Q_D(CustomToggle);

	d->useThemeColors = value;
	d->setupProperties();
}

bool CustomToggle::useThemeColors() const
{
	Q_D(const CustomToggle);

	return d->useThemeColors;
}

void CustomToggle::setDisabledColor(const QColor &color)
{
	Q_D(CustomToggle);

	d->disabledColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		d->setupProperties();
}

QColor CustomToggle::disabledColor() const
{
	Q_D(const CustomToggle);

	if (d->useThemeColors || !d->disabledColor.isValid()) {
		return CustomStyle::instance().themeColor("disabled");
	}
	else {
		return d->disabledColor;
	}
}

void CustomToggle::setActiveColor(const QColor &color)
{
	Q_D(CustomToggle);

	d->activeColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		d->setupProperties();
}

QColor CustomToggle::activeColor() const
{
	Q_D(const CustomToggle);

	if (d->useThemeColors || !d->activeColor.isValid()) {
		return CustomStyle::instance().themeColor("primary1");
	}
	else {
		return d->activeColor;
	}
}

void CustomToggle::setInactiveColor(const QColor &color)
{
	Q_D(CustomToggle);

	d->inactiveColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		d->setupProperties();
}

QColor CustomToggle::inactiveColor() const
{
	Q_D(const CustomToggle);

	if (d->useThemeColors || !d->inactiveColor.isValid()) {
		return CustomStyle::instance().themeColor("canvas");
	}
	else {
		return d->inactiveColor;
	}
}

void CustomToggle::setTrackColor(const QColor &color)
{
	Q_D(CustomToggle);

	d->trackColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		d->setupProperties();
}

QColor CustomToggle::trackColor() const
{
	Q_D(const CustomToggle);

	if (d->useThemeColors || !d->trackColor.isValid()) {
		return CustomStyle::instance().themeColor("accent3");
	}
	else {
		return d->trackColor;
	}
}

void CustomToggle::setOrientation(Qt::Orientation orientation)
{
	Q_D(CustomToggle);

	if (d->orientation == orientation) {
		return;
	}

	d->orientation = orientation;
	updateGeometry();
}

Qt::Orientation CustomToggle::orientation() const
{
	Q_D(const CustomToggle);

	return d->orientation;
}

QSize CustomToggle::sizeHint() const
{
	Q_D(const CustomToggle);

	return Qt::Horizontal == d->orientation
		? QSize(64, 48)
		: QSize(48, 64);
}

bool CustomToggle::event(QEvent *event)
{
	Q_D(CustomToggle);

	switch (event->type())
	{
	case QEvent::ParentChange:
	{
		QWidget *widget;
		if ((widget = parentWidget())) {
			d->rippleOverlay->setParent(widget);
		}
		break;
	}
	default:
		break;
	}
	return QAbstractButton::event(event);
}

void CustomToggle::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)
}

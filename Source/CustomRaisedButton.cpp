#include "stdafx.h"
#include "Customraisedbutton.h"
#include "Customraisedbutton_p.h"
#include <QStateMachine>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QEventTransition>

/*!
*  \class CustomRaisedButtonPrivate
*  \internal
*/

/*!
*  \internal
*/
CustomRaisedButtonPrivate::CustomRaisedButtonPrivate(CustomRaisedButton *q)
	: CustomFlatButtonPrivate(q)
{
}

/*!
*  \internal
*/
CustomRaisedButtonPrivate::~CustomRaisedButtonPrivate()
{
}

/*!
*  \internal
*/
void CustomRaisedButtonPrivate::init()
{
	Q_Q(CustomRaisedButton);

	shadowStateMachine = new QStateMachine(q);
	normalState = new QState;
	pressedState = new QState;
	effect = new QGraphicsDropShadowEffect;

	effect->setBlurRadius(7);
	effect->setOffset(QPointF(0, 2));
	effect->setColor(QColor(0, 0, 0, 75));

	q->setBackgroundMode(Qt::OpaqueMode);
	q->setMinimumHeight(42);
	q->setGraphicsEffect(effect);
	q->setBaseOpacity(0.3);

	shadowStateMachine->addState(normalState);
	shadowStateMachine->addState(pressedState);

	normalState->assignProperty(effect, "offset", QPointF(0, 2));
	normalState->assignProperty(effect, "blurRadius", 7);

	pressedState->assignProperty(effect, "offset", QPointF(0, 5));
	pressedState->assignProperty(effect, "blurRadius", 29);

	QAbstractTransition *transition;

	transition = new QEventTransition(q, QEvent::MouseButtonPress);
	transition->setTargetState(pressedState);
	normalState->addTransition(transition);

	transition = new QEventTransition(q, QEvent::MouseButtonDblClick);
	transition->setTargetState(pressedState);
	normalState->addTransition(transition);

	transition = new QEventTransition(q, QEvent::MouseButtonRelease);
	transition->setTargetState(normalState);
	pressedState->addTransition(transition);

	QPropertyAnimation *animation;

	animation = new QPropertyAnimation(effect, "offset", q);
	animation->setDuration(100);
	shadowStateMachine->addDefaultAnimation(animation);

	animation = new QPropertyAnimation(effect, "blurRadius", q);
	animation->setDuration(100);
	shadowStateMachine->addDefaultAnimation(animation);

	shadowStateMachine->setInitialState(normalState);
	shadowStateMachine->start();
}

/*!
*  \class CustomRaisedButton
*/

CustomRaisedButton::CustomRaisedButton(QWidget *parent)
	: CustomFlatButton(*new CustomRaisedButtonPrivate(this), parent)
{
	d_func()->init();
}

CustomRaisedButton::CustomRaisedButton(const QString &text, QWidget *parent)
	: CustomFlatButton(*new CustomRaisedButtonPrivate(this), parent)
{
	d_func()->init();

	setText(text);
}

CustomRaisedButton::~CustomRaisedButton()
{
}

CustomRaisedButton::CustomRaisedButton(CustomRaisedButtonPrivate &d, QWidget *parent)
	: CustomFlatButton(d, parent)
{
	d_func()->init();
}

bool CustomRaisedButton::event(QEvent *event)
{
	Q_D(CustomRaisedButton);

	if (QEvent::EnabledChange == event->type()) {
		if (isEnabled()) {
			d->shadowStateMachine->start();
			d->effect->setEnabled(true);
		}
		else {
			d->shadowStateMachine->stop();
			d->effect->setEnabled(false);
		}
	}
	return CustomFlatButton::event(event);
}

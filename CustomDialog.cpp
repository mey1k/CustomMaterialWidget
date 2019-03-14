#include "stdafx.h"
#include "Customdialog.h"
#include "Customdialog_p.h"
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QStateMachine>
#include <QState>
#include <QtWidgets/QApplication>
#include <QPropertyAnimation>
#include <QPainter>
#include "Customdialog_internal.h"
#include "Customstatetransition.h"

/*!
*  \class CustomDialogPrivate
*  \internal
*/

CustomDialogPrivate::CustomDialogPrivate(CustomDialog *q)
	: q_ptr(q)
{
}

CustomDialogPrivate::~CustomDialogPrivate()
{
}

void CustomDialogPrivate::init()
{
	Q_Q(CustomDialog);

	dialogWindow = new CustomDialogWindow(q);
	proxyStack = new QStackedLayout;
	stateMachine = new QStateMachine(q);
	proxy = new CustomDialogProxy(dialogWindow, proxyStack, q);

	QVBoxLayout *layout = new QVBoxLayout;
	q->setLayout(layout);

	QWidget *widget = new QWidget;
	widget->setLayout(proxyStack);
	widget->setMinimumWidth(400);

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setColor(QColor(0, 0, 0, 200));
	effect->setBlurRadius(64);
	effect->setOffset(0, 13);
	widget->setGraphicsEffect(effect);

	layout->addWidget(widget);
	layout->setAlignment(widget, Qt::AlignCenter);

	proxyStack->addWidget(dialogWindow);
	proxyStack->addWidget(proxy);
	proxyStack->setCurrentIndex(1);

	q->setAttribute(Qt::WA_TransparentForMouseEvents);

	QState *hiddenState = new QState;
	QState *visibleState = new QState;

	stateMachine->addState(hiddenState);
	stateMachine->addState(visibleState);
	stateMachine->setInitialState(hiddenState);

	CustomStateTransition *transition;

	transition = new CustomStateTransition(DialogShowTransition);
	transition->setTargetState(visibleState);
	hiddenState->addTransition(transition);

	transition = new CustomStateTransition(DialogHideTransition);
	transition->setTargetState(hiddenState);
	visibleState->addTransition(transition);

	visibleState->assignProperty(proxy, "opacity", 1);
	visibleState->assignProperty(effect, "color", QColor(0, 0, 0, 200));
	visibleState->assignProperty(dialogWindow, "offset", 0);
	hiddenState->assignProperty(proxy, "opacity", 0);
	hiddenState->assignProperty(effect, "color", QColor(0, 0, 0, 0));
	hiddenState->assignProperty(dialogWindow, "offset", 200);

	QPropertyAnimation *animation;

	animation = new QPropertyAnimation(proxy, "opacity", q);
	animation->setDuration(280);
	stateMachine->addDefaultAnimation(animation);

	animation = new QPropertyAnimation(effect, "color", q);
	animation->setDuration(280);
	stateMachine->addDefaultAnimation(animation);

	animation = new QPropertyAnimation(dialogWindow, "offset", q);
	animation->setDuration(280);
	animation->setEasingCurve(QEasingCurve::OutCirc);
	stateMachine->addDefaultAnimation(animation);

	QObject::connect(visibleState, SIGNAL(propertiesAssigned()),
		proxy, SLOT(makeOpaque()));
	QObject::connect(hiddenState, SIGNAL(propertiesAssigned()),
		proxy, SLOT(makeTransparent()));

	stateMachine->start();
	QCoreApplication::processEvents();
}

/*!
*  \class CustomDialog
*/

CustomDialog::CustomDialog(QWidget *parent)
	: CustomOverlayWidget(parent),
	d_ptr(new CustomDialogPrivate(this))
{
	d_func()->init();

	cautionWrapper = new CautionWidget();
	cautionWrapper->setGeometry(cautionWrapper->rec.width()/2 - (70 * cautionWrapper->correctScaleW)/2, cautionWrapper->rec.height()/2 - (70 * cautionWrapper->correctScaleW) / 2
		- 80 * cautionWrapper->correctScaleH, 70 * cautionWrapper->correctScaleW, 70 * cautionWrapper->correctScaleH);
	cautionWrapper->resize(70 * cautionWrapper->correctScaleW, 70 * cautionWrapper->correctScaleH);
	cautionWrapper->setParent(this);
	cautionWrapper->setCautionImage();
	cautionWrapper->hide();
}

CustomDialog::~CustomDialog()
{
}

QLayout *CustomDialog::windowLayout() const
{
	Q_D(const CustomDialog);

	return d->dialogWindow->layout();
}

void CustomDialog::setWindowLayout(QLayout *layout)
{
	Q_D(CustomDialog);

	d->dialogWindow->setLayout(layout);
}

void CustomDialog::showDialog()
{
	Q_D(CustomDialog);

	d->stateMachine->postEvent(new CustomStateTransitionEvent(DialogShowTransition));

	raise();

	//caution->setWrapperGeometry(this->width() / 2, this->height() / 2);

	cautionWrapper->show();
}

void CustomDialog::hideDialog()
{
	Q_D(CustomDialog);

	d->stateMachine->postEvent(new CustomStateTransitionEvent(DialogHideTransition));
	setAttribute(Qt::WA_TransparentForMouseEvents);
	d->proxyStack->setCurrentIndex(1);
	
	cautionWrapper->hide();
}

void CustomDialog::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomDialog);

	QPainter painter(this);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::black);
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);
	painter.setOpacity(d->proxy->opacity() / 2.4);
	painter.drawRect(QWidget::rect());
}

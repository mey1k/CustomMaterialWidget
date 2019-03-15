#include "Customcheckable.h"
#include "Customcheckable_p.h"
#include <QPainter>
#include <QEvent>
#include <QStateMachine>
#include <QSignalTransition>
#include <QEventTransition>
#include <QColor>
#include <QCoreApplication>
#include "Customrippleoverlay.h"
#include "Customripple.h"
#include "Customstyle.h"
#include "Customcheckable_internal.h"

/*!
*  \class CustomCheckablePrivate
*  \internal
*/

CustomCheckablePrivate::CustomCheckablePrivate(CustomCheckable *q)
	: q_ptr(q)
{
}


CustomCheckablePrivate::~CustomCheckablePrivate()
{
}

void CustomCheckablePrivate::init()
{
	Q_Q(CustomCheckable);

	rippleOverlay = new CustomRippleOverlay;
	checkedIcon = new CustomCheckableIcon(QIcon(":/ThemeWhiteRed/res/svg/whiteRed/check_box_check_select.svg"), q);
	uncheckedIcon = new CustomCheckableIcon(QIcon(":/ThemeWhiteRed/res/svg/whiteRed/check_box_outline_blank.svg"), q);
	stateMachine = new QStateMachine(q);
	uncheckedState = new QState;
	checkedState = new QState;
	disabledUncheckedState = new QState;
	disabledCheckedState = new QState;
	uncheckedTransition = new QSignalTransition(q, SIGNAL(toggled(bool)));
	checkedTransition = new QSignalTransition(q, SIGNAL(toggled(bool)));
	labelPosition = CustomCheckable::LabelPositionRight;
	useThemeColors = true;

	rippleOverlay->setParent(q->parentWidget());
	rippleOverlay->installEventFilter(q);

	q->setCheckable(true);
	q->setStyle(&CustomStyle::instance());
	q->setFont(QFont("Roboto", 11, QFont::Normal));

	stateMachine->addState(uncheckedState);
	stateMachine->addState(checkedState);
	stateMachine->addState(disabledUncheckedState);
	stateMachine->addState(disabledCheckedState);
	stateMachine->setInitialState(uncheckedState);

	// Transition to checked

	uncheckedTransition->setTargetState(checkedState);
	uncheckedState->addTransition(uncheckedTransition);

	// Transition to unchecked

	checkedTransition->setTargetState(uncheckedState);
	checkedState->addTransition(checkedTransition);

	QAbstractTransition *transition;

	// Transitions enabled <==> disabled

	transition = new QEventTransition(q, QEvent::EnabledChange);
	transition->setTargetState(disabledUncheckedState);
	uncheckedState->addTransition(transition);

	transition = new QEventTransition(q, QEvent::EnabledChange);
	transition->setTargetState(uncheckedState);
	disabledUncheckedState->addTransition(transition);

	transition = new QEventTransition(q, QEvent::EnabledChange);
	transition->setTargetState(disabledCheckedState);
	checkedState->addTransition(transition);

	transition = new QEventTransition(q, QEvent::EnabledChange);
	transition->setTargetState(checkedState);
	disabledCheckedState->addTransition(transition);

	transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
	transition->setTargetState(disabledCheckedState);
	disabledUncheckedState->addTransition(transition);

	transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
	transition->setTargetState(disabledUncheckedState);
	disabledCheckedState->addTransition(transition);

	//

	checkedState->assignProperty(checkedIcon, "opacity", 1);
	checkedState->assignProperty(uncheckedIcon, "opacity", 0);

	uncheckedState->assignProperty(checkedIcon, "opacity", 0);
	uncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

	disabledCheckedState->assignProperty(checkedIcon, "opacity", 1);
	disabledCheckedState->assignProperty(uncheckedIcon, "opacity", 0);

	disabledUncheckedState->assignProperty(checkedIcon, "opacity", 0);
	disabledUncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

	checkedState->assignProperty(checkedIcon, "color", q->checkedColor());
	checkedState->assignProperty(uncheckedIcon, "color", q->checkedColor());

	uncheckedState->assignProperty(uncheckedIcon, "color", q->uncheckedColor());
	uncheckedState->assignProperty(uncheckedIcon, "color", q->uncheckedColor());

	disabledUncheckedState->assignProperty(uncheckedIcon, "color", q->disabledColor());
	disabledCheckedState->assignProperty(checkedIcon, "color", q->disabledColor());

	stateMachine->start();
	QCoreApplication::processEvents();
}

/*!
*  \class CustomCheckable
*/

CustomCheckable::CustomCheckable(QWidget *parent)
	: QAbstractButton(parent),
	d_ptr(new CustomCheckablePrivate(this))
{
	d_func()->init();
}

CustomCheckable::~CustomCheckable()
{
}

void CustomCheckable::setLabelPosition(LabelPosition placement)
{
	Q_D(CustomCheckable);

	d->labelPosition = placement;
	update();
}

CustomCheckable::LabelPosition CustomCheckable::labelPosition() const
{
	Q_D(const CustomCheckable);

	return d->labelPosition;
}

void CustomCheckable::setUseThemeColors(bool value)
{
	Q_D(CustomCheckable);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	setupProperties();
}

bool CustomCheckable::useThemeColors() const
{
	Q_D(const CustomCheckable);

	return d->useThemeColors;
}

void CustomCheckable::setCheckedColor(const QColor &color)
{
	Q_D(CustomCheckable);

	d->checkedColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		setupProperties();
}

QColor CustomCheckable::checkedColor() const
{
	Q_D(const CustomCheckable);

	if (d->useThemeColors || !d->checkedColor.isValid()) {
		return CustomStyle::instance().themeColor("primary1");
	}
	else {
		return d->checkedColor;
	}
}

void CustomCheckable::setUncheckedColor(const QColor &color)
{
	Q_D(CustomCheckable);

	d->uncheckedColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		setupProperties();
}

QColor CustomCheckable::uncheckedColor() const
{
	Q_D(const CustomCheckable);

	if (d->useThemeColors || !d->uncheckedColor.isValid()) {
		return CustomStyle::instance().themeColor("text");
	}
	else {
		return d->uncheckedColor;
	}
}

void CustomCheckable::setTextColor(const QColor &color)
{
	Q_D(CustomCheckable);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		setupProperties();
}

QColor CustomCheckable::textColor() const
{
	Q_D(const CustomCheckable);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CustomStyle::instance().themeColor("text");
	}
	else {
		return d->textColor;
	}
}

void CustomCheckable::setDisabledColor(const QColor &color)
{
	Q_D(CustomCheckable);

	d->disabledColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		setupProperties();
}

QColor CustomCheckable::disabledColor() const
{
	Q_D(const CustomCheckable);

	if (d->useThemeColors || !d->disabledColor.isValid()) {
		return CustomStyle::instance().themeColor("accent3");
	}
	else {
		return d->disabledColor;
	}
}

void CustomCheckable::setCheckedIcon(const QIcon &icon)
{
	Q_D(CustomCheckable);

	d->checkedIcon->setIcon(icon);
	update();
}

QIcon CustomCheckable::checkedIcon() const
{
	Q_D(const CustomCheckable);

	return d->checkedIcon->icon();
}

void CustomCheckable::setUncheckedIcon(const QIcon &icon)
{
	Q_D(CustomCheckable);

	d->uncheckedIcon->setIcon(icon);
	update();
}

QIcon CustomCheckable::uncheckedIcon() const
{
	Q_D(const CustomCheckable);

	return d->uncheckedIcon->icon();
}

/*!
*  \reimp
*/
QSize CustomCheckable::sizeHint() const
{
	if (text().isEmpty()) {
		return QSize(40, 40);
	}
	return QSize(fontMetrics().size(Qt::TextShowMnemonic, text()).width() + 52, 40);
}

CustomCheckable::CustomCheckable(CustomCheckablePrivate &d, QWidget *parent)
	: QAbstractButton(parent),
	d_ptr(&d)
{
	d_func()->init();
}

/*!
*  \reimp
*/
bool CustomCheckable::event(QEvent *event)
{
	Q_D(CustomCheckable);

	switch (event->type())
	{
	case QEvent::Resize:
	case QEvent::Move:
		d->checkedIcon->setGeometry(rect());
		d->uncheckedIcon->setGeometry(rect());
		d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
		break;
	case QEvent::ParentChange:
		QWidget * widget;
		if ((widget = parentWidget())) {
			d->rippleOverlay->setParent(widget);
		}
		break;
	default:
		break;
	}
	return QAbstractButton::event(event);
}

/*!
*  \reimp
*/
bool CustomCheckable::eventFilter(QObject *obj, QEvent *event)
{
	if (QEvent::Resize == event->type())
	{
		Q_D(CustomCheckable);

		d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
	}
	return QAbstractButton::eventFilter(obj, event);
}

/*!
*  \reimp
*/
void CustomCheckable::mousePressEvent(QMouseEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomCheckable);

	if (!isEnabled()) {
		return;
	}

	CustomRipple *ripple;
	if (CustomCheckable::LabelPositionLeft == d->labelPosition) {
		ripple = new CustomRipple(QPoint(width() - 14, 28));
	}
	else {
		ripple = new CustomRipple(QPoint(28, 28));
	}
	ripple->setRadiusEndValue(22);
	ripple->setColor(isChecked() ? checkedColor() : uncheckedColor());
	if (isChecked()) {
		ripple->setOpacityStartValue(1);
	}
	d->rippleOverlay->addRipple(ripple);

	setChecked(!isChecked());
}

/*!
*  \reimp
*/
void CustomCheckable::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomCheckable);

	QPainter painter(this);

	QPen pen;
	pen.setColor(isEnabled() ? textColor() : disabledColor());
	painter.setPen(pen);

	if (CustomCheckable::LabelPositionLeft == d->labelPosition) {
		painter.drawText(4, 25, text());
	}
	else {
		painter.drawText(48, 25, text());
	}
}

void CustomCheckable::setupProperties()
{
	Q_D(CustomCheckable);

	d->checkedState->assignProperty(d->checkedIcon, "color", checkedColor());
	d->checkedState->assignProperty(d->uncheckedIcon, "color", checkedColor());
	d->uncheckedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
	d->disabledUncheckedState->assignProperty(d->uncheckedIcon, "color", disabledColor());
	d->disabledCheckedState->assignProperty(d->checkedIcon, "color", disabledColor());

	if (isEnabled()) {
		if (isChecked()) {
			d->checkedIcon->setColor(checkedColor());
		}
		else {
			d->uncheckedIcon->setColor(uncheckedColor());
		}
	}
	else {
		d->checkedIcon->setColor(disabledColor());
		d->uncheckedIcon->setColor(disabledColor());
	}

	update();
}

#include "Customsnackbar.h"
#include "Customsnackbar_p.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "Customsnackbar_internal.h"
#include "Customstyle.h"
#include "Customstatetransition.h"
#include <QDebug>

/*!
*  \class CustomSnackbarPrivate
*  \internal
*/

CustomSnackbarPrivate::CustomSnackbarPrivate(CustomSnackbar *q)
	: q_ptr(q)
{
}

CustomSnackbarPrivate::~CustomSnackbarPrivate()
{
}

void CustomSnackbarPrivate::init()
{
	Q_Q(CustomSnackbar);

	stateMachine = new CustomSnackbarStateMachine(q);
	bgOpacity = 0.9;
	duration = 3000;
	boxWidth = 300;
	clickDismiss = false;
	useThemeColors = true;

	q->setAttribute(Qt::WA_TransparentForMouseEvents);

	QFont font("Roboto", 10, QFont::Medium);
	font.setCapitalization(QFont::AllUppercase);
	q->setFont(font);

	stateMachine->start();
	QCoreApplication::processEvents();
}

/*!
*  \class CustomSnackbar
*/

CustomSnackbar::CustomSnackbar(QWidget *parent)
	: CustomOverlayWidget(parent),
	d_ptr(new CustomSnackbarPrivate(this))
{
	d_func()->init();
}

CustomSnackbar::~CustomSnackbar()
{
}


void CustomSnackbar::setAutoHideDuration(int duration)
{
	Q_D(CustomSnackbar);

	d->duration = duration;

}

int CustomSnackbar::autoHideDuration() const
{
	Q_D(const CustomSnackbar);

	return d->duration;
}

void CustomSnackbar::setUseThemeColors(bool value)
{
	Q_D(CustomSnackbar);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CustomSnackbar::useThemeColors() const
{
	Q_D(const CustomSnackbar);

	return d->useThemeColors;
}

void CustomSnackbar::setBackgroundColor(const QColor &color)
{
	Q_D(CustomSnackbar);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomSnackbar::backgroundColor() const
{
	Q_D(const CustomSnackbar);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CustomStyle::instance().themeColor("text");
	}
	else {
		return d->backgroundColor;
	}
}

void CustomSnackbar::setBackgroundOpacity(qreal opacity)
{
	Q_D(CustomSnackbar);

	d->bgOpacity = opacity;
	update();
}

qreal CustomSnackbar::backgroundOpacity() const
{
	Q_D(const CustomSnackbar);

	return d->bgOpacity;
}

void CustomSnackbar::setTextColor(const QColor &color)
{
	Q_D(CustomSnackbar);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomSnackbar::textColor() const
{
	Q_D(const CustomSnackbar);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CustomStyle::instance().themeColor("canvas");
	}
	else {
		return d->textColor;
	}
}

void CustomSnackbar::setFontSize(qreal size)
{
	QFont f(font());
	f.setPointSizeF(size);
	setFont(f);

	update();
}

qreal CustomSnackbar::fontSize() const
{
	return font().pointSizeF();
}

void CustomSnackbar::setBoxWidth(int width)
{
	Q_D(CustomSnackbar);

	d->boxWidth = width;

	update();
}

int CustomSnackbar::boxWidth() const
{
	Q_D(const CustomSnackbar);

	return d->boxWidth;
}

void CustomSnackbar::setClickToDismissMode(bool value)
{
	Q_D(CustomSnackbar);

	d->clickDismiss = value;
}

bool CustomSnackbar::clickToDismissMode() const
{
	Q_D(const CustomSnackbar);

	return d->clickDismiss;
}

void CustomSnackbar::addMessage(const QString &message)
{
	Q_D(CustomSnackbar);

	d->messages.push_back(message);
	d->stateMachine->postEvent(new CustomStateTransitionEvent(SnackbarShowTransition));
	raise();
}

void CustomSnackbar::addInstantMessage(const QString &message)
{
	Q_D(CustomSnackbar);

	if (d->messages.isEmpty()) {
		d->messages.push_back(message);
	}
	else {
		d->messages.insert(1, message);
	}

	d->stateMachine->progress();
}

void CustomSnackbar::dequeue()
{
	Q_D(CustomSnackbar);

	if (d->messages.isEmpty()) {
		return;
	}

	d->messages.removeFirst();

	if (!d->messages.isEmpty()) {
		d->stateMachine->postEvent(new CustomStateTransitionEvent(SnackbarNextTransition));
	}
	else {
		d->stateMachine->postEvent(new CustomStateTransitionEvent(SnackbarWaitTransition));
	}
}

void CustomSnackbar::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomSnackbar);

	if (d->messages.isEmpty()) {
		return;
	}

	QString message = d->messages.first();

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(backgroundColor());
	painter.setBrush(brush);
	painter.setOpacity(d->bgOpacity);

	QRect r(0, 0, d->boxWidth, 40);

	painter.setPen(Qt::white);
	QRect br = painter.boundingRect(r, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);

	painter.setPen(Qt::NoPen);
	r = br.united(r).adjusted(-10, -10, 10, 20);

	const qreal s = 1 - d->stateMachine->offset();

	painter.translate((width() - (r.width() - 20)) / 2,
		height() + 10 - s * (r.height()));

	
	br.moveCenter(r.center()); // text move to center
	
	painter.drawRoundedRect(r.adjusted(0, 0, 0, 3), 3, 3); // draw rectangle
	painter.setPen(textColor());
	painter.drawText(br, Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, message);
}

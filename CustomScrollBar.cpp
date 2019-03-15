#include "Customscrollbar.h"
#include "Customscrollbar_p.h"
#include <QPainter>
#include <QDebug>
#include "Customscrollbar_internal.h"
#include "Customstyle.h"

/*!
*  \class CustomScrollBarPrivate
*  \internal
*/

CustomScrollBarPrivate::CustomScrollBarPrivate(CustomScrollBar *q)
	: q_ptr(q)
{
}

CustomScrollBarPrivate::~CustomScrollBarPrivate()
{
}

void CustomScrollBarPrivate::init()
{
	Q_Q(CustomScrollBar);

	stateMachine = new CustomScrollBarStateMachine(q);
	hideOnMouseOut = true;
	useThemeColors = true;

	q->setMouseTracking(true);
	q->setStyle(&CustomStyle::instance());
	q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
		"QScrollBar::add-line:vertical { height: 0; margin: 0; }"
		"QScrollBar::sub-line:vertical { height: 0; margin: 0; }");

	stateMachine->start();
}

/*!
*  \class CustomScrollBar
*/

CustomScrollBar::CustomScrollBar(QWidget *parent)
	: QScrollBar(parent),
	d_ptr(new CustomScrollBarPrivate(this))
{
	d_func()->init();
}

CustomScrollBar::~CustomScrollBar()
{
}

/*!
*  \reimp
*/
QSize CustomScrollBar::sizeHint() const
{
	if (Qt::Horizontal == orientation()) {
		return QSize(1, 10);
	}
	else {
		return QSize(10, 1);
	}
}

void CustomScrollBar::setUseThemeColors(bool value)
{
	Q_D(CustomScrollBar);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CustomScrollBar::useThemeColors() const
{
	Q_D(const CustomScrollBar);

	return d->useThemeColors;
}

void CustomScrollBar::setCanvasColor(const QColor &color)
{
	Q_D(CustomScrollBar);

	d->canvasColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomScrollBar::canvasColor() const
{
	Q_D(const CustomScrollBar);

	if (d->useThemeColors || !d->canvasColor.isValid()) {
		return parentWidget()->palette().color(backgroundRole());
	}
	else {
		return d->canvasColor;
	}
}

void CustomScrollBar::setBackgroundColor(const QColor &color)
{
	Q_D(CustomScrollBar);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomScrollBar::backgroundColor() const
{
	Q_D(const CustomScrollBar);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CustomStyle::instance().themeColor("border");
	}
	else {
		return d->backgroundColor;
	}
}

void CustomScrollBar::setSliderColor(const QColor &color)
{
	Q_D(CustomScrollBar);

	d->sliderColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomScrollBar::sliderColor() const
{
	Q_D(const CustomScrollBar);

	if (d->useThemeColors || !d->sliderColor.isValid()) {
		return CustomStyle::instance().themeColor("primary1");
	}
	else {
		return d->sliderColor;
	}
}

void CustomScrollBar::setHideOnMouseOut(bool value)
{
	Q_D(CustomScrollBar);

	d->hideOnMouseOut = value;
	update();
}

bool CustomScrollBar::hideOnMouseOut() const
{
	Q_D(const CustomScrollBar);

	return d->hideOnMouseOut;
}

/*!
*  \reimp
*/
void CustomScrollBar::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomScrollBar);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.fillRect(rect(), canvasColor());

	int x, y, w, h;
	rect().getRect(&x, &y, &w, &h);

	QMargins margins(2, 2, 2, 2);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(backgroundColor());
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);

	if (d->hideOnMouseOut) {
		painter.setOpacity(d->stateMachine->opacity());
	}

	QRect trimmed(rect().marginsRemoved(margins));

	QPainterPath path;
	path.addRoundedRect(trimmed, 3, 3);
	painter.setClipPath(path);

	painter.drawRect(trimmed);

	const qreal q = (Qt::Horizontal == orientation() ? w : h) /
		static_cast<qreal>(maximum() - minimum() + pageStep() - 1);

	QRect handle = Qt::Horizontal == orientation()
		? QRect(sliderPosition()*q, y, pageStep()*q, h)
		: QRect(x, sliderPosition()*q, w, pageStep()*q);

	brush.setColor(sliderColor());
	painter.setBrush(brush);

	painter.drawRoundedRect(handle, 9, 9);
}

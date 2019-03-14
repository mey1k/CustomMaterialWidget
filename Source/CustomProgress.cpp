#include "stdafx.h"
#include "Customprogress.h"
#include "Customprogress_p.h"
#include <QPropertyAnimation>
#include <QPainter>
#include "Customprogress_internal.h"
#include "Customstyle.h"

/*!
*  \class CustomProgressPrivate
*  \internal
*/

CustomProgressPrivate::CustomProgressPrivate(CustomProgress *q)
	: q_ptr(q)
{
}

CustomProgressPrivate::~CustomProgressPrivate()
{
}

void CustomProgressPrivate::init()
{
	Q_Q(CustomProgress);

	delegate = new CustomProgressDelegate(q);
	progressType = Material::DeterminateProgress;
	useThemeColors = false;

	QPropertyAnimation *animation;

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("offset");
	animation->setTargetObject(delegate);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->setDuration(1000);

	animation->setLoopCount(-1);

	animation->start();
}

/*!
*  \class CustomProgress
*/

CustomProgress::CustomProgress(QWidget *parent)
	: QProgressBar(parent),
	d_ptr(new CustomProgressPrivate(this))
{
	d_func()->init();
}

CustomProgress::~CustomProgress()
{
}

void CustomProgress::setProgressType(Material::ProgressType type)
{
	Q_D(CustomProgress);

	d->progressType = type;
	update();
}

Material::ProgressType CustomProgress::progressType() const
{
	Q_D(const CustomProgress);

	return d->progressType;
}

void CustomProgress::setUseThemeColors(bool state)
{
	Q_D(CustomProgress);

	if (d->useThemeColors == state) {
		return;
	}

	d->useThemeColors = state;
	update();
}

bool CustomProgress::useThemeColors() const
{
	Q_D(const CustomProgress);

	return d->useThemeColors;
}

void CustomProgress::setProgressColor(const QColor &color)
{
	Q_D(CustomProgress);

	d->progressColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomProgress::progressColor() const
{
	Q_D(const CustomProgress);

	if (d->useThemeColors || !d->progressColor.isValid()) {
		return CustomStyle::instance().themeColor("primary1");
	}
	else {
		return d->progressColor;
	}
}

void CustomProgress::setBackgroundColor(const QColor &color)
{
	Q_D(CustomProgress);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomProgress::backgroundColor() const
{
	Q_D(const CustomProgress);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CustomStyle::instance().themeColor("border");
	}
	else {
		return d->backgroundColor;
	}
}

/*!
*  \reimp
*/
void CustomProgress::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomProgress);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(isEnabled() ? backgroundColor()
		: CustomStyle::instance().themeColor("disabled"));
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);

	QPainterPath path;
	path.addRoundedRect(0, height() / 2 - 3, width(), 6, 3, 3);
	painter.setClipPath(path);

	painter.drawRect(0, 0, width(), height());

	if (isEnabled())
	{
		brush.setColor(progressColor());
		painter.setBrush(brush);

		if (Material::IndeterminateProgress == d->progressType) {
			painter.drawRect(d->delegate->offset()*width() * 2 - width(), 0, width(), height());
		}
		else {
			qreal p = static_cast<qreal>(width())*(value() - minimum()) / (maximum() - minimum());
			painter.drawRect(0, 0, p, height());
		}
	}
}

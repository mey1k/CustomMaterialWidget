#include "Customcircularprogress.h"
#include "Customcircularprogress_p.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
#include "Customcircularprogress_internal.h"
#include "Customstyle.h"

/*!
*  \class CustomCircularProgressPrivate
*  \internal
*/

CustomCircularProgressPrivate::CustomCircularProgressPrivate(CustomCircularProgress *q)
	: q_ptr(q)
{
}

CustomCircularProgressPrivate::~CustomCircularProgressPrivate()
{
}

void CustomCircularProgressPrivate::init()
{
	Q_Q(CustomCircularProgress);

	delegate = new CustomCircularProgressDelegate(q);
	progressType = Material::IndeterminateProgress;
	penWidth = 6.25;
	size = 64;
	useThemeColors = true;

	q->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
		QSizePolicy::MinimumExpanding));

	QParallelAnimationGroup *group = new QParallelAnimationGroup(q);
	group->setLoopCount(-1);

	QPropertyAnimation *animation;

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("dashLength");
	animation->setTargetObject(delegate);
	animation->setEasingCurve(QEasingCurve::InOutQuad);
	animation->setStartValue(0.1);
	animation->setKeyValueAt(0.15, 0.2);
	animation->setKeyValueAt(0.6, 20);
	animation->setKeyValueAt(0.7, 20);
	animation->setEndValue(20);
	animation->setDuration(2050);

	group->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("dashOffset");
	animation->setTargetObject(delegate);
	animation->setEasingCurve(QEasingCurve::InOutSine);
	animation->setStartValue(0);
	animation->setKeyValueAt(0.15, 0);
	animation->setKeyValueAt(0.6, -7);
	animation->setKeyValueAt(0.7, -7);
	animation->setEndValue(-25);
	animation->setDuration(2050);

	group->addAnimation(animation);

	animation = new QPropertyAnimation(q);
	animation->setPropertyName("angle");
	animation->setTargetObject(delegate);
	animation->setStartValue(0);
	animation->setEndValue(719);
	animation->setDuration(2050);

	group->addAnimation(animation);

	group->start();
}

/*!
*  \class CustomCircularProgress
*/

CustomCircularProgress::CustomCircularProgress(QWidget *parent)
	: QProgressBar(parent),
	d_ptr(new CustomCircularProgressPrivate(this))
{
	d_func()->init();
}

CustomCircularProgress::~CustomCircularProgress()
{
}

void CustomCircularProgress::setProgressType(Material::ProgressType type)
{
	Q_D(CustomCircularProgress);

	d->progressType = type;
	update();
}

Material::ProgressType CustomCircularProgress::progressType() const
{
	Q_D(const CustomCircularProgress);

	return d->progressType;
}

void CustomCircularProgress::setUseThemeColors(bool value)
{
	Q_D(CustomCircularProgress);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CustomCircularProgress::useThemeColors() const
{
	Q_D(const CustomCircularProgress);

	return d->useThemeColors;
}

void CustomCircularProgress::setLineWidth(qreal width)
{
	Q_D(CustomCircularProgress);

	d->penWidth = width;
	update();
	updateGeometry();
}

qreal CustomCircularProgress::lineWidth() const
{
	Q_D(const CustomCircularProgress);

	return d->penWidth;
}

void CustomCircularProgress::setSize(int size)
{
	Q_D(CustomCircularProgress);

	d->size = size;
	update();
	updateGeometry();
}

int CustomCircularProgress::size() const
{
	Q_D(const CustomCircularProgress);

	return d->size;
}

void CustomCircularProgress::setColor(const QColor &color)
{
	Q_D(CustomCircularProgress);

	d->color = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomCircularProgress::color() const
{
	Q_D(const CustomCircularProgress);

	if (d->useThemeColors || !d->color.isValid()) {
		return CustomStyle::instance().themeColor("primary1");
	}
	else {
		return d->color;
	}
}

/*!
*  \reimp
*/
QSize CustomCircularProgress::sizeHint() const
{
	Q_D(const CustomCircularProgress);

	const qreal s = d->size + d->penWidth + 8;
	return QSize(s, s);
}

/*!
*  \reimp
*/
void CustomCircularProgress::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomCircularProgress);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if (!isEnabled())
	{
		QPen pen;
		pen.setCapStyle(Qt::RoundCap);
		pen.setWidthF(d->penWidth);
		pen.setColor(CustomStyle::instance().themeColor("border"));
		painter.setPen(pen);
		painter.drawLine(rect().center() - QPointF(20, 20), rect().center() + QPointF(20, 20));
		painter.drawLine(rect().center() + QPointF(20, -20), rect().center() - QPointF(20, -20));
		return;
	}

	if (Material::IndeterminateProgress == d->progressType)
	{
		painter.translate(width() / 2, height() / 2);
		painter.rotate(d->delegate->angle());
	}

	QPen pen;
	pen.setCapStyle(Qt::RoundCap);
	pen.setWidthF(d->penWidth);
	pen.setColor(color());

	if (Material::IndeterminateProgress == d->progressType)
	{
		QVector<qreal> pattern;
		pattern << d->delegate->dashLength()*d->size / 50 << 30 * d->size / 50;

		pen.setDashOffset(d->delegate->dashOffset()*d->size / 50);
		pen.setDashPattern(pattern);

		painter.setPen(pen);

		painter.drawEllipse(QPoint(0, 0), d->size / 2, d->size / 2);
	}
	else
	{
		painter.setPen(pen);

		const qreal x = (width() - d->size) / 2;
		const qreal y = (height() - d->size) / 2;

		const qreal a = 360 * (value() - minimum()) / (maximum() - minimum());

		QPainterPath path;
		path.arcMoveTo(x, y, d->size, d->size, 0);
		path.arcTo(x, y, d->size, d->size, 0, a);

		painter.drawPath(path);
	}
}

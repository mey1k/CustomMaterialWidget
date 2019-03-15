#include "Custombadge.h"
#include "Custombadge_p.h"
#include <QPainter>
#include "Customstyle.h"
#include "SurgicalGuide.h"

/*!
*  \class CustomBadgePrivate
*  \internal
*/

/*!
*  \internal
*/
CustomBadgePrivate::CustomBadgePrivate(CustomBadge *q)
	: q_ptr(q)
{
}

/*!
*  \internal
*/
CustomBadgePrivate::~CustomBadgePrivate()
{
}

/*!
*  \internal
*/
void CustomBadgePrivate::init()
{
	Q_Q(CustomBadge);

	x = 0;
	y = 0;
	padding = 10;
	useThemeColors = true;

	q->setAttribute(Qt::WA_TransparentForMouseEvents);

	QFont font(q->font());
	font.setPointSizeF(10);
	font.setStyleName("Bold");
	q->setFont(font);
	q->setText("+1");
	q->setBackgroundColor(QColor(159, 34, 65));
}

/*!
*  \class CustomBadge
*/

CustomBadge::CustomBadge(QWidget *parent)
	: CustomOverlayWidget(parent),
	d_ptr(new CustomBadgePrivate(this))
{
	d_func()->init();
}

CustomBadge::CustomBadge(const QIcon &icon, QWidget *parent)
	: CustomOverlayWidget(parent),
	d_ptr(new CustomBadgePrivate(this))
{
	d_func()->init();

	setIcon(icon);
}

CustomBadge::CustomBadge(const QString &text, QWidget *parent)
	: CustomOverlayWidget(parent),
	d_ptr(new CustomBadgePrivate(this))
{
	d_func()->init();

	setText(text);
}

CustomBadge::~CustomBadge()
{
}

void CustomBadge::setUseThemeColors(bool value)
{
	Q_D(CustomBadge);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CustomBadge::useThemeColors() const
{
	Q_D(const CustomBadge);

	return d->useThemeColors;
}

void CustomBadge::setTextColor(const QColor &color)
{
	Q_D(CustomBadge);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomBadge::textColor() const
{
	Q_D(const CustomBadge);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CustomStyle::instance().themeColor("canvas");
	}
	else {
		return d->textColor;
	}
}

void CustomBadge::setBackgroundColor(const QColor &color)
{
	Q_D(CustomBadge);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomBadge::backgroundColor() const
{
	Q_D(const CustomBadge);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CustomStyle::instance().themeColor("accent1");
	}
	else {
		return d->backgroundColor;
	}
}

void CustomBadge::setRelativePosition(const QPointF &pos)
{
	setRelativePosition(pos.x(), pos.y());
}

void CustomBadge::setRelativePosition(qreal x, qreal y)
{
	Q_D(CustomBadge);

	d->x = x;
	d->y = y;
	update();
}

QPointF CustomBadge::relativePosition() const
{
	Q_D(const CustomBadge);

	return QPointF(d->x, d->y);
}

void CustomBadge::setRelativeXPosition(qreal x)
{
	Q_D(CustomBadge);

	d->x = x;
	update();
}

qreal CustomBadge::relativeXPosition() const
{
	Q_D(const CustomBadge);

	return d->x;
}

void CustomBadge::setRelativeYPosition(qreal y)
{
	Q_D(CustomBadge);

	d->y = y;
	update();
}

qreal CustomBadge::relativeYPosition() const
{
	Q_D(const CustomBadge);

	return d->y;
}

/*!
*  \reimp
*/
QSize CustomBadge::sizeHint() const
{
	const int s = getDiameter();
	return QSize(s + 4, s + 4);
}

void CustomBadge::setIcon(const QIcon &icon)
{
	Q_D(CustomBadge);

	d->icon = icon;

	update();
}

QIcon CustomBadge::icon() const
{
	Q_D(const CustomBadge);

	return d->icon;
}

void CustomBadge::setText(const QString &text)
{
	Q_D(CustomBadge);

	d->text = text;

	if (!d->icon.isNull()) {
		d->icon = QIcon();
	}

	d->size = fontMetrics().size(Qt::TextShowMnemonic, text);

	update();
}

QString CustomBadge::text() const
{
	Q_D(const CustomBadge);

	return d->text;
}

/*!
*  \reimp
*/
void CustomBadge::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomBadge);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	painter.translate(d->x, d->y);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);

	if (mainParent != nullptr)
	{
		if (mainParent->themeType == Theme::whiteRed)
			brush.setColor(isEnabled() ? QColor(159, 34, 65) : CustomStyle::instance().themeColor("disabled"));

		else
			brush.setColor(isEnabled() ? QColor(42, 125, 225) : CustomStyle::instance().themeColor("disabled"));
	}
	else
		brush.setColor(isEnabled() ? QColor(159, 34, 65) : CustomStyle::instance().themeColor("disabled"));
	
	/*brush.setColor(isEnabled() ? backgroundColor()
		: CustomStyle::instance().themeColor("disabled"));*/

	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);

	const int s = getDiameter();

	QRectF r(0, 0, s, s);
	r.translate(QPointF((width() - s), (height() - s)) / 2);


	if (d->icon.isNull())
	{
		painter.drawEllipse(r);
		painter.setPen(textColor());
		painter.setBrush(Qt::NoBrush);
		painter.drawText(r.translated(0, -0.5), Qt::AlignCenter, d->text);
	}
	else
	{
		painter.drawEllipse(r);
		QRectF q(0, 0, iconSize/2, iconSize/2);
		q.moveCenter(r.center());
		QPixmap pixmap = icon().pixmap(iconSize/2, iconSize/2);
		QPainter icon(&pixmap);
		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
		icon.fillRect(pixmap.rect(), textColor());
		painter.drawPixmap(q.toRect(), pixmap);
	}
}

int CustomBadge::getDiameter() const
{
	Q_D(const CustomBadge);

	if (d->icon.isNull()) {
		return qMax(d->size.width(), d->size.height()) + d->padding;
	}
	else {
		return iconSize;
	}
}

void CustomBadge::setSIze(int size)
{
	Q_D(CustomBadge);

	d->size.setWidth(size);
	d->size.setHeight(size);
	iconSize = size;
}

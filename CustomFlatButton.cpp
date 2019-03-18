#include "Customflatbutton.h"
#include "Customflatbutton_p.h"
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QBitmap>
#include <QPainterPath>
#include <QIcon>
#include "Customrippleoverlay.h"
#include "Customripple.h"
#include "Customstyle.h"
#include "Customflatbutton_internal.h"
#include <qdebug.h>

/*!
*  \class CustomFlatButtonPrivate
*  \internal
*/

/*!
*  \internal
*/
CustomFlatButtonPrivate::CustomFlatButtonPrivate(CustomFlatButton *q)
	: q_ptr(q)
{

}

/*!
*  \internal
*/
CustomFlatButtonPrivate::~CustomFlatButtonPrivate()
{
}

/*!
*  \internal
*/
void CustomFlatButtonPrivate::init()
{
	Q_Q(CustomFlatButton);

	rippleOverlay = new CustomRippleOverlay(q);
	stateMachine = new CustomFlatButtonStateMachine(q);
	role = Material::Default;
	rippleStyle = Material::PositionedRipple;
	iconPlacement = Material::RightIcon;
	overlayStyle = Material::GrayOverlay;
	bgMode = Qt::OpaqueMode;
	textAlignment = Qt::AlignLeft;
	fixedRippleRadius = 64;
	cornerRadius = 5;
	baseOpacity = 0.13;
	fontSize = 10;        // 10.5;
	useThemeColors = false;
	useFixedRippleRadius = false;
	haloVisible = false;
	backgroundColor = QColor(255,255,255,177);
	

	q->setStyle(&CustomStyle::instance());
	q->setAttribute(Qt::WA_Hover);
	q->setMouseTracking(true);

	QFont font("Roboto", 10, QFont::Light);
	//font.setCapitalization(QFont::AllUppercase);
	q->setFont(font);

	QPainterPath path;
	path.addRoundedRect(q->rect(), cornerRadius, cornerRadius);
	rippleOverlay->setClipPath(path);
	rippleOverlay->setClipping(true);

	stateMachine->setupProperties();
	stateMachine->startAnimations();


	//Custom
	//q->setVisibleHalo(false);
	//q->setBackgroundMode(Qt::OpaqueMode);
	//q->setBackgroundColor(Qt::white);
}

/*!
*  \class CustomFlatButton
*/

CustomFlatButton::CustomFlatButton(QWidget *parent, Material::ButtonPreset preset)
	: QPushButton(parent),
	d_ptr(new CustomFlatButtonPrivate(this))
{
	d_func()->init();

	applyPreset(preset);
}

CustomFlatButton::CustomFlatButton(const QString &text, QWidget *parent, Material::ButtonPreset preset)
	: QPushButton(text, parent),
	d_ptr(new CustomFlatButtonPrivate(this))
{
	d_func()->init();

	applyPreset(preset);
}

CustomFlatButton::CustomFlatButton(const QString &text, Material::Role role, QWidget *parent, Material::ButtonPreset preset)
	: QPushButton(text, parent),
	d_ptr(new CustomFlatButtonPrivate(this))
{
	d_func()->init();

	applyPreset(preset);
	setRole(role);
}

CustomFlatButton::~CustomFlatButton()
{
}

void CustomFlatButton::applyPreset(Material::ButtonPreset preset)
{
	switch (preset)
	{
	case Material::FlatPreset:
		setOverlayStyle(Material::NoOverlay);
		break;
	case Material::CheckablePreset:
		setOverlayStyle(Material::NoOverlay);
		setCheckable(true);
		setHaloVisible(false);
		break;
	default:
		break;
	}
}

void CustomFlatButton::setUseThemeColors(bool value)
{
	Q_D(CustomFlatButton);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	d->stateMachine->setupProperties();
}

bool CustomFlatButton::useThemeColors() const
{
	Q_D(const CustomFlatButton);

	return d->useThemeColors;
}

void CustomFlatButton::setRole(Material::Role role)
{
	Q_D(CustomFlatButton);

	d->role = role;
	d->stateMachine->setupProperties();
}

Material::Role CustomFlatButton::role() const
{
	Q_D(const CustomFlatButton);

	return d->role;
}

void CustomFlatButton::setForegroundColor(const QColor &color)
{
	Q_D(CustomFlatButton);

	d->foregroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomFlatButton::foregroundColor() const
{
	Q_D(const CustomFlatButton);

	if (d->useThemeColors || !d->foregroundColor.isValid())
	{
		if (Qt::OpaqueMode == d->bgMode) {
			return CustomStyle::instance().themeColor("canvas");
		}
		switch (d->role)
		{
		case Material::Primary:
			return CustomStyle::instance().themeColor("primary1");
		case Material::Secondary:
			return CustomStyle::instance().themeColor("accent1");
		case Material::Default:
		default:
			return CustomStyle::instance().themeColor("text");
		}
	}
	return d->foregroundColor;
}

void CustomFlatButton::setBackgroundColor(const QColor &color)
{
	Q_D(CustomFlatButton);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

void CustomFlatButton::UpdateFlatButton()
{
	Q_D(CustomFlatButton);

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomFlatButton::backgroundColor() const
{
	Q_D(const CustomFlatButton);

	if (d->useThemeColors || !d->backgroundColor.isValid())
	{
		switch (d->role)
		{
		case Material::Primary:
			return CustomStyle::instance().themeColor("primary1");
		case Material::Secondary:
			return CustomStyle::instance().themeColor("accent1");
		case Material::Default:
		default:
			return CustomStyle::instance().themeColor("text");
		}
	}
	return d->backgroundColor;
}

void CustomFlatButton::setOverlayColor(const QColor &color)
{
	Q_D(CustomFlatButton);

	d->overlayColor = color;

	MATERIAL_DISABLE_THEME_COLORS

		setOverlayStyle(Material::TintedOverlay);
	update();
}

QColor CustomFlatButton::overlayColor() const
{
	Q_D(const CustomFlatButton);

	if (d->useThemeColors || !d->overlayColor.isValid()) {
		return foregroundColor();
	}
	return d->overlayColor;
}

void CustomFlatButton::setDisabledForegroundColor(const QColor &color)
{
	Q_D(CustomFlatButton);

	d->disabledColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomFlatButton::disabledForegroundColor() const
{
	Q_D(const CustomFlatButton);

	if (d->useThemeColors || !d->disabledColor.isValid()) {
		return CustomStyle::instance().themeColor("disabled");
	}
	else {
		return d->disabledColor;
	}
}

void CustomFlatButton::setDisabledBackgroundColor(const QColor &color)
{
	Q_D(CustomFlatButton);

	d->disabledBackgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomFlatButton::disabledBackgroundColor() const
{
	Q_D(const CustomFlatButton);

	if (d->useThemeColors || !d->disabledBackgroundColor.isValid()) {
		return CustomStyle::instance().themeColor("disabled3");
	}
	else {
		return d->disabledBackgroundColor;
	}
}

void CustomFlatButton::setFontSize(qreal size)
{
	Q_D(CustomFlatButton);

	d->fontSize = size;

	QFont f(font());
	f.setPointSizeF(size);
	setFont(f);

	update();
}

qreal CustomFlatButton::fontSize() const
{
	Q_D(const CustomFlatButton);

	return d->fontSize;
}

void CustomFlatButton::setHaloVisible(bool visible)
{
	Q_D(CustomFlatButton);

	d->haloVisible = visible;
	update();
}

bool CustomFlatButton::isHaloVisible() const
{
	Q_D(const CustomFlatButton);

	return d->haloVisible;
}

void CustomFlatButton::setOverlayStyle(Material::OverlayStyle style)
{
	Q_D(CustomFlatButton);

	d->overlayStyle = style;
	update();
}

Material::OverlayStyle CustomFlatButton::overlayStyle() const
{
	Q_D(const CustomFlatButton);

	return d->overlayStyle;
}

void CustomFlatButton::setRippleStyle(Material::RippleStyle style)
{
	Q_D(CustomFlatButton);

	d->rippleStyle = style;
}

Material::RippleStyle CustomFlatButton::rippleStyle() const
{
	Q_D(const CustomFlatButton);

	return d->rippleStyle;
}

void CustomFlatButton::setIconPlacement(Material::ButtonIconPlacement placement)
{
	Q_D(CustomFlatButton);

	d->iconPlacement = placement;
	update();
}

Material::ButtonIconPlacement CustomFlatButton::iconPlacement() const
{
	Q_D(const CustomFlatButton);

	return d->iconPlacement;
}

void CustomFlatButton::setCornerRadius(qreal radius)
{
	Q_D(CustomFlatButton);

	d->cornerRadius = radius;
	updateClipPath();
	update();
}

qreal CustomFlatButton::cornerRadius() const
{
	Q_D(const CustomFlatButton);

	return d->cornerRadius;
}

void CustomFlatButton::setBackgroundMode(Qt::BGMode mode)
{
	Q_D(CustomFlatButton);

	d->bgMode = mode;
	d->stateMachine->setupProperties();
}

Qt::BGMode CustomFlatButton::backgroundMode() const
{
	Q_D(const CustomFlatButton);

	return d->bgMode;
}

void CustomFlatButton::setBaseOpacity(qreal opacity)
{
	Q_D(CustomFlatButton);

	d->baseOpacity = opacity;
	d->stateMachine->setupProperties();
}

qreal CustomFlatButton::baseOpacity() const
{
	Q_D(const CustomFlatButton);

	return d->baseOpacity;
}

void CustomFlatButton::setCheckable(bool value)
{
	Q_D(CustomFlatButton);

	d->stateMachine->updateCheckedStatus();

	QPushButton::setCheckable(value);
}

void CustomFlatButton::setHasFixedRippleRadius(bool value)
{
	Q_D(CustomFlatButton);

	d->useFixedRippleRadius = value;
}

bool CustomFlatButton::hasFixedRippleRadius() const
{
	Q_D(const CustomFlatButton);

	return d->useFixedRippleRadius;
}

void CustomFlatButton::setFixedRippleRadius(qreal radius)
{
	Q_D(CustomFlatButton);

	d->fixedRippleRadius = radius;
	setHasFixedRippleRadius(true);
}

void CustomFlatButton::setTextAlignment(Qt::Alignment alignment)
{
	Q_D(CustomFlatButton);

	d->textAlignment = alignment;
}

Qt::Alignment CustomFlatButton::textAlignment() const
{
	Q_D(const CustomFlatButton);

	return d->textAlignment;
}

/*!
*  \reimp
*/
QSize CustomFlatButton::sizeHint() const
{
	ensurePolished();

	QSize label(fontMetrics().size(Qt::TextSingleLine, text()));

	int w = 20 + label.width();
	int h = label.height();
	if (!icon().isNull()) {
		w += iconSize().width() + CustomFlatButton::IconPadding;
		h = qMax(h, iconSize().height());
	}
	return QSize(w, 20 + h);
}

CustomFlatButton::CustomFlatButton(CustomFlatButtonPrivate &d, QWidget *parent, Material::ButtonPreset preset)
	: QPushButton(parent),
	d_ptr(&d)
{
	d_func()->init();

	applyPreset(preset);
}

/*!
*  \reimp
*/
void CustomFlatButton::checkStateSet()
{
	Q_D(CustomFlatButton);

	d->stateMachine->updateCheckedStatus();

	QPushButton::checkStateSet();
}

/*!
*  \reimp
*/
void CustomFlatButton::mousePressEvent(QMouseEvent *event)
{
	Q_D(CustomFlatButton);

	if (Material::NoRipple != d->rippleStyle)
	{
		QPoint pos;
		qreal radiusEndValue;

		if (Material::CenteredRipple == d->rippleStyle) {
			pos = rect().center();
		}
		else {
			pos = event->pos();
		}

		if (d->useFixedRippleRadius) {
			radiusEndValue = d->fixedRippleRadius;
		}
		else {
			radiusEndValue = static_cast<qreal>(width()) / 2;
		}

		CustomRipple *ripple = new CustomRipple(pos);

		ripple->setRadiusEndValue(radiusEndValue);
		ripple->setOpacityStartValue(0.35);
		//ripple->setColor(foregroundColor());
		ripple->setColor(Qt::white);
		ripple->radiusAnimation()->setDuration(600);
		ripple->opacityAnimation()->setDuration(1300);

		d->rippleOverlay->addRipple(ripple);
	}

	QPushButton::mousePressEvent(event);
}

/*!
*  \reimp
*/
void CustomFlatButton::mouseReleaseEvent(QMouseEvent *event)
{
	Q_D(CustomFlatButton);

	QPushButton::mouseReleaseEvent(event);

	d->stateMachine->updateCheckedStatus();
}

void CustomFlatButton::resizeEvent(QResizeEvent *event)
{
	QPushButton::resizeEvent(event);

	updateClipPath();
}

/*!
*  \reimp
*/
void CustomFlatButton::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomFlatButton);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	const qreal cr = d->cornerRadius;

	if (cr > 0)
	{
		QPainterPath path;
		path.addRoundedRect(rect(), cr, cr);

		painter.setClipPath(path);
		painter.setClipping(true);
	}

	paintBackground(&painter);
	d->stateMachine->setHaloOpacity(0.13);
	d->stateMachine->setHaloSize(0.7);

	painter.setOpacity(1);
	painter.setClipping(false);

	paintForeground(&painter);
	paintHalo(&painter);
}

/*!
*  \halo
*/
void CustomFlatButton::setVisibleHalo(bool value)
{
	if (value)
	{
		Q_D(CustomFlatButton);

		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		const qreal cr = d->cornerRadius;

		if (cr > 0)
		{
			QPainterPath path;
			path.addRoundedRect(rect(), cr, cr);

			painter.setClipPath(path);
			painter.setClipping(true);
		}

		d->stateMachine->setHaloOpacity(0.13);

		paintHalo(&painter);

		painter.setOpacity(1);
		painter.setClipping(false);

		paintForeground(&painter);
	}
}

/*!
*  \internal
*/
void CustomFlatButton::paintBackground(QPainter *painter)
{
	Q_D(CustomFlatButton);

	const qreal overlayOpacity = d->stateMachine->overlayOpacity();
	const qreal checkedProgress = d->stateMachine->checkedOverlayProgress();

	if (Qt::OpaqueMode == d->bgMode) {
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);

		if (isEnabled()) {
			QColor color;

			if (theme != nullptr)
			{
				if (theme->themeType == ThemeType::whiteRed)
					color = QColor(255, 255, 255);
				else
					color = QColor(10, 34, 64);
			}
			else
				color = QColor(255, 255, 255);

			brush.setColor(color);
		}
		else {
			QColor color;

			if (theme != nullptr)
			{
				if (theme->themeType == ThemeType::whiteRed)
					color = QColor(217, 216, 214);
				else
					color = QColor(10, 34, 64, 255);
			}
			else
				color = QColor(217, 216, 214);

			brush.setColor(color);
		}

		painter->setOpacity(0.8);
		painter->setBrush(brush);

		//custom flatbutton
		if (d->q_ptr->isFocus)
		{
			QColor color;
			if (theme != nullptr)
			{
				if (theme->themeType == ThemeType::whiteRed)
					color = QColor(159, 34, 65);
				else
					color = QColor(42, 125, 225);
			}
			else
				color = QColor(159, 34, 65);

			brush.setColor(color);
			painter->setOpacity(1);
			painter->setBrush(brush);

			QPen pen(color, 3);
			painter->setPen(pen);
			d->q_ptr->setForegroundColor(Qt::white);
		}
		else
		{
			QColor color;
			if (theme != nullptr)
			{
				if (theme->themeType == ThemeType::whiteRed)
					color = QColor(137, 138, 141);
				else
					color = QColor(132, 144, 159);
			}
			else
				color = QColor(137, 138, 141);

			painter->setPen(Qt::NoPen);
			d->q_ptr->setForegroundColor(color);
		}

		painter->drawRect(rect());
	}

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	painter->setPen(Qt::NoPen);

	if (!isEnabled()) {
		return;
	}

	if ((Material::NoOverlay != d->overlayStyle) && (overlayOpacity > 0)) {
		if (Material::TintedOverlay == d->overlayStyle) {
			brush.setColor(overlayColor());
		}
		else {
			brush.setColor(Qt::GlobalColor::blue);
		}
		painter->setOpacity(overlayOpacity);
		painter->setBrush(brush);
		painter->drawRect(rect());
	}

	if (isCheckable() && checkedProgress > 0) {
		const qreal q = Qt::TransparentMode == d->bgMode ? 0.45 : 0.7;
		brush.setColor(foregroundColor());
		painter->setOpacity(q*checkedProgress);
		painter->setBrush(brush);
		QRect r(rect());
		r.setHeight(static_cast<qreal>(r.height())*checkedProgress);
		painter->drawRect(r);
	}
}

/*!
*  \internal
*/
void CustomFlatButton::paintHalo(QPainter *painter)
{
	Q_D(CustomFlatButton);

	if (!d->haloVisible) {
		return;
	}

	const qreal opacity = d->stateMachine->haloOpacity();
	const qreal s = d->stateMachine->haloScaleFactor()*d->stateMachine->haloSize();
	const qreal radius = static_cast<qreal>(width())*s;

	if (isEnabled() && opacity > 0) {
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(foregroundColor());
		painter->setOpacity(opacity);
		painter->setBrush(brush);
		painter->setPen(Qt::NoPen);
		const QPointF center = rect().center();
		painter->drawEllipse(center, radius, radius);
	}
}

#define COLOR_INTERPOLATE(CH) (1-progress)*source.CH() + progress*dest.CH()

/*!
*  \internal
*/
void CustomFlatButton::paintForeground(QPainter *painter)
{
	Q_D(CustomFlatButton);

	if (isEnabled()) {
		painter->setPen(foregroundColor());
		const qreal progress = d->stateMachine->checkedOverlayProgress();
		if (isCheckable() && progress > 0) {
			QColor source = foregroundColor();
			QColor dest = Qt::TransparentMode == d->bgMode ? Qt::white
				: backgroundColor();
			if (qFuzzyCompare(1, progress)) {
				painter->setPen(dest);
			}
			else {
				painter->setPen(QColor(COLOR_INTERPOLATE(red),
					COLOR_INTERPOLATE(green),
					COLOR_INTERPOLATE(blue),
					COLOR_INTERPOLATE(alpha)));
			}
		}
	}
	else {
		painter->setPen(disabledForegroundColor());
	}

	if (icon().isNull()) {
		if (Qt::AlignLeft == d->textAlignment) {
			painter->drawText(rect().adjusted(12, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text());
		}
		else {
			painter->drawText(rect(), Qt::AlignCenter, text());
		}
		return;
	}

	QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));

	QSize base(size() - textSize);

	const int iw = iconSize().width() + IconPadding;
	QPoint pos(Qt::AlignLeft == d->textAlignment ? 12 : (base.width() - iw) / 2, 0);

	QRect textGeometry(pos + QPoint(0, base.height() / 2), textSize);
	QRect iconGeometry(pos + QPoint(0, (height() - iconSize().height()) / 2), iconSize());

	if (Material::LeftIcon == d->iconPlacement) {
		textGeometry.translate(iw, 0);
	}
	else if (Material::CenterIcon == d->iconPlacement)
	{
		QPoint centerPos((width() / 2 - iconSize().width() / 2), (height()/2 - iconSize().width() / 2));
		iconGeometry.setRect(centerPos.rx(), centerPos.ry(), iconSize().width(), iconSize().height());
	}
	else if (Material::RightIcon == d->iconPlacement)
	{
		//iconGeometry.translate(textSize.width() + IconPadding, 0);
		QPoint rightPos(width()-20 * correctScaleW - (iconSize().width() / 2) - IconPadding, (height() / 2 - iconSize().width() / 2));
		iconGeometry.setRect(rightPos.rx(), rightPos.ry(), iconSize().width(), iconSize().height());
	}

	painter->drawText(textGeometry, Qt::AlignCenter, text());

	QPixmap pixmap = icon().pixmap(iconSize());
	QPainter icon(&pixmap);
	icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
	icon.fillRect(pixmap.rect(), painter->pen().color());
	//Original color
	//icon.fillRect(pixmap.rect(), painter->pen().color());
	painter->drawPixmap(iconGeometry, pixmap);

	if (useTwoIcons && (!secondIcon.isNull()))
	{
		
		QPainter icon(&secondIcon);

		QPoint rightPos(width() - 20 * correctScaleW  - (secondIcon.width() / 2) - IconPadding, (height() / 2 - secondIcon.width() / 2));
		iconGeometry.setRect(rightPos.rx(), rightPos.ry(), secondIcon.width(), secondIcon.height());

		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
		if(!usePng)
			icon.fillRect(secondIcon.rect(), painter->pen().color());
		painter->drawPixmap(iconGeometry, secondIcon);
	}
}

/*!
*  \internal
*/
void CustomFlatButton::updateClipPath()
{
	Q_D(CustomFlatButton);

	const qreal radius = d->cornerRadius;

	QPainterPath path;
	path.addRoundedRect(rect(), radius, radius);
	d->rippleOverlay->setClipPath(path);
}


void CustomFlatButton::setFocusOutColor(QColor color)
{
	focusOutColor = color;
}

void CustomFlatButton::setTwoIcons(bool flag, QPixmap second, int width, int height, bool png)
{
	QSize myRessortSize(width, height);

	if (flag)
		useTwoIcons = flag;

	usePng = png;

	secondIcon = second.scaled(myRessortSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

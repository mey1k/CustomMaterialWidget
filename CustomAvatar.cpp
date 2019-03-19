#include "Customavatar.h"
#include "Customavatar_p.h"
#include <QPainter>
#include "Customstyle.h"
#include <qevent.h>

/*!
*  \class CustomAvatarPrivate
*  \internal
*/

/*!
*  \internal
*/
CustomAvatarPrivate::CustomAvatarPrivate(CustomAvatar *q)
	: q_ptr(q)
{
}

/*!
*  \internal
*/
CustomAvatarPrivate::~CustomAvatarPrivate()
{
}

/*!
*  \internal
*/
void CustomAvatarPrivate::init()
{
	Q_Q(CustomAvatar);

	size = 40;
	type = Material::LetterAvatar;
	useThemeColors = true;

	QFont font(q->font());
	font.setPointSizeF(16);
	q->setFont(font);

	QSizePolicy policy(QSizePolicy::MinimumExpanding,
		QSizePolicy::MinimumExpanding);
	q->setSizePolicy(policy);
	q->setMouseTracking(true);
	q->setBackgroundColor(Qt::white);
}

/*!
*  \class CustomAvatar
*/

CustomAvatar::CustomAvatar(QWidget *parent)
	: QWidget(parent),
	d_ptr(new CustomAvatarPrivate(this))
{
	d_func()->init();
	setEventFilter();
}

CustomAvatar::CustomAvatar(const QIcon &icon, QWidget *parent)
	: QWidget(parent),
	d_ptr(new CustomAvatarPrivate(this))
{
	d_func()->init();

	setIcon(icon);

	setEventFilter();
}

CustomAvatar::CustomAvatar(const QChar &letter, QWidget *parent)
	: QWidget(parent),
	d_ptr(new CustomAvatarPrivate(this))
{
	d_func()->init();

	setLetter(letter);

	setEventFilter();
}

CustomAvatar::CustomAvatar(const QImage &image, QWidget *parent)
	: QWidget(parent),
	d_ptr(new CustomAvatarPrivate(this))
{
	d_func()->init();

	setImage(image);

	setEventFilter();
}

CustomAvatar::~CustomAvatar()
{
}

void CustomAvatar::setUseThemeColors(bool value)
{
	Q_D(CustomAvatar);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	update();
}

bool CustomAvatar::useThemeColors() const
{
	Q_D(const CustomAvatar);

	return d->useThemeColors;
}

void CustomAvatar::setTextColor(const QColor &color)
{
	Q_D(CustomAvatar);

	d->textColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomAvatar::textColor() const
{
	Q_D(const CustomAvatar);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CustomStyle::instance().themeColor("canvas");
	}
	else {
		return d->textColor;
	}
}

void CustomAvatar::setBackgroundColor(const QColor &color)
{
	Q_D(CustomAvatar);

	d->backgroundColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		update();
}

QColor CustomAvatar::backgroundColor() const
{
	Q_D(const CustomAvatar);

	if (d->useThemeColors || !d->backgroundColor.isValid()) {
		return CustomStyle::instance().themeColor("primary1");
	}
	else {
		return d->backgroundColor;
	}
}

/*!
*  \reimp
*/
QSize CustomAvatar::sizeHint() const
{
	Q_D(const CustomAvatar);

	return QSize(d->size + 2, d->size + 2);
}

void CustomAvatar::setSize(int size)
{
	Q_D(CustomAvatar);

	d->size = size;

	if (!d->image.isNull()) {
		d->pixmap = QPixmap::fromImage(d->image.scaled(d->size, d->size,

			Qt::IgnoreAspectRatio,
			Qt::SmoothTransformation));
	}

	QFont f(font());
	f.setPointSizeF(size * 16 / 40);
	setFont(f);

	update();
}

void CustomAvatar::setEventFilter()
{
	Q_D(CustomAvatar);

	d->q_ptr->installEventFilter(this);
}

int CustomAvatar::size() const
{
	Q_D(const CustomAvatar);

	return d->size;
}

void CustomAvatar::setLetter(const QChar &letter)
{
	Q_D(CustomAvatar);

	d->letter = letter;
	d->type = Material::LetterAvatar;
	update();
}

void CustomAvatar::setImage(const QImage &image)
{
	Q_D(CustomAvatar);

	d->image = image;
	d->type = Material::ImageAvatar;

	d->pixmap = QPixmap::fromImage(image.scaled(d->size, d->size,
		Qt::IgnoreAspectRatio,
		Qt::SmoothTransformation));
	update();
}

void CustomAvatar::setIcon(const QIcon &icon)
{
	Q_D(CustomAvatar);

	d->icon = icon;
	d->type = Material::IconAvatar;
	update();
}

void CustomAvatar::setButton(const QIcon &icon)
{
	Q_D(CustomAvatar);

	d->icon = icon;
	d->type = Material::ButtonAvatar;
	update();
}

void CustomAvatar::setTwoIcons(const QIcon &icon, int twoIconsPadding)
{
	Q_D(CustomAvatar);

	d->icon = icon;
	d->type = Material::TwoIconsAvatar;
	TwoIconsPadding = twoIconsPadding;
	update();
}

Material::AvatarType CustomAvatar::type() const
{
	Q_D(const CustomAvatar);

	return d->type;
}

void CustomAvatar::mouseMoveEvent(QMouseEvent *event)
{
	Q_D(CustomAvatar);

	isEnter = true;

	update();

	QWidget::mouseMoveEvent(event);
}

void CustomAvatar::mouseReleaseEvent(QMouseEvent *event)
{
	Q_D(CustomAvatar);

	QWidget::mouseReleaseEvent(event);
}

void CustomAvatar::mousePressEvent(QMouseEvent *event)
{
	Q_D(CustomAvatar);

	QWidget::mousePressEvent(event);

	emit pressEvent();
}

bool CustomAvatar::eventFilter(QObject *watched, QEvent *event)
{
	//customfocus
	//qDebug() << event->type();

	if (QEvent::Leave == event->type()) {

		isEnter = false;
		update();

	}

	return false;
}


/*!
*  \reimp
*/
void CustomAvatar::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomAvatar);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QRect r = rect();
	qreal hs = d->size / 2;


	if (!isEnabled())
	{
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(QColor(137, 138, 141));
		painter.setPen(Qt::NoPen);
		painter.setBrush(brush);
		painter.drawEllipse(QRectF((width() - d->size) / 2, (height() - d->size) / 2,
			d->size, d->size));

		QRect iconGeometry((width() - hs) / 2, (height() - hs) / 2, hs, hs);
		QPixmap pixmap = d->icon.pixmap(hs, hs);
		QPainter icon(&pixmap);
		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);

		//Custom Material
		icon.fillRect(pixmap.rect(), QColor(100, 101, 101));
		painter.drawPixmap(iconGeometry, pixmap);
		
		return;
	}

	//background color, Around color
	if (Material::IconAvatar == d->type && Material::LetterAvatar == d->type)
	{
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(backgroundColor());
		QPen pen(Qt::NoPen);
		painter.setPen(pen);
		painter.setBrush(brush);
		painter.drawEllipse(QRectF((width() - d->size) / 2, (height() - d->size) / 2,
			d->size, d->size));
	}
	else if (Material::TwoIconsAvatar == d->type)
	{
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);

		QColor color;

		if (theme != nullptr)
		{
			if (theme->themeType == Theme::ThemeType::whiteRed)
				color = QColor(159, 34, 65);
			else
				color = QColor(42, 125, 225);
		}
		else
			color = QColor(159, 34, 65);


		if (status == "Checked")
		{
			QPen pen(color, 2);
			painter.setPen(pen);
			
			if (theme != nullptr)
			{
				if (theme->themeType == Theme::ThemeType::whiteRed)
					brush.setColor(Qt::white);
				else
					brush.setColor(QColor(10, 34, 64));
			}
			else
				brush.setColor(Qt::white);

		}
		else if (status == "Current")
		{
			QPen pen(Qt::NoPen);
			painter.setPen(pen);
			brush.setColor(color);
		}
		else
		{
			QPen pen(Qt::NoPen);
			painter.setPen(pen);
			brush.setColor(backgroundColor());
		}

		painter.setBrush(brush);
		painter.drawEllipse(QRectF((width() - d->size) / 2 + (TwoIconsPadding / 2), (height() - d->size) / 2 + TwoIconsPadding,
			d->size - TwoIconsPadding, d->size - TwoIconsPadding));
	}
	else if (Material::ButtonAvatar == d->type)
	{
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);

		if (theme != nullptr)
		{
			if (theme->themeType == Theme::ThemeType::whiteRed)
			{
				brush.setColor(backgroundColor());

				if (isEnter)
				{
					QPen pen(QColor(159, 34, 65), 2);
					painter.setPen(pen);
				}
				else
				{
					QPen pen(QColor(255, 255, 255, 102), 2);
					painter.setPen(pen);
				}
			}
			else
			{
				brush.setColor(QColor(10, 34, 64));

				if (isEnter)
				{
					QPen pen(QColor(42, 125, 225), 2);
					painter.setPen(pen);
				}
				else
				{
					QPen pen(QColor(255, 255, 255, 102), 2);
					painter.setPen(pen);
				}
			}
		}
		else
		{
			brush.setColor(backgroundColor());

			if (isEnter)
			{
				QPen pen(QColor(159, 34, 65), 2);
				painter.setPen(pen);
			}
			else
			{
				QPen pen(QColor(255, 255, 255, 102), 2);
				painter.setPen(pen);
			}
		}

		painter.setBrush(brush);
		painter.drawEllipse(QRectF((width() - d->size) / 2, (height() - d->size) / 2,
			d->size, d->size));
	}

	//Pixmap color
	switch (d->type)
	{
	case Material::ImageAvatar:
	{
		QPainterPath path;
		path.addEllipse(width() / 2 - hs, height() / 2 - hs, d->size, d->size);
		painter.setClipPath(path);

		painter.drawPixmap(QRect(width() / 2 - hs, height() / 2 - hs, d->size, d->size),
			d->pixmap);
		break;
	}
	case Material::IconAvatar:
	{
		QRect iconGeometry((width() - hs) / 2, (height() - hs) / 2, hs, hs);
		QPixmap pixmap = d->icon.pixmap(hs, hs);
		QPainter icon(&pixmap);
		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
		
		//Custom Material
		//icon.fillRect(pixmap.rect(), textColor());
		painter.drawPixmap(iconGeometry, pixmap);
		break;
	}
	case Material::LetterAvatar:
	{
		painter.setPen(textColor());
		painter.setBrush(Qt::NoBrush);
		painter.drawText(r, Qt::AlignCenter, QString(d->letter));
		break;
	}
	case Material::TwoIconsAvatar:
	{
		QColor color;

		if (theme != nullptr)
		{
			if (theme->themeType == Theme::ThemeType::whiteRed)
				color = QColor(159, 34, 65);
			else
				color = QColor(255, 255, 255);
		}
		else
			color = QColor(159, 34, 65);

		hs = d->size / 2 - TwoIconsPadding / 2;

		QRect iconGeometry((width() - hs) / 2, (height() - hs) / 2 + TwoIconsPadding / 2, hs, hs);
		QPixmap pixmap = d->icon.pixmap(hs, hs);
		QPainter icon(&pixmap);
		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
		
		//icon.fillRect(pixmap.rect(), textColor());
		if (status == "Checked")
			icon.fillRect(pixmap.rect(), color);
		else if (status == "Current")
			icon.fillRect(pixmap.rect(), QColor(255, 255, 255));

		painter.drawPixmap(iconGeometry, pixmap);
		break;
	}
	case Material::ButtonAvatar:
	{
		QRect iconGeometry((width() - hs) / 2, (height() - hs) / 2, hs, hs);
		QPixmap pixmap = d->icon.pixmap(hs, hs);
		QPainter icon(&pixmap);
		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);

		//Custom Material
		//icon.fillRect(pixmap.rect(), textColor());
		painter.drawPixmap(iconGeometry, pixmap);
		break;
	}
	default:
		break;
	}
}
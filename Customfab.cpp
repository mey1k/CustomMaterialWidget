#include "Customfab.h"
#include "Customfab_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QState>
#include <QEvent>
#include <QPainter>
#include "Customrippleoverlay.h"

/*!
*  \class CustomFloatingActionButtonPrivate
*  \internal
*/

/*!
*  \internal
*/
CustomFloatingActionButtonPrivate::CustomFloatingActionButtonPrivate(CustomFloatingActionButton *q)
	: CustomRaisedButtonPrivate(q)
{
}

/*!
*  \internal
*/
CustomFloatingActionButtonPrivate::~CustomFloatingActionButtonPrivate()
{
}

/*!
*  \internal
*/
void CustomFloatingActionButtonPrivate::init()
{
	Q_Q(CustomFloatingActionButton);

	corner = Qt::BottomRightCorner;
	mini = false;
	offsX = 34;
	offsY = 36;

	q->setRole(Material::Primary);
	q->setFixedSize(DefaultDiameter, DefaultDiameter);
	q->setGeometry(fabGeometry());

	setupProperties();

	if (q->parentWidget()) {
		q->parentWidget()->installEventFilter(q);
	}

	q->setFixedRippleRadius(50);
}

/*!
*  \internal
*/
QRect CustomFloatingActionButtonPrivate::fabGeometry() const
{
	Q_Q(const CustomFloatingActionButton);

	QWidget *parent = q->parentWidget();
	if (!parent) {
		return QRect();
	}

	const int s = mini ? MiniDiameter : DefaultDiameter;

	switch (corner)
	{
	case Qt::TopLeftCorner:
		return QRect(offsX, offsY, s, s);
	case Qt::TopRightCorner:
		return QRect(parent->width() - (offsX + s), offsY, s, s);
	case Qt::BottomLeftCorner:
		return QRect(offsX, parent->height() - (offsY + s), s, s);
	case Qt::BottomRightCorner:
	default:
		break;
	}
	return QRect(parent->width() - (offsX + s), parent->height() - (offsY + s), s, s);
}

/*!
*  \internal
*/
void CustomFloatingActionButtonPrivate::setupProperties()
{
	if (mini) {
		effect->setColor(QColor(0, 0, 0, 80));
		normalState->assignProperty(effect, "offset", QPointF(0, 3));
		normalState->assignProperty(effect, "blurRadius", 13);
		pressedState->assignProperty(effect, "offset", QPointF(0, 7));
		pressedState->assignProperty(effect, "blurRadius", 20);
	}
	else {
		effect->setColor(QColor(0, 0, 0, 105));
		normalState->assignProperty(effect, "offset", QPointF(0, 6));
		normalState->assignProperty(effect, "blurRadius", 16);
		pressedState->assignProperty(effect, "offset", QPointF(0, 11));
		pressedState->assignProperty(effect, "blurRadius", 28);
	}
}

/*!
*  \class CustomFloatingActionButton
*/

CustomFloatingActionButton::CustomFloatingActionButton(const QIcon &icon, QWidget *parent)
	: CustomRaisedButton(*new CustomFloatingActionButtonPrivate(this), parent)
{
	d_func()->init();

	setIcon(icon);
}

CustomFloatingActionButton::~CustomFloatingActionButton()
{
}

/*!
*  \reimp
*/
QSize CustomFloatingActionButton::sizeHint() const
{
	Q_D(const CustomFloatingActionButton);

	if (d->mini) {
		return QSize(CustomFloatingActionButtonPrivate::MiniDiameter,
			CustomFloatingActionButtonPrivate::MiniDiameter);
	}
	else {
		return QSize(CustomFloatingActionButtonPrivate::DefaultDiameter,
			CustomFloatingActionButtonPrivate::DefaultDiameter);
	}
}

void CustomFloatingActionButton::setMini(bool state)
{
	Q_D(CustomFloatingActionButton);

	if (d->mini == state) {
		return;
	}

	d->mini = state;

	setFixedSize(d->diameter(), d->diameter());
	setFixedRippleRadius(state ? 30 : 50);

	d->setupProperties();
	updateClipPath();
	setGeometry(d->fabGeometry());
	update();
}

bool CustomFloatingActionButton::isMini() const
{
	Q_D(const CustomFloatingActionButton);

	return d->mini;
}

void CustomFloatingActionButton::setCorner(Qt::Corner corner)
{
	Q_D(CustomFloatingActionButton);

	if (d->corner == corner) {
		return;
	}

	d->corner = corner;
	setGeometry(d->fabGeometry());
	update();
}

Qt::Corner CustomFloatingActionButton::corner() const
{
	Q_D(const CustomFloatingActionButton);

	return d->corner;
}

void CustomFloatingActionButton::setOffset(int x, int y)
{
	Q_D(CustomFloatingActionButton);

	d->offsX = x;
	d->offsY = y;
	setGeometry(d->fabGeometry());
	update();
}

QSize CustomFloatingActionButton::offset() const
{
	Q_D(const CustomFloatingActionButton);

	return QSize(d->offsX, d->offsY);
}

void CustomFloatingActionButton::setXOffset(int x)
{
	Q_D(CustomFloatingActionButton);

	d->offsX = x;
	setGeometry(d->fabGeometry());
	update();
}

int CustomFloatingActionButton::xOffset() const
{
	Q_D(const CustomFloatingActionButton);

	return d->offsX;
}

void CustomFloatingActionButton::setYOffset(int y)
{
	Q_D(CustomFloatingActionButton);

	d->offsY = y;
	setGeometry(d->fabGeometry());
	update();
}

int CustomFloatingActionButton::yOffset() const
{
	Q_D(const CustomFloatingActionButton);

	return d->offsY;
}

/*!
*  \reimp
*/
bool CustomFloatingActionButton::event(QEvent *event)
{
	Q_D(CustomFloatingActionButton);

	if (!parent()) {
		return CustomRaisedButton::event(event);
	}
	switch (event->type())
	{
	case QEvent::ParentChange:
	{
		parent()->installEventFilter(this);
		setGeometry(d->fabGeometry());
		break;
	}
	case QEvent::ParentAboutToChange:
	{
		parent()->removeEventFilter(this);
		break;
	}
	default:
		break;
	}
	return CustomRaisedButton::event(event);
}

/*!
*  \reimp
*/
bool CustomFloatingActionButton::eventFilter(QObject *obj, QEvent *event)
{
	const QEvent::Type type = event->type();

	if (QEvent::Move == type || QEvent::Resize == type)
	{
		Q_D(CustomFloatingActionButton);
		setGeometry(d->fabGeometry());
	}

	return CustomRaisedButton::eventFilter(obj, event);
}

/*!
*  \reimp
*/
void CustomFloatingActionButton::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		Q_D(CustomFloatingActionButton);

	QRect square = QRect(0, 0, d->diameter(), d->diameter());
	square.moveCenter(rect().center());

	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);

	if (isEnabled()) {
		brush.setColor(backgroundColor());
	}
	else {
		brush.setColor(disabledBackgroundColor());
	}

	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(square);

	QRect iconGeometry(0, 0, d->iconSize(), d->iconSize());
	iconGeometry.moveCenter(square.center());

	QPixmap pixmap = icon().pixmap(QSize(d->iconSize(), d->iconSize()));
	QPainter icon(&pixmap);
	icon.setCompositionMode(QPainter::CompositionMode_SourceIn);

	//Custom Material
	//icon.fillRect(pixmap.rect(), isEnabled() ? foregroundColor()
	//	: disabledForegroundColor());
	painter.drawPixmap(iconGeometry, pixmap);
}

void CustomFloatingActionButton::updateClipPath()
{
	Q_D(CustomFloatingActionButton);

	QPainterPath path;
	path.addEllipse(0, 0, d->diameter(), d->diameter());
	d->rippleOverlay->setClipPath(path);
}

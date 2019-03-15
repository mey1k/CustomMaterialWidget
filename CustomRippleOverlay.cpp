#include "Customrippleoverlay.h"
#include <QPainter>
#include "Customripple.h"

/*!
*  \class CustomRippleOverlay
*  \internal
*/

CustomRippleOverlay::CustomRippleOverlay(QWidget *parent)
	: CustomOverlayWidget(parent),
	m_useClip(false)
{
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setAttribute(Qt::WA_NoSystemBackground);
}

CustomRippleOverlay::~CustomRippleOverlay()
{
}

void CustomRippleOverlay::addRipple(CustomRipple *ripple)
{
	ripple->setOverlay(this);
	m_ripples.push_back(ripple);
	ripple->start();

	connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(stop()));
	connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(deleteLater()));
}

void CustomRippleOverlay::addRipple(const QPoint &position, qreal radius)
{
	CustomRipple *ripple = new CustomRipple(position);
	ripple->setRadiusEndValue(radius);
	addRipple(ripple);
}

void CustomRippleOverlay::removeRipple(CustomRipple *ripple)
{
	if (m_ripples.removeOne(ripple)) {
		delete ripple;
		update();
	}
}

/*!
*  \reimp
*/
void CustomRippleOverlay::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);

	if (m_useClip) {
		painter.setClipPath(m_clipPath);
	}

	QList<CustomRipple *>::const_iterator i;
	for (i = m_ripples.begin(); i != m_ripples.end(); ++i) {
		paintRipple(&painter, *i);
	}
}

void CustomRippleOverlay::paintRipple(QPainter *painter, CustomRipple *ripple)
{
	const qreal radius = ripple->radius();
	const QPointF center = ripple->center();
	painter->setOpacity(ripple->opacity());
	painter->setBrush(ripple->brush());
	painter->drawEllipse(center, radius, radius);
}

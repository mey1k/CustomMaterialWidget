#include "Customdialog_internal.h"
#include <QPainter>
#include <QPixmap>
#include <QEvent>
#include <QtWidgets/QStackedLayout>
#include "Customdialog.h"

/*!
*  \class CustomDialogProxy
*  \internal
*/

CustomDialogProxy::CustomDialogProxy(
	CustomDialogWindow *source,
	QStackedLayout         *layout,
	CustomDialog       *dialog,
	QWidget                *parent)
	: QWidget(parent),
	m_source(source),
	m_layout(layout),
	m_dialog(dialog),
	m_opacity(0),
	m_mode(Transparent)
{
}

CustomDialogProxy::~CustomDialogProxy()
{
}

void CustomDialogProxy::setOpacity(qreal opacity)
{
	m_opacity = opacity;
	m_mode = SemiTransparent;
	update();
	m_dialog->update();
}


void CustomDialogProxy::makeOpaque()
{
	m_dialog->setAttribute(Qt::WA_TransparentForMouseEvents, false);
	m_layout->setCurrentIndex(0);
	m_opacity = 1.0;
	m_mode = Opaque;
	update();
}

void CustomDialogProxy::makeTransparent()
{
	m_opacity = 0.0;
	m_mode = Transparent;
	update();
}

QSize CustomDialogProxy::sizeHint() const
{
	return m_source->sizeHint();
}

bool CustomDialogProxy::event(QEvent *event)
{
	const QEvent::Type type = event->type();

	if (QEvent::Move == type || QEvent::Resize == type) {
		m_source->setGeometry(geometry());
	}
	return QWidget::event(event);
}

void CustomDialogProxy::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		QPainter painter(this);

	if (Transparent == m_mode) {
		return;
	}
	else if (Opaque != m_mode) {
		painter.setOpacity(m_opacity);
	}
	QPixmap pm = m_source->grab(m_source->rect());
	painter.drawPixmap(0, 0, pm);
}

/*!
*  \class CustomDialogWindow
*  \internal
*/

CustomDialogWindow::CustomDialogWindow(
	CustomDialog *dialog,
	QWidget          *parent)
	: QWidget(parent),
	m_dialog(dialog)
{
}

CustomDialogWindow::~CustomDialogWindow()
{
}

void CustomDialogWindow::setOffset(int offset)
{
	QMargins margins = m_dialog->layout()->contentsMargins();
	margins.setBottom(offset);
	m_dialog->layout()->setContentsMargins(margins);
}

int CustomDialogWindow::offset() const
{
	return m_dialog->layout()->contentsMargins().bottom();
}

void CustomDialogWindow::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

		QPainter painter(this);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::white);
	painter.setPen(Qt::NoPen);
	painter.setBrush(brush);
	painter.drawRect(rect());
}

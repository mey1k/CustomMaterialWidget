#include "stdafx.h"
#include "CustomOverlayWidget.h"
#include <QEvent>

/*!
*  \class CustomOverlayWidget
*  \internal
*/

CustomOverlayWidget::CustomOverlayWidget(QWidget *parent)
	: QWidget(parent)
{
	if (parent) {
		parent->installEventFilter(this);
	}
}

CustomOverlayWidget::~CustomOverlayWidget()
{
}

/*!
*  \reimp
*/
bool CustomOverlayWidget::event(QEvent *event)
{
	if (!parent()) {
		return QWidget::event(event);
	}
	switch (event->type())
	{
	case QEvent::ParentChange:
	{
		parent()->installEventFilter(this);
		setGeometry(overlayGeometry());
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
	return QWidget::event(event);
}

/*!
*  \reimp
*/
bool CustomOverlayWidget::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::Move:
	case QEvent::Resize:
		setGeometry(overlayGeometry());
		break;
	default:
		break;
	}
	return QWidget::eventFilter(obj, event);
}

QRect CustomOverlayWidget::overlayGeometry() const
{
	//test
	/*QRect *rect = new QRect();
	rect->setX(100);
	rect->setY(100);
	rect->setWidth(300);
	rect->setHeight(300);

	return *rect;*/

	QWidget *widget = parentWidget();
	if (!widget) {
		return QRect();
	}
	return widget->rect();
}

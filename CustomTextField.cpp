#include "Customtextfield.h"
#include "Customtextfield_p.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "Customtextfield_internal.h"
#include "Customstyle.h"
#include <QDebug>

/*!
*  \class CustomTextFieldPrivate
*  \internal
*/

CustomTextFieldPrivate::CustomTextFieldPrivate(CustomTextField *q)
	: q_ptr(q)
{
}

CustomTextFieldPrivate::~CustomTextFieldPrivate()
{
}

void CustomTextFieldPrivate::init()
{
	Q_Q(CustomTextField);

	stateMachine = new CustomTextFieldStateMachine(q);
	label = 0;
	labelFontSize = 9.5;
	showLabel = false;
	showInputLine = true;
	useThemeColors = true;

	q->setFrame(false);
	q->setStyle(&CustomStyle::instance());
	q->setAttribute(Qt::WA_Hover);
	q->setMouseTracking(true);
	q->setTextMargins(0, 2, 0, 4);

	q->setFont(QFont("Roboto", 11, QFont::Normal));

	stateMachine->start();
	QCoreApplication::processEvents();
}

/*!
*  \class CustomTextField
*/

CustomTextField::CustomTextField(QWidget *parent)
	: QLineEdit(parent),
	d_ptr(new CustomTextFieldPrivate(this))
{
	d_func()->init();
}

CustomTextField::~CustomTextField()
{
}

void CustomTextField::setUseThemeColors(bool value)
{
	Q_D(CustomTextField);

	if (d->useThemeColors == value) {
		return;
	}

	d->useThemeColors = value;
	d->stateMachine->setupProperties();
}

bool CustomTextField::useThemeColors() const
{
	Q_D(const CustomTextField);

	return d->useThemeColors;
}

void CustomTextField::setShowLabel(bool value)
{
	Q_D(CustomTextField);

	if (d->showLabel == value) {
		return;
	}

	d->showLabel = value;

	if (!d->label && value) {
		d->label = new CustomTextFieldLabel(this);
		d->stateMachine->setLabel(d->label);
	}

	if (value) {
		setContentsMargins(0, 23, 0, 0);
	}
	else {
		setContentsMargins(0, 0, 0, 0);
	}
}

bool CustomTextField::hasLabel() const
{
	Q_D(const CustomTextField);

	return d->showLabel;
}

void CustomTextField::setLabelFontSize(qreal size)
{
	Q_D(CustomTextField);

	d->labelFontSize = size;

	if (d->label)
	{
		QFont font(d->label->font());
		font.setPointSizeF(size);
		d->label->setFont(font);
		d->label->update();
	}
}

qreal CustomTextField::labelFontSize() const
{
	Q_D(const CustomTextField);

	return d->labelFontSize;
}

void CustomTextField::setLabel(const QString &label)
{
	Q_D(CustomTextField);

	d->labelString = label;
	setShowLabel(true);
	d->label->update();
}

QString CustomTextField::label() const
{
	Q_D(const CustomTextField);

	return d->labelString;
}

void CustomTextField::setTextColor(const QColor &color)
{
	Q_D(CustomTextField);

	d->textColor = color;
	setStyleSheet(QString("QLineEdit { color: %1; }").arg(color.name()));

	MATERIAL_DISABLE_THEME_COLORS
		d->stateMachine->setupProperties();
}

QColor CustomTextField::textColor() const
{
	Q_D(const CustomTextField);

	if (d->useThemeColors || !d->textColor.isValid()) {
		return CustomStyle::instance().themeColor("text");
	}
	else {
		return d->textColor;
	}
}

void CustomTextField::setLabelColor(const QColor &color)
{
	Q_D(CustomTextField);

	d->labelColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		d->stateMachine->setupProperties();
}

QColor CustomTextField::labelColor() const
{
	Q_D(const CustomTextField);

	if (d->useThemeColors || !d->labelColor.isValid()) {
		return CustomStyle::instance().themeColor("accent3");
	}
	else {
		return d->labelColor;
	}
}

void CustomTextField::setInkColor(const QColor &color)
{
	Q_D(CustomTextField);

	d->inkColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		d->stateMachine->setupProperties();
}

QColor CustomTextField::inkColor() const
{
	Q_D(const CustomTextField);

	if (d->useThemeColors || !d->inkColor.isValid()) {
		return CustomStyle::instance().themeColor("primary1");
	}
	else {
		return d->inkColor;
	}
}

void CustomTextField::setInputLineColor(const QColor &color)
{
	Q_D(CustomTextField);

	d->inputLineColor = color;

	MATERIAL_DISABLE_THEME_COLORS
		d->stateMachine->setupProperties();
}

QColor CustomTextField::inputLineColor() const
{
	Q_D(const CustomTextField);

	if (d->useThemeColors || !d->inputLineColor.isValid()) {
		return CustomStyle::instance().themeColor("border");
	}
	else {
		return d->inputLineColor;
	}
}

void CustomTextField::setShowInputLine(bool value)
{
	Q_D(CustomTextField);

	if (d->showInputLine == value) {
		return;
	}

	d->showInputLine = value;
	update();
}

bool CustomTextField::hasInputLine() const
{
	Q_D(const CustomTextField);

	return d->showInputLine;
}

CustomTextField::CustomTextField(CustomTextFieldPrivate &d, QWidget *parent)
	: QLineEdit(parent),
	d_ptr(&d)
{
	d_func()->init();
}

/*!
*  \reimp
*/
bool CustomTextField::event(QEvent *event)
{
	Q_D(CustomTextField);

	switch (event->type())
	{
	case QEvent::Resize:
	case QEvent::Move: {
		if (d->label) {
			d->label->setGeometry(rect());
		}
	}
	default:
		break;
	}
	return QLineEdit::event(event);
}

/*!
*  \reimp
*/
void CustomTextField::paintEvent(QPaintEvent *event)
{
	Q_D(CustomTextField);

	QLineEdit::paintEvent(event);

	QPainter painter(this);

	const qreal progress = d->stateMachine->progress();

	if (text().isEmpty() && progress < 1)
	{
		painter.setOpacity(1 - progress);
		painter.fillRect(rect(), parentWidget()->palette().color(backgroundRole()));
	}

	const int y = height() - 1;
	const int wd = width() - 5;

	if (d->showInputLine)
	{
		QPen pen;
		pen.setWidth(1);
		pen.setColor(inputLineColor());

		if (!isEnabled())
			pen.setStyle(Qt::DashLine);

		painter.setPen(pen);
		painter.setOpacity(1);
		painter.drawLine(QLineF(2.5, y, wd, y));

		//test
		QLinearGradient gradient(0, 0, width(), height());
		/*gradient.setColorAt(0, QColor(230, 230, 230, 20));
		gradient.setColorAt(0.27, QColor(110, 110, 110));
		gradient.setColorAt(0.44, QColor(230, 230, 230, 20));
		gradient.setColorAt(0.76, QColor(110, 110, 110));
		gradient.setColorAt(1, QColor(230, 230, 230, 20));*/
		gradient.setColorAt(0, QColor(230, 230, 230, 20));
		gradient.setColorAt(0.25, QColor(230, 230, 230, 50));
		
		gradient.setColorAt(0.5, inkColor());
		
		gradient.setColorAt(0.75, QColor(230, 230, 230, 50));
		gradient.setColorAt(1, QColor(230, 230, 230, 20));


		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(inkColor());

		if (progress > 0)
		{
			painter.setPen(Qt::NoPen);
			//painter.setBrush(brush);
			painter.setBrush(gradient);
			const int w = (1 - progress)*static_cast<qreal>(wd / 2);
			painter.drawRect(w + 2.5, height() - 2, wd - w * 2, 2);
		}
	}
}

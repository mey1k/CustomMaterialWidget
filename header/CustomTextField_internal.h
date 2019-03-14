#ifndef CustomTEXTFIELD_INTERNAL_H
#define CustomTEXTFIELD_INTERNAL_H

#include <QStateMachine>
#include <QtWidgets/QWidget>
#include "Customtextfield.h"

class QPropertyAnimation;
class CustomTextFieldLabel;

class CustomTextFieldStateMachine : public QStateMachine
{
	Q_OBJECT

		Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
	CustomTextFieldStateMachine(CustomTextField *parent);
	~CustomTextFieldStateMachine();

	void setLabel(CustomTextFieldLabel *label);

	inline void setProgress(qreal progress);
	inline qreal progress() const;

public slots:
	void setupProperties();

private:
	Q_DISABLE_COPY(CustomTextFieldStateMachine)

		CustomTextField *const m_textField;
	QState              *const m_normalState;
	QState              *const m_focusedState;
	CustomTextFieldLabel  *m_label;
	QPropertyAnimation        *m_offsetAnimation;
	QPropertyAnimation        *m_colorAnimation;
	qreal                      m_progress;
};

inline void CustomTextFieldStateMachine::setProgress(qreal progress)
{
	m_progress = progress;
	m_textField->update();
}

inline qreal CustomTextFieldStateMachine::progress() const
{
	return m_progress;
}

class CustomTextFieldLabel : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(qreal scale WRITE setScale READ scale)
		Q_PROPERTY(QPointF offset WRITE setOffset READ offset)
		Q_PROPERTY(QColor color WRITE setColor READ color)

public:
	CustomTextFieldLabel(CustomTextField *parent);
	~CustomTextFieldLabel();

	inline void setScale(qreal scale);
	inline qreal scale() const;

	inline void setOffset(const QPointF &pos);
	inline QPointF offset() const;

	inline void setColor(const QColor &color);
	inline QColor color() const;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomTextFieldLabel)

		CustomTextField *const m_textField;
	qreal                      m_scale;
	qreal                      m_posX;
	qreal                      m_posY;
	QColor                     m_color;
};

inline void CustomTextFieldLabel::setScale(qreal scale)
{
	m_scale = scale;
	update();
}

inline qreal CustomTextFieldLabel::scale() const
{
	return m_scale;
}

inline void CustomTextFieldLabel::setOffset(const QPointF &pos)
{
	m_posX = pos.x();
	m_posY = pos.y();
	update();
}

inline QPointF CustomTextFieldLabel::offset() const
{
	return QPointF(m_posX, m_posY);
}

inline void CustomTextFieldLabel::setColor(const QColor &color)
{
	m_color = color;
	update();
}

inline QColor CustomTextFieldLabel::color() const
{
	return m_color;
}

#endif // CustomTEXTFIELD_INTERNAL_H

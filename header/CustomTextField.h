#ifndef CustomTEXTFIELD_H
#define CustomTEXTFIELD_H

#include <QtWidgets/QLineEdit>
#include <QColor>

class CustomTextFieldPrivate;

class CustomTextField : public QLineEdit
{
	Q_OBJECT

		Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
		Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
		Q_PROPERTY(QColor inputLineColor WRITE setInputLineColor READ inputLineColor)

public:
	explicit CustomTextField(QWidget *parent = 0);
	~CustomTextField();

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setShowLabel(bool value);
	bool hasLabel() const;

	void setLabelFontSize(qreal size);
	qreal labelFontSize() const;

	void setLabel(const QString &label);
	QString label() const;

	void setTextColor(const QColor &color);
	QColor textColor() const;

	void setLabelColor(const QColor &color);
	QColor labelColor() const;

	void setInkColor(const QColor &color);
	QColor inkColor() const;

	void setInputLineColor(const QColor &color);
	QColor inputLineColor() const;

	void setShowInputLine(bool value);
	bool hasInputLine() const;

protected:
	CustomTextField(CustomTextFieldPrivate &d, QWidget *parent = 0);

	bool event(QEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	const QScopedPointer<CustomTextFieldPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomTextField)
		Q_DECLARE_PRIVATE(CustomTextField)
};

#endif // CustomTEXTFIELD_H

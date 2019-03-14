#ifndef CustomTOGGLE_H
#define CustomTOGGLE_H

#include <QtWidgets/QAbstractButton>

class CustomTogglePrivate;

class CustomToggle : public QAbstractButton
{
	Q_OBJECT

		Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)
		Q_PROPERTY(QColor activeColor WRITE setActiveColor READ activeColor)
		Q_PROPERTY(QColor inactiveColor WRITE setInactiveColor READ inactiveColor)
		Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
	explicit CustomToggle(QWidget *parent = 0);
	~CustomToggle();

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setDisabledColor(const QColor &color);
	QColor disabledColor() const;

	void setActiveColor(const QColor &color);
	QColor activeColor() const;

	void setInactiveColor(const QColor &color);
	QColor inactiveColor() const;

	void setTrackColor(const QColor &color);
	QColor trackColor() const;

	void setOrientation(Qt::Orientation orientation);
	Qt::Orientation orientation() const;

	QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
	bool event(QEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	const QScopedPointer<CustomTogglePrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomToggle)
		Q_DECLARE_PRIVATE(CustomToggle)
};

#endif // CustomTOGGLE_H

#ifndef CustomFLATBUTTON_H
#define CustomFLATBUTTON_H

#include <QtWidgets/QPushButton>
#include <QScopedPointer>
#include <qapplication.h>
#include "CustomTheme.h"
#include <qdesktopwidget.h>

class CustomFlatButtonPrivate;

class CustomFlatButton : public QPushButton
{
	Q_OBJECT

		Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
		Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
		Q_PROPERTY(QColor overlayColor WRITE setOverlayColor READ overlayColor)
		Q_PROPERTY(QColor disabledForegroundColor WRITE setDisabledForegroundColor READ disabledForegroundColor)
		Q_PROPERTY(QColor disabledBackgroundColor WRITE setDisabledBackgroundColor READ disabledBackgroundColor)
		Q_PROPERTY(qreal fontSize WRITE setFontSize READ fontSize)

public:
	explicit CustomFlatButton(QWidget *parent = 0, Material::ButtonPreset preset = Material::FlatPreset);
	explicit CustomFlatButton(const QString &text, QWidget *parent = 0, Material::ButtonPreset preset = Material::FlatPreset);
	CustomFlatButton(const QString &text, Material::Role role, QWidget *parent = 0, Material::ButtonPreset preset = Material::FlatPreset);
	~CustomFlatButton();

	void applyPreset(Material::ButtonPreset preset);

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setRole(Material::Role role);
	Material::Role role() const;

	void setForegroundColor(const QColor &color);
	QColor foregroundColor() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

	void setOverlayColor(const QColor &color);
	QColor overlayColor() const;

	void setDisabledForegroundColor(const QColor &color);
	QColor disabledForegroundColor() const;

	void setDisabledBackgroundColor(const QColor &color);
	QColor disabledBackgroundColor() const;

	void setFontSize(qreal size);
	qreal fontSize() const;

	void setHaloVisible(bool visible);
	bool isHaloVisible() const;

	void setOverlayStyle(Material::OverlayStyle style);
	Material::OverlayStyle overlayStyle() const;

	void setRippleStyle(Material::RippleStyle style);
	Material::RippleStyle rippleStyle() const;

	void setIconPlacement(Material::ButtonIconPlacement placement);
	Material::ButtonIconPlacement iconPlacement() const;

	void setCornerRadius(qreal radius);
	qreal cornerRadius() const;

	void setBackgroundMode(Qt::BGMode mode);
	Qt::BGMode backgroundMode() const;

	void setBaseOpacity(qreal opacity);
	qreal baseOpacity() const;

	void setCheckable(bool value);

	void setHasFixedRippleRadius(bool value);
	bool hasFixedRippleRadius() const;

	void setFixedRippleRadius(qreal radius);

	void setTextAlignment(Qt::Alignment alignment);
	Qt::Alignment textAlignment() const;

	QSize sizeHint() const Q_DECL_OVERRIDE;

	void setVisibleHalo(bool value);

	bool isFocus = false;
	bool autoFocus = true;

	int IconPadding = 0;

	void UpdateFlatButton();
	
	QColor focusOutColor = QColor(137, 138, 141);
	void setFocusOutColor(QColor color);

	void setTwoIcons(bool flag, QPixmap secondIcon, int width, int height, bool usePng);
	bool useTwoIcons = false;
	bool usePng = false;
	QPixmap secondIcon;

protected:

	CustomFlatButton(CustomFlatButtonPrivate &d, QWidget *parent = 0, Material::ButtonPreset preset = Material::FlatPreset);

	void checkStateSet() Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	virtual void paintBackground(QPainter *painter);
	virtual void paintHalo(QPainter *painter);
	virtual void paintForeground(QPainter *painter);

	virtual void updateClipPath();

	const QScopedPointer<CustomFlatButtonPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomFlatButton)
		Q_DECLARE_PRIVATE(CustomFlatButton)

	QRect rec = QApplication::desktop()->availableGeometry();
	double correctScaleW = rec.width() / 2560.0;
	double correctScaleH = rec.height() / 1400.0;
};

#endif // CustomFLATBUTTON_H

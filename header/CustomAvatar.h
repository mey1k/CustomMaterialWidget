#ifndef CustomAVATAR_H
#define CustomAVATAR_H

#include <QtWidgets/QWidget>
#include "Customtheme.h"
#include <QtWidgets/qtooltip.h>
#include <QPainter>

class CustomAvatarPrivate;

class CustomAvatar : public QWidget
{
	Q_OBJECT

public:
	explicit CustomAvatar(QWidget *parent = 0);
	explicit CustomAvatar(const QIcon &icon, QWidget *parent = 0);
	explicit CustomAvatar(const QChar &letter, QWidget *parent = 0);
	explicit CustomAvatar(const QImage &image, QWidget *parent = 0);
	~CustomAvatar();

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setTextColor(const QColor &color);
	QColor textColor() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

	QSize sizeHint() const Q_DECL_OVERRIDE;

	void setSize(int size);
	int size() const;

	void setLetter(const QChar &letter);
	void setImage(const QImage &image);
	void setIcon(const QIcon &icon);
	void setButton(const QIcon &icon);
	void setTwoIcons(const QIcon &icon, int);
	QString status = "";
	int TwoIconsPadding = 14;
	bool isEnter = false;

	Material::AvatarType type() const;

signals:
	void pressEvent();

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	bool CustomAvatar::eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
	const QScopedPointer<CustomAvatarPrivate> d_ptr;
	void setEventFilter();

private:
	Q_DISABLE_COPY(CustomAvatar)
		Q_DECLARE_PRIVATE(CustomAvatar)
};

#endif // CustomAVATAR_H

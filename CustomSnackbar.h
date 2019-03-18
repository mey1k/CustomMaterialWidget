#ifndef CustomSNACKBAR_H
#define CustomSNACKBAR_H

#include <CustomOverlayWidget.h>

class CustomSnackbarPrivate;

class CustomSnackbar : public CustomOverlayWidget
{
	Q_OBJECT

public:
	explicit CustomSnackbar(QWidget *parent = 0);
	~CustomSnackbar();

	void setAutoHideDuration(int duration);
	int autoHideDuration() const;

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

	void setBackgroundOpacity(qreal opacity);
	qreal backgroundOpacity() const;

	void setTextColor(const QColor &color);
	QColor textColor() const;

	void setFontSize(qreal size);
	qreal fontSize() const;

	void setBoxWidth(int width);
	int boxWidth() const;

	void setClickToDismissMode(bool value);
	bool clickToDismissMode() const;

public slots:
	void addMessage(const QString &message);
	void addInstantMessage(const QString &message);

protected slots:
	void dequeue();

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	const QScopedPointer<CustomSnackbarPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomSnackbar)
		Q_DECLARE_PRIVATE(CustomSnackbar)
};

#endif // CustomSNACKBAR_H

#ifndef CustomOverlayWidget_H
#define CustomOverlayWidget_H

#include <QtWidgets/QWidget>

class CustomOverlayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit CustomOverlayWidget(QWidget *parent = 0);
	~CustomOverlayWidget();

protected:
	bool event(QEvent *event) Q_DECL_OVERRIDE;
	bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

	virtual QRect overlayGeometry() const;

private:
	Q_DISABLE_COPY(CustomOverlayWidget)
};

#endif // CustomOverlayWidget_H

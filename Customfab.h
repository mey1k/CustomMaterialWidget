#ifndef CustomFAB_H
#define CustomFAB_H

#include "Customraisedbutton.h"

class CustomFloatingActionButtonPrivate;

class CustomFloatingActionButton : public CustomRaisedButton
{
	Q_OBJECT

public:
	explicit CustomFloatingActionButton(const QIcon &icon, QWidget *parent = 0);
	~CustomFloatingActionButton();

	QSize sizeHint() const Q_DECL_OVERRIDE;

	void setMini(bool state);
	bool isMini() const;

	void setCorner(Qt::Corner corner);
	Qt::Corner corner() const;

	void setOffset(int x, int y);
	QSize offset() const;

	void setXOffset(int x);
	int xOffset() const;

	void setYOffset(int y);
	int yOffset() const;

protected:
	bool event(QEvent *event) Q_DECL_OVERRIDE;
	bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	void updateClipPath() Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomFloatingActionButton)
		Q_DECLARE_PRIVATE(CustomFloatingActionButton)

};

#endif // CustomFAB_H

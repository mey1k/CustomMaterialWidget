#ifndef CustomDIALOG_H
#define CustomDIALOG_H

#include <qpainter.h>
#include <QScopedPointer>
#include "Customoverlaywidget.h"

class QLayout;
class CustomDialogPrivate;

class CautionWidget : public QWidget {

private:
	QPixmap pixmap = QPixmap(":/ThemeWhiteRed/res/img/whiteRed/warning.png");

	int cautionWrapperX = 0;
	int cautionWrapperY = 0;
	int transparentValue = 0;

public:
	QRect rec = QApplication::desktop()->availableGeometry();
	double correctScaleW = rec.width() / 2560.0;
	double correctScaleH = rec.height() / 1400.0;

	void setCautionImage()
	{
		QSize myRessortSize(70 * correctScaleW, 60 * correctScaleH);

		pixmap = pixmap.scaled(myRessortSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}

	void paintEvent(QPaintEvent *e) 
	{

		QWidget::paintEvent(e);

		QPainter painter(this);
		QPainter icon(&pixmap);

		icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
		//icon.fillRect(pixmap.rect(), QColor(159,34,65));

		painter.drawPixmap(QRect(0, 0, 70 * correctScaleW, 60 * correctScaleH ), pixmap);
	}

	void showEvent(QShowEvent *e) {
		QWidget::showEvent(e);
	}
};

class CustomDialog : public CustomOverlayWidget
{
	Q_OBJECT

public:
	explicit CustomDialog(QWidget *parent = 0);
	~CustomDialog();

	QLayout *windowLayout() const;
	void setWindowLayout(QLayout *layout);

public slots:
	void showDialog();
	void hideDialog();

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	const QScopedPointer<CustomDialogPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomDialog)
		Q_DECLARE_PRIVATE(CustomDialog)

	CautionWidget* cautionWrapper;
};

#endif // CustomDIALOG_H

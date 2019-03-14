#ifndef CustomCIRCULARPROGRESS_H
#define CustomCIRCULARPROGRESS_H

#include <QtWidgets/QProgressBar>
#include "Customtheme.h"

class CustomCircularProgressPrivate;

class CustomCircularProgress : public QProgressBar
{
	Q_OBJECT

		Q_PROPERTY(qreal lineWidth WRITE setLineWidth READ lineWidth)
		Q_PROPERTY(qreal size WRITE setSize READ size)
		Q_PROPERTY(QColor color WRITE setColor READ color)

public:
	explicit CustomCircularProgress(QWidget *parent = 0);
	~CustomCircularProgress();

	void setProgressType(Material::ProgressType type);
	Material::ProgressType progressType() const;

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setLineWidth(qreal width);
	qreal lineWidth() const;

	void setSize(int size);
	int size() const;

	void setColor(const QColor &color);
	QColor color() const;

	QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	const QScopedPointer<CustomCircularProgressPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomCircularProgress)
		Q_DECLARE_PRIVATE(CustomCircularProgress)
};

#endif // CustomCIRCULARPROGRESS_H

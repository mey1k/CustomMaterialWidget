#ifndef CustomPROGRESS_H
#define CustomPROGRESS_H

#include <QtWidgets/QProgressBar>
#include "Customtheme.h"

class CustomProgressPrivate;

class CustomProgress : public QProgressBar
{
	Q_OBJECT

		Q_PROPERTY(QColor progressColor WRITE setProgressColor READ progressColor)
		Q_PROPERTY(QColor backgroundColor WRITE setProgressColor READ backgroundColor)

public:
	explicit CustomProgress(QWidget *parent = 0);
	~CustomProgress();

	void setProgressType(Material::ProgressType type);
	Material::ProgressType progressType() const;

	void setUseThemeColors(bool state);
	bool useThemeColors() const;

	void setProgressColor(const QColor &color);
	QColor progressColor() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

	const QScopedPointer<CustomProgressPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomProgress)
		Q_DECLARE_PRIVATE(CustomProgress)
};

#endif // CustomPROGRESS_H

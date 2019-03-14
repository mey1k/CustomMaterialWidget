#ifndef CustomDIALOG_INTERNAL_H
#define CustomDIALOG_INTERNAL_H

#include <QtWidgets/QWidget>

class QStackedLayout;
class CustomDialog;
class CustomDialogWindow;

class CustomDialogProxy : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

		enum TransparencyMode {
		Transparent,
		SemiTransparent,
		Opaque,
	};

public:
	CustomDialogProxy(CustomDialogWindow *source,
		QStackedLayout *layout,
		CustomDialog *dialog,
		QWidget *parent = 0);
	~CustomDialogProxy();

	void setOpacity(qreal opacity);
	inline qreal opacity() const;

protected slots:
	void makeOpaque();
	void makeTransparent();

	QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
	bool event(QEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomDialogProxy)

		CustomDialogWindow *const m_source;
	QStackedLayout         *const m_layout;
	CustomDialog       *const m_dialog;
	qreal                         m_opacity;
	TransparencyMode              m_mode;
};

inline qreal CustomDialogProxy::opacity() const
{
	return m_opacity;
}

class CustomDialogWindow : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
	explicit CustomDialogWindow(CustomDialog *dialog, QWidget *parent = 0);
	~CustomDialogWindow();

	void setOffset(int offset);
	int offset() const;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomDialogWindow)

		CustomDialog *const m_dialog;
};

#endif // CustomDIALOG_INTERNAL_H

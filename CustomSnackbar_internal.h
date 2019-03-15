#ifndef CustomSNACKBAR_INTERNAL_H
#define CustomSNACKBAR_INTERNAL_H

#include <QStateMachine>
#include <QTimer>

class CustomSnackbar;

class CustomSnackbarStateMachine : public QStateMachine
{
	Q_OBJECT

		Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
	CustomSnackbarStateMachine(CustomSnackbar *parent);
	~CustomSnackbarStateMachine();

	void setOffset(qreal offset);
	inline qreal offset() const;

public slots:
	void progress();

protected slots:
	void snackbarShown();

protected:
	bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
	Q_DISABLE_COPY(CustomSnackbarStateMachine)

		CustomSnackbar *const m_snackbar;
	QTimer                    m_timer;
	qreal                     m_offset;
};

inline qreal CustomSnackbarStateMachine::offset() const
{
	return m_offset;
}

#endif // CustomSNACKBAR_INTERNAL_H

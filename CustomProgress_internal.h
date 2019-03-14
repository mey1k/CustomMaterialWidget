#ifndef CustomPROGRESS_INTERNAL_H
#define CustomPROGRESS_INTERNAL_H

#include <QObject>
#include "Customprogress.h"

class CustomProgressDelegate : public QObject
{
	Q_OBJECT

		Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
	CustomProgressDelegate(CustomProgress *parent);
	~CustomProgressDelegate();

	inline void setOffset(qreal offset);
	inline qreal offset() const;

private:
	Q_DISABLE_COPY(CustomProgressDelegate)

		CustomProgress *const m_progress;
	qreal                     m_offset;
};

inline void CustomProgressDelegate::setOffset(qreal offset)
{
	m_offset = offset;
	m_progress->update();
}

inline qreal CustomProgressDelegate::offset() const
{
	return m_offset;
}

#endif // CustomPROGRESS_INTERNAL_H

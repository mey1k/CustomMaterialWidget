#ifndef CustomCIRCULARPROGRESS_INTERNAL_H
#define CustomCIRCULARPROGRESS_INTERNAL_H

#include <QObject>
#include "Customcircularprogress.h"

class CustomCircularProgressDelegate : public QObject
{
	Q_OBJECT

		Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
		Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
		Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
	CustomCircularProgressDelegate(CustomCircularProgress *parent);
	~CustomCircularProgressDelegate();

	inline void setDashOffset(qreal offset);
	inline qreal dashOffset() const;

	inline void setDashLength(qreal length);
	inline qreal dashLength() const;

	inline void setAngle(int angle);
	inline int angle() const;

private:
	Q_DISABLE_COPY(CustomCircularProgressDelegate)

		CustomCircularProgress *const m_progress;
	qreal                             m_dashOffset;
	qreal                             m_dashLength;
	int                               m_angle;
};

inline void CustomCircularProgressDelegate::setDashOffset(qreal offset)
{
	m_dashOffset = offset;
	m_progress->update();
}

inline qreal CustomCircularProgressDelegate::dashOffset() const
{
	return m_dashOffset;
}

inline void CustomCircularProgressDelegate::setDashLength(qreal length)
{
	m_dashLength = length;
	m_progress->update();
}

inline qreal CustomCircularProgressDelegate::dashLength() const
{
	return m_dashLength;
}

inline void CustomCircularProgressDelegate::setAngle(int angle)
{
	m_angle = angle;
	m_progress->update();
}

inline int CustomCircularProgressDelegate::angle() const
{
	return m_angle;
}

#endif // CustomCIRCULARPROGRESS_INTERNAL_H

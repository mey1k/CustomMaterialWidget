#include "Customcircularprogress_internal.h"

/*!
*  \class CustomCircularProgressDelegate
*  \internal
*/

CustomCircularProgressDelegate::CustomCircularProgressDelegate(CustomCircularProgress *parent)
	: QObject(parent),
	m_progress(parent),
	m_dashOffset(0),
	m_dashLength(89),
	m_angle(0)
{
	Q_ASSERT(parent);
}

CustomCircularProgressDelegate::~CustomCircularProgressDelegate()
{
}

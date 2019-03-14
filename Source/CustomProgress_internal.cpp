#include "stdafx.h"
#include "Customprogress_internal.h"

/*!
*  \class CustomProgressDelegate
*  \internal
*/

CustomProgressDelegate::CustomProgressDelegate(CustomProgress *parent)
	: QObject(parent),
	m_progress(parent),
	m_offset(0)
{
	Q_ASSERT(parent);
}

CustomProgressDelegate::~CustomProgressDelegate()
{
}

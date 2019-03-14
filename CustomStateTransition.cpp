#include "stdafx.h"
#include "CustomStateTransition.h"

CustomStateTransition::CustomStateTransition(CustomStateTransitionType type)
	: m_type(type)
{
}

bool CustomStateTransition::eventTest(QEvent *event)
{
	if (event->type() != QEvent::Type(QEvent::User + 1)) {
		return false;
	}
	CustomStateTransitionEvent *transition = static_cast<CustomStateTransitionEvent *>(event);
	return (m_type == transition->type);
}

void CustomStateTransition::onTransition(QEvent *)
{
}

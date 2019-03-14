#ifndef CustomFLATBUTTON_P_H
#define CustomFLATBUTTON_P_H

#include <QtGlobal>
#include <QColor>
#include "Customtheme.h"

class CustomFlatButton;
class CustomRippleOverlay;
class CustomFlatButtonStateMachine;

class CustomFlatButtonPrivate
{
	Q_DISABLE_COPY(CustomFlatButtonPrivate)
		Q_DECLARE_PUBLIC(CustomFlatButton)

public:
	CustomFlatButtonPrivate(CustomFlatButton *q);
	virtual ~CustomFlatButtonPrivate();

	void init();

	CustomFlatButton             *const q_ptr;
	CustomRippleOverlay          *rippleOverlay;
	CustomFlatButtonStateMachine *stateMachine;
	Material::Role                    role;
	Material::RippleStyle             rippleStyle;
	Material::ButtonIconPlacement     iconPlacement;
	Material::OverlayStyle            overlayStyle;
	Qt::BGMode                        bgMode;
	Qt::Alignment                     textAlignment;
	QColor                            backgroundColor;
	QColor                            foregroundColor;
	QColor                            overlayColor;
	QColor                            disabledColor;
	QColor                            disabledBackgroundColor;
	qreal                             fixedRippleRadius;
	qreal                             cornerRadius;
	qreal                             baseOpacity;
	qreal                             fontSize;
	bool                              useThemeColors;
	bool                              useFixedRippleRadius;
	bool                              haloVisible;
};

#endif // CustomFLATBUTTON_P_H

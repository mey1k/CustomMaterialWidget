#ifndef CustomFAB_P_H
#define CustomFAB_P_H

#include "Customraisedbutton_p.h"

class CustomFloatingActionButton;

class CustomFloatingActionButtonPrivate : public CustomRaisedButtonPrivate
{
	Q_DISABLE_COPY(CustomFloatingActionButtonPrivate)
		Q_DECLARE_PUBLIC(CustomFloatingActionButton)

public:
	enum {
		DefaultDiameter = 56,
		MiniDiameter = 40
	};

	enum {
		DefaultIconSize = 24,
		MiniIconSize = 18
	};

	CustomFloatingActionButtonPrivate(CustomFloatingActionButton *q);
	~CustomFloatingActionButtonPrivate();

	void init();
	QRect fabGeometry() const;
	void setupProperties();

	inline int diameter() const;
	inline int iconSize() const;

	Qt::Corner corner;
	bool       mini;
	int        offsX;
	int        offsY;
};

inline int CustomFloatingActionButtonPrivate::diameter() const
{
	return mini ? MiniDiameter : DefaultDiameter;
}

inline int CustomFloatingActionButtonPrivate::iconSize() const
{
	return mini ? MiniIconSize : DefaultIconSize;
}

#endif // CustomFAB_P_H

#ifndef CustomBADGE_P_H
#define CustomBADGE_P_H

#include <QtGlobal>
#include <QSize>
#include <QIcon>
#include <QColor>

class CustomBadge;

class CustomBadgePrivate
{
	Q_DISABLE_COPY(CustomBadgePrivate)
		Q_DECLARE_PUBLIC(CustomBadge)

public:
	CustomBadgePrivate(CustomBadge *q);
	~CustomBadgePrivate();

	void init();

	CustomBadge *const q_ptr;
	QString                text;
	QColor                 textColor;
	QColor                 backgroundColor;
	QSize                  size;
	QIcon                  icon;
	qreal                  x;
	qreal                  y;
	int                    padding;
	bool                   useThemeColors;
};

#endif // CustomBADGE_P_H

#ifndef CustomTHEME_P_H
#define CustomTHEME_P_H

#include <QHash>
#include <QColor>

class CustomTheme;

class CustomThemePrivate
{
	Q_DISABLE_COPY(CustomThemePrivate)
		Q_DECLARE_PUBLIC(CustomTheme)

public:
	CustomThemePrivate(CustomTheme *q);
	~CustomThemePrivate();

	QColor rgba(int r, int g, int b, qreal a) const;

	CustomTheme *const q_ptr;
	QHash<QString, QColor> colors;
};

#endif // CustomTHEME_P_H

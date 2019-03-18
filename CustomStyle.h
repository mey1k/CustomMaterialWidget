#ifndef CustomSTYLE_H
#define CustomSTYLE_H

#include <QtWidgets/QCommonStyle>
#include "CustomStyle_p.h"

#define MATERIAL_DISABLE_THEME_COLORS \
    if (d->useThemeColors == true) { d->useThemeColors = false; }

class CustomTheme;

class CustomStyle : public QCommonStyle
{
	Q_OBJECT

public:
	inline static CustomStyle &instance();

	void setTheme(CustomTheme *theme);
	QColor themeColor(const QString &key) const;

protected:
	const QScopedPointer<CustomStylePrivate> d_ptr;

private:
	Q_DECLARE_PRIVATE(CustomStyle)

		CustomStyle();

	CustomStyle(CustomStyle const &);
	void operator=(CustomStyle const &);
};

inline CustomStyle &CustomStyle::instance()
{
	static CustomStyle instance;
	return instance;
}

#endif // CustomSTYLE_H

#ifndef CustomTABS_H
#define CustomTABS_H

#include <QtWidgets/QWidget>
#include <QIcon>
#include "Customtheme.h"

class CustomTabsPrivate;
class CustomTab;

class CustomTabs : public QWidget
{
	Q_OBJECT

public:
	explicit CustomTabs(QWidget *parent = 0);
	~CustomTabs();

	void setUseThemeColors(bool value);
	bool useThemeColors() const;

	void setHaloVisible(bool value);
	bool isHaloVisible() const;

	void setRippleStyle(Material::RippleStyle style);
	Material::RippleStyle rippleStyle() const;

	void setInkColor(const QColor &color);
	QColor inkColor() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

	void setTextColor(const QColor &color);
	QColor textColor() const;

	void addTab(const QString &text, const QIcon &icon = QIcon());

	void setCurrentTab(CustomTab *tab);
	void setCurrentTab(int index);

	int currentIndex() const;

signals:
	void currentChanged(int);

protected:
	void setTabActive(int index, bool active = true);
	void updateTabs();

	const QScopedPointer<CustomTabsPrivate> d_ptr;

private:
	Q_DISABLE_COPY(CustomTabs)
		Q_DECLARE_PRIVATE(CustomTabs)
};

#endif // CustomTABS_H

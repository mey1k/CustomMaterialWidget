#pragma once


class Theme
{
public:

	enum ThemeType {
		whiteRed = 0,
		blackBlue
	};

	void setPointer(Theme *thisPointer);

	ThemeType themeType = ThemeType::whiteRed;

	Theme *singletonTheme;
};

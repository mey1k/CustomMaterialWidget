#pragma once
class Theme
{

public:
	void setPointer(Theme *thisPointer);

	ThemeType themeType = ThemeType::whiteRed;

	Theme *singletonTheme;
};

enum ThemeType {
	whiteRed = 0,
	blackBlue
};
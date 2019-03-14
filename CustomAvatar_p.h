#ifndef CustomAVATAR_P_H
#define CustomAVATAR_P_H

#include <QtGlobal>
#include <QChar>
#include <QImage>
#include <QIcon>
#include <QPixmap>
#include <QColor>
#include "Customtheme.h"

class CustomAvatar;

class CustomAvatarPrivate
{
	Q_DISABLE_COPY(CustomAvatarPrivate)
		Q_DECLARE_PUBLIC(CustomAvatar)

public:
	CustomAvatarPrivate(CustomAvatar *q);
	~CustomAvatarPrivate();

	void init();

	CustomAvatar *const q_ptr;
	int                     size;
	Material::AvatarType    type;
	QChar                   letter;
	QImage                  image;
	QIcon                   icon;
	QPixmap                 pixmap;
	bool                    useThemeColors;
	QColor                  textColor;
	QColor                  backgroundColor;
};

#endif // CustomAVATAR_P_H

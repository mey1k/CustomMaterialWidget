#include "stdafx.h"
#include "CustomToothLabel.h"

#include <QPainter>
#include <qfont.h>

#include <SurgicalGuide.h>

CustomToothLabel::CustomToothLabel(QWidget* parent) : QLabel(parent)
{
	for (int i = 0; i < 32; i++)
	{
		selectedTooth[i] = false;
	}
}

CustomToothLabel::~CustomToothLabel()
{
}

void CustomToothLabel::setSelectedTooth(QVector<int> teeth)
{
	QVector<int> copyTeeth = teeth;

	for (int i = 0; i < copyTeeth.count(); i++)
	{
		int selectTooth = copyTeeth.at(i);

		if (10 < selectTooth < 19)
		{
			selectTooth = 7 - (selectTooth - 11);
		}
		else if (20 < selectTooth < 29)
		{
			selectTooth = selectTooth - 13;
		}
		else if (30 < selectTooth < 39)
		{
			selectTooth = 39 - (selectTooth - 15);

		}
		else if (40 < selectTooth < 49)
		{
			selectTooth = selectTooth - 17;
		}

		selectedTooth[selectTooth] = true;
	}
}

void CustomToothLabel::printMark()
{
	int downNearCnt = 0;

	QPainter painterDownMark(this);
	QPixmap pixmapDownMark(":/Tooth/res/img/whiteRed/red-mark-down.png");

	QPainter painterUpMark(this);
	QPixmap pixmapUpMark(":/Tooth/res/img/whiteRed/red-mark-up.png");

	for (int i = 0; i < 32; i++)
	{
		if (i < 16)
		{
			if (selectedTooth[i])
			{
				for (int j = i + 1; j < 16; j++)
				{
					if (selectedTooth[j])
					{
						i = j;
						downNearCnt++;
					}
					else
					{
						if (downNearCnt > 1)
						{
							//custom
							painterDownMark.drawPixmap(width() / (18 - i), height() / 15, pixmapDownMark.width(), pixmapDownMark.height(), pixmapDownMark);
							downNearCnt = 0;
						}
						else
						{
							//fixed
							pixmapDownMark = QPixmap(":/Tooth/res/img/whiteRed/red-mark-up.png");
							painterDownMark.drawPixmap(width() / (18 - i), height() / 15, pixmapDownMark.width(), pixmapDownMark.height(), pixmapDownMark);
						}

						break;
					}
				}

			}
		}
		/*else
		{
			if (selectedTooth[i])
			{
				drawPix(mark - up)

					for (int j = i + 1; j<16; j++)
					{
						if (j == i + 1)
						{
							if (selected[j])
								drawPix((move)mark - up)
							else
								break;
						}
					}

			}
		}*/
	}
}

void CustomToothLabel::paintEvent(QPaintEvent* e)
{
	double correctScaleW = screenWidth / 2560.0;
	double correctScaleH = screenHeight / 1400.0;

	QLabel::paintEvent(e);

	QPainter painter(this);

	//drawText
	QFont font(QFont("Roboto", 12, QFont::Normal));
	painter.setFont(font);

	QPen pen(QColor(159, 34, 65));

	if (mainParent != nullptr)
	{
		if (mainParent->themeType == Theme::whiteRed) 
			pen = QPen(QColor(159, 34, 65));
		else
			pen = QPen(QColor(42, 125, 225));
	}

	painter.setPen(pen);

	QString strSelectedTooth = "Tooth ";

	for (int i = 0; i < 32; i++)
	{
		if (selectedTooth[i])
		{
			if (-1 < i && i < 8)
				strSelectedTooth += QString::number(18 - (i));
			else if (7 < i && i < 16)
				strSelectedTooth += QString::number(13 + (i));
			else if (15 < i && i < 24)
				strSelectedTooth += QString::number(54 - (i));
			else if (23 < i && i < 32)
				strSelectedTooth += QString::number(17 + (i));

			for (int j = i + 1; j < 32; j++)
			{
				if (selectedTooth[j])
				{
					strSelectedTooth += ", ";
					break;
				}
			}
		}
	}


	painter.drawText(QPoint(width() / 18, this->geometry().y() - 65 * correctScaleH), strSelectedTooth);

	QPainter toothBackground(this);
	QPixmap pixmapBg(":/Tooth/res/img/whiteRed/tooth_bright_bg.png");

	if (mainParent != nullptr)
	{
		if (mainParent->themeType == Theme::whiteRed)
			pixmapBg = QPixmap(":/Tooth/res/img/whiteRed/tooth_bright_bg.png");
		else
			pixmapBg = QPixmap(":/Tooth/res/img/blueBlack/tooth_bg.png");
	}

	toothBackground.drawPixmap(0, 0, width(), height(), pixmapBg);

	for (int i = 0; i < 16; i++)
	{
		if (selectedTooth[i])
		{
			QPainter painter(this);

			QString toothUpPath = ":/Tooth/res/img/whiteRed/tooth_bright_up_" + QString::number(i + 1) + ".png";

			if (mainParent != nullptr)
			{
				if (mainParent->themeType == Theme::whiteRed)
					toothUpPath = ":/Tooth/res/img/whiteRed/tooth_bright_up_" + QString::number(i + 1) + ".png";
				else
					toothUpPath = ":/Tooth/res/img/blueBlack/tooth_up_" + QString::number(i + 1) + ".png";
			}

			QPixmap pixmap(toothUpPath);

			painter.drawPixmap(0, 0, width(), height(), pixmap);

		}
	}

	for (int i = 0; i < 16; i++)
	{
		if (selectedTooth[i + 16])
		{
			QPainter painter(this);

			QString toothDownPath = ":/Tooth/res/img/whiteRed/tooth_bright_down_" + QString::number(i + 1) + ".png";

			if (mainParent != nullptr)
			{
				if (mainParent->themeType == Theme::whiteRed)
					toothDownPath = ":/Tooth/res/img/whiteRed/tooth_bright_down_" + QString::number(i + 1) + ".png";
				else
					toothDownPath = ":/Tooth/res/img/blueBlack/tooth_down_" + QString::number(i + 1) + ".png";
			}

			QPixmap pixmap(toothDownPath);

			painter.drawPixmap(0, 0, width(), height(), pixmap);
		}
	}
}

#ifndef CALENDARMANAGER_H
#define CALENDARMANAGER_H

#include <QCalendarWidget>

#include <QStringList>
#include <QBrush>
#include <QColor>
#include <QFile>
#include <QList>
#include <QDate>
#include <QPen>

class CustomCalendar : public QCalendarWidget
{
	Q_OBJECT

		Q_PROPERTY(QColor color READ getColor WRITE setColor)

public:
	CustomCalendar(QWidget *parent = 0);
	~CustomCalendar();

	void setColor(const QColor &color);
	QColor getColor() const;

protected:
	virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

private:
	struct calendarEvent
	{
		QDate date;
		QString name;
	};

	QList<calendarEvent> m_events;
	QList<QDate> m_dates;

	QPen m_outlinePen;
	QBrush m_transparentBrush;

	void getDates();
};

#endif // CALENDARMANAGER_H
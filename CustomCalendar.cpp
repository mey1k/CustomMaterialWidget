#include <QPainter>

#include "CustomCalendar.h"

CustomCalendar::CustomCalendar(QWidget *parent, Theme *singletonTheme)
    : QCalendarWidget(parent)
{
    m_outlinePen.setColor(Qt::red);
    m_transparentBrush.setColor(Qt::transparent);

    getDates();

	theme = singletonTheme;
}

CustomCalendar::~CustomCalendar()
{

}

void CustomCalendar::setColor(const QColor &color)
{
    m_outlinePen.setColor(color);
}

QColor CustomCalendar::getColor() const
{
    return (m_outlinePen.color());
}

void CustomCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    /*CustomCalendar::paintCell(painter, rect, date);

    if (m_dates.contains(date)) {

        QPixmap pixmap(":/ThemeWhiteRed/res/svg/whiteRed/7_calendar_schedule_check_icon.svg");
        QPainter icon(&pixmap);

        QPoint top(width() / 3, height() / 10);
        QPoint bottom((width() / 3) * 2, (height() / 10) * 3);

        QRect iconGeometry(top, bottom);

        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), painter->pen().color());
        painter->drawPixmap(iconGeometry, pixmap);

        painter->setPen(m_outlinePen);
        painter->setBrush(m_transparentBrush);
        painter->drawRect(rect.adjusted(0, 0, -1, -1));
    }
    else
    {
    }*/

    if (m_dates.contains(date)) {
        painter->save();

        QPixmap pixmap;

        if (theme->themeType == ThemeType::whiteRed)
            pixmap = QPixmap(":/ThemeWhiteRed/res/svg/whiteRed/calendar_schedule_check_icon.svg");
        else
            pixmap = QPixmap(":/ThemeBlackBlue/res/svg/blueBlack/calendar_schedule_check_icon.svg");

        QPainter icon(&pixmap);

        QPoint top(rect.topLeft().x() + (rect.width() / 2) - 5, rect.topLeft().y() + rect.height() / 10);
        QPoint bottom(rect.topLeft().x() + (rect.width() / 2) + 5, rect.topLeft().y() + (rect.height() / 10) * 3);

        QRect iconGeometry(top, bottom);

        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        //icon.fillRect(pixmap.rect(), qRgb(159, 34, 65));
        painter->drawPixmap(iconGeometry, pixmap);

        if (this->selectedDate() == date)
        {
            QBrush brush;

            if (theme->themeType == ThemeType::whiteRed)
                brush = QBrush(QColor(159, 34, 65), Qt::SolidPattern);
            else
                brush = QBrush(QColor(42, 125, 225), Qt::SolidPattern);

            painter->setBrush(brush);
            painter->drawRect(rect);
            QPen whitePen(QColor("#ffffff"));
            painter->setPen(whitePen);
        }
        painter->drawText(rect, Qt::AlignCenter | Qt::TextSingleLine, QString::number(date.day()));


        painter->restore();
    }
    else
        QCalendarWidget::paintCell(painter, rect, date);
}

void CustomCalendar::getDates()
{
    //QFile file("/data/events.csv");
    //if (!file.open(QIODevice::ReadOnly)) {
    //	//Error code
    //}

    //QList<QByteArray> wordList;

    QDate date;
    QString name;
    calendarEvent e;

    /*while (!file.atEnd()) {
        QByteArray line = file.readLine();
        wordList = line.split(',');*/

        //date = QDate::fromString(wordList.first(), "dd/MM/yyyy");
    date = QDate::currentDate();
    name = "???? ????";

        e.date = date;
        e.name = name;

        m_events.append(e);
        m_dates.append(date);
    //}

    //file.close();
}

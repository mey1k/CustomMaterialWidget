#ifndef DIALOGSETTINGSEDITOR_H
#define DIALOGSETTINGSEDITOR_H

#include <QWidget>
#include <qlabel.h>
#include "qeventloop.h"

class CustomDialog;

class CustomDialogSetting : public QWidget
{
	Q_OBJECT

public:
	explicit CustomDialogSetting(QWidget *parent = 0);
	~CustomDialogSetting();
	void setupCautionForm(QString message, QString btnText, int width, int height, int type);
	void showCautionForm();
	void setTextMessage(QString);
	bool isSelection = false;
private slots:
	void setupForm();
	void updateWidget();
	void exitCautionForm();
	void setAcceptedFlag();
	void setRejectedFlag();

private:
	CustomDialog * m_CautionDialog;
	QLabel *lblCautionMessage;
	QEventLoop loop;

signals:
	void closed();
};

#endif // DIALOGSETTINGSEDITOR_H

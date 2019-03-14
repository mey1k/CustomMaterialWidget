#include "stdafx.h"
#include "CustomDialogSetting.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include "Customdialog.h"
#include "Customflatbutton.h"
#include "qeventloop.h"
#include <QDialogButtonBox>

CustomDialogSetting::CustomDialogSetting(QWidget *parent) : QWidget(parent)
{
	m_CautionDialog = new CustomDialog(parent);
}


CustomDialogSetting::~CustomDialogSetting()
{
}

void CustomDialogSetting::setupCautionForm(QString message, QString btnText, int width, int height, int type)
{

	double correctScaleW = width / 2560.0;
	double correctScaleH = height / 1400.0;

	QVBoxLayout *dialogLayout = new QVBoxLayout;
	m_CautionDialog->setWindowLayout(dialogLayout);

	if (type == 1)
	{
		QPushButton *closeButton = new QPushButton(btnText);
		closeButton->setFixedWidth(150 * correctScaleW);
		closeButton->setFixedHeight(50 * correctScaleH);

		if (correctScaleW < 0.8) correctScaleW -= 0.05;

		QString radiusRate = QString::number(25 * correctScaleW);

		QString buttonStyle = "QPushButton{"
			"color: rgb(136, 137, 141);"
			"background-color: rgba(217, 217, 217);"
			"border-style: outset;"
			"border-width: 5px;"
			"border-radius: " + radiusRate + "px;"
			"border-color: white;"
			"padding: 6px;"
			"}"

			"QPushButton:hover:pressed{"
			"color: white;"
			"background-color: rgb(159,34,65);"
			"border-width: 5px;"
			"border-radius: " + radiusRate + "px;"
			"border-color: white;"
			"}"

			"QPushButton:hover{"
			"color: white;"
			"background-color: rgb(177, 177, 177);"
			"border-width: 5px;"
			"border-radius: " + radiusRate + "px;"
			"border-color: white;"
			"}";

		closeButton->setStyleSheet(buttonStyle);

		lblCautionMessage = new QLabel();
		lblCautionMessage->setText(message);
		lblCautionMessage->setAlignment(Qt::AlignCenter);

		dialogLayout->addWidget(lblCautionMessage);
		dialogLayout->addWidget(closeButton);
		dialogLayout->setAlignment(lblCautionMessage, Qt::AlignCenter);
		dialogLayout->setAlignment(closeButton, Qt::AlignCenter);
		dialogLayout->setContentsMargins(0, 50 * correctScaleH, 0, 30 * correctScaleH);
		dialogLayout->setSpacing(15);

		lblCautionMessage->setStyleSheet("QLabel {font : bold 20px;}");

		connect(closeButton, SIGNAL(pressed()), m_CautionDialog, SLOT(hideDialog()));
		connect(closeButton, SIGNAL(pressed()), this, SLOT(exitCautionForm()));
	}
	else
	{
		QDialogButtonBox *closeButton = new QDialogButtonBox(QDialogButtonBox::Ok
			| QDialogButtonBox::Cancel);
		/*closeButton->setFixedWidth(150 * correctScaleW);
		closeButton->setFixedHeight(50 * correctScaleH);*/

		closeButton->button(QDialogButtonBox::Ok)->setText(
			QString::fromLocal8Bit("확인"));
		closeButton->button(QDialogButtonBox::Cancel)->setText(
			QString::fromLocal8Bit("취소"));

		closeButton->setCenterButtons(true);

		if (correctScaleW < 0.8) correctScaleW -= 0.05;

		QString radiusRate = QString::number(25 * correctScaleW);

		QString buttonStyle = "QPushButton{"
			"color: rgb(136, 137, 141);"
			"background-color: rgba(217, 217, 217);"
			"color: white;"
			"border-style: outset;"
			"border-width: 5px;"
			"border-radius: " + radiusRate + "px;"
			"border-color:white;"
			"min-width: 4em;"
			"padding: 10 10 10 10;"
			"margin: 0 14 0 7;"
			"}"

			"QPushButton:hover:pressed{"
			"color: white;"
			"background-color: rgb(159,34,65);"
			"border-width: 5px;"
			"border-radius: " + radiusRate + "px;"
			"border-color: white;"
			"}"

			"QPushButton:hover{"
			"color: white;"
			"background-color: rgb(177, 177, 177);"
			"border-width: 5px;"
			"border-radius: " + radiusRate + "px;"
			"border-color: white;"
			"}";

		closeButton->setStyleSheet(buttonStyle);

		lblCautionMessage = new QLabel();
		lblCautionMessage->setText(message);
		lblCautionMessage->setAlignment(Qt::AlignCenter);

		dialogLayout->addWidget(lblCautionMessage);
		dialogLayout->addWidget(closeButton);
		dialogLayout->setAlignment(lblCautionMessage, Qt::AlignCenter);
		dialogLayout->setAlignment(closeButton, Qt::AlignCenter);
		dialogLayout->setContentsMargins(0, 50 * correctScaleH, 0, 30 * correctScaleH);
		dialogLayout->setSpacing(15);

		lblCautionMessage->setStyleSheet("QLabel {font : bold 20px;}");

		connect(closeButton, SIGNAL(accepted()), m_CautionDialog, SLOT(hideDialog()));
		connect(closeButton, SIGNAL(accepted()), this, SLOT(exitCautionForm()));
		connect(closeButton, SIGNAL(accepted()), this, SLOT(setAcceptedFlag()));
		connect(closeButton, SIGNAL(rejected()), m_CautionDialog, SLOT(hideDialog()));
		connect(closeButton, SIGNAL(rejected()), this, SLOT(exitCautionForm()));
		connect(closeButton, SIGNAL(rejected()), this, SLOT(setRejectedFlag()));
	}
}

void CustomDialogSetting::setTextMessage(QString message)
{
	lblCautionMessage->setText(message);
}

void CustomDialogSetting::updateWidget()
{
}

void CustomDialogSetting::showCautionForm()
{
	m_CautionDialog->showDialog();
	loop.exec();
}

void CustomDialogSetting::setupForm()
{

}

void CustomDialogSetting::exitCautionForm()
{
	loop.exit();

	emit closed();
}

void CustomDialogSetting::setAcceptedFlag()
{
	isSelection = true;
}

void CustomDialogSetting::setRejectedFlag()
{
	isSelection = false;
}
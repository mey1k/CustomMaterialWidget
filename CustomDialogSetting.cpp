#include "CustomDialogSetting.h"਍⌀椀渀挀氀甀搀攀 㰀儀嘀䈀漀砀䰀愀礀漀甀琀㸀ഀ
#include <QColorDialog>਍⌀椀渀挀氀甀搀攀 ∀䌀甀猀琀漀洀搀椀愀氀漀最⸀栀∀ഀ
#include "Customflatbutton.h"਍⌀椀渀挀氀甀搀攀 ∀焀攀瘀攀渀琀氀漀漀瀀⸀栀∀ഀ
#include <QDialogButtonBox>਍ഀ
CustomDialogSetting::CustomDialogSetting(QWidget *parent) : QWidget(parent)਍笀ഀ
    m_CautionDialog = new CustomDialog(parent);਍紀ഀ
਍ഀ
CustomDialogSetting::~CustomDialogSetting()਍笀ഀ
}਍ഀ
void CustomDialogSetting::setupCautionForm(QString message, QString btnText, int width, int height, int type)਍笀ഀ
਍    搀漀甀戀氀攀 挀漀爀爀攀挀琀匀挀愀氀攀圀 㴀 眀椀搀琀栀 ⼀ ㈀㔀㘀　⸀　㬀ഀ
    double correctScaleH = height / 1400.0;਍ഀ
    QVBoxLayout *dialogLayout = new QVBoxLayout;਍    洀开䌀愀甀琀椀漀渀䐀椀愀氀漀最ⴀ㸀猀攀琀圀椀渀搀漀眀䰀愀礀漀甀琀⠀搀椀愀氀漀最䰀愀礀漀甀琀⤀㬀ഀ
਍    椀昀 ⠀琀礀瀀攀 㴀㴀 ㄀⤀ഀ
    {਍        儀倀甀猀栀䈀甀琀琀漀渀 ⨀挀氀漀猀攀䈀甀琀琀漀渀 㴀 渀攀眀 儀倀甀猀栀䈀甀琀琀漀渀⠀戀琀渀吀攀砀琀⤀㬀ഀ
        closeButton->setFixedWidth(150 * correctScaleW);਍        挀氀漀猀攀䈀甀琀琀漀渀ⴀ㸀猀攀琀䘀椀砀攀搀䠀攀椀最栀琀⠀㔀　 ⨀ 挀漀爀爀攀挀琀匀挀愀氀攀䠀⤀㬀ഀ
਍        椀昀 ⠀挀漀爀爀攀挀琀匀挀愀氀攀圀 㰀 　⸀㠀⤀ 挀漀爀爀攀挀琀匀挀愀氀攀圀 ⴀ㴀 　⸀　㔀㬀ഀ
਍        儀匀琀爀椀渀最 爀愀搀椀甀猀刀愀琀攀 㴀 儀匀琀爀椀渀最㨀㨀渀甀洀戀攀爀⠀㈀㔀 ⨀ 挀漀爀爀攀挀琀匀挀愀氀攀圀⤀㬀ഀ
਍        儀匀琀爀椀渀最 戀甀琀琀漀渀匀琀礀氀攀 㴀 ∀儀倀甀猀栀䈀甀琀琀漀渀笀∀ഀ
            "color: rgb(136, 137, 141);"਍            ∀戀愀挀欀最爀漀甀渀搀ⴀ挀漀氀漀爀㨀 爀最戀愀⠀㈀㄀㜀Ⰰ ㈀㄀㜀Ⰰ ㈀㄀㜀⤀㬀∀ഀ
            "border-style: outset;"਍            ∀戀漀爀搀攀爀ⴀ眀椀搀琀栀㨀 㔀瀀砀㬀∀ഀ
            "border-radius: " + radiusRate + "px;"਍            ∀戀漀爀搀攀爀ⴀ挀漀氀漀爀㨀 眀栀椀琀攀㬀∀ഀ
            "padding: 6px;"਍            ∀紀∀ഀ
਍            ∀儀倀甀猀栀䈀甀琀琀漀渀㨀栀漀瘀攀爀㨀瀀爀攀猀猀攀搀笀∀ഀ
            "color: white;"਍            ∀戀愀挀欀最爀漀甀渀搀ⴀ挀漀氀漀爀㨀 爀最戀⠀㄀㔀㤀Ⰰ㌀㐀Ⰰ㘀㔀⤀㬀∀ഀ
            "border-width: 5px;"਍            ∀戀漀爀搀攀爀ⴀ爀愀搀椀甀猀㨀 ∀ ⬀ 爀愀搀椀甀猀刀愀琀攀 ⬀ ∀瀀砀㬀∀ഀ
            "border-color: white;"਍            ∀紀∀ഀ
਍            ∀儀倀甀猀栀䈀甀琀琀漀渀㨀栀漀瘀攀爀笀∀ഀ
            "color: white;"਍            ∀戀愀挀欀最爀漀甀渀搀ⴀ挀漀氀漀爀㨀 爀最戀⠀㄀㜀㜀Ⰰ ㄀㜀㜀Ⰰ ㄀㜀㜀⤀㬀∀ഀ
            "border-width: 5px;"਍            ∀戀漀爀搀攀爀ⴀ爀愀搀椀甀猀㨀 ∀ ⬀ 爀愀搀椀甀猀刀愀琀攀 ⬀ ∀瀀砀㬀∀ഀ
            "border-color: white;"਍            ∀紀∀㬀ഀ
਍        挀氀漀猀攀䈀甀琀琀漀渀ⴀ㸀猀攀琀匀琀礀氀攀匀栀攀攀琀⠀戀甀琀琀漀渀匀琀礀氀攀⤀㬀ഀ
਍        氀戀氀䌀愀甀琀椀漀渀䴀攀猀猀愀最攀 㴀 渀攀眀 儀䰀愀戀攀氀⠀⤀㬀ഀ
        lblCautionMessage->setText(message);਍        氀戀氀䌀愀甀琀椀漀渀䴀攀猀猀愀最攀ⴀ㸀猀攀琀䄀氀椀最渀洀攀渀琀⠀儀琀㨀㨀䄀氀椀最渀䌀攀渀琀攀爀⤀㬀ഀ
਍        搀椀愀氀漀最䰀愀礀漀甀琀ⴀ㸀愀搀搀圀椀搀最攀琀⠀氀戀氀䌀愀甀琀椀漀渀䴀攀猀猀愀最攀⤀㬀ഀ
        dialogLayout->addWidget(closeButton);਍        搀椀愀氀漀最䰀愀礀漀甀琀ⴀ㸀猀攀琀䄀氀椀最渀洀攀渀琀⠀氀戀氀䌀愀甀琀椀漀渀䴀攀猀猀愀最攀Ⰰ 儀琀㨀㨀䄀氀椀最渀䌀攀渀琀攀爀⤀㬀ഀ
        dialogLayout->setAlignment(closeButton, Qt::AlignCenter);਍        搀椀愀氀漀最䰀愀礀漀甀琀ⴀ㸀猀攀琀䌀漀渀琀攀渀琀猀䴀愀爀最椀渀猀⠀　Ⰰ 㔀　 ⨀ 挀漀爀爀攀挀琀匀挀愀氀攀䠀Ⰰ 　Ⰰ ㌀　 ⨀ 挀漀爀爀攀挀琀匀挀愀氀攀䠀⤀㬀ഀ
        dialogLayout->setSpacing(15);਍ഀ
        lblCautionMessage->setStyleSheet("QLabel {font : bold 20px;}");਍ഀ
        connect(closeButton, SIGNAL(pressed()), m_CautionDialog, SLOT(hideDialog()));਍        挀漀渀渀攀挀琀⠀挀氀漀猀攀䈀甀琀琀漀渀Ⰰ 匀䤀䜀一䄀䰀⠀瀀爀攀猀猀攀搀⠀⤀⤀Ⰰ 琀栀椀猀Ⰰ 匀䰀伀吀⠀攀砀椀琀䌀愀甀琀椀漀渀䘀漀爀洀⠀⤀⤀⤀㬀ഀ
    }਍    攀氀猀攀ഀ
    {਍        儀䐀椀愀氀漀最䈀甀琀琀漀渀䈀漀砀 ⨀挀氀漀猀攀䈀甀琀琀漀渀 㴀 渀攀眀 儀䐀椀愀氀漀最䈀甀琀琀漀渀䈀漀砀⠀儀䐀椀愀氀漀最䈀甀琀琀漀渀䈀漀砀㨀㨀伀欀ഀ
            | QDialogButtonBox::Cancel);਍        ⼀⨀挀氀漀猀攀䈀甀琀琀漀渀ⴀ㸀猀攀琀䘀椀砀攀搀圀椀搀琀栀⠀㄀㔀　 ⨀ 挀漀爀爀攀挀琀匀挀愀氀攀圀⤀㬀ഀ
        closeButton->setFixedHeight(50 * correctScaleH);*/਍ഀ
        closeButton->button(QDialogButtonBox::Ok)->setText(਍            儀匀琀爀椀渀最㨀㨀昀爀漀洀䰀漀挀愀氀㠀䈀椀琀⠀∀⸀ﴂ﷿⋿⤀⤀㬀ഀ
        closeButton->button(QDialogButtonBox::Cancel)->setText(਍            儀匀琀爀椀渀最㨀㨀昀爀漀洀䰀漀挀愀氀㠀䈀椀琀⠀∀ﴀ﷿﷿﷿⋿⤀⤀㬀ഀ
਍        挀氀漀猀攀䈀甀琀琀漀渀ⴀ㸀猀攀琀䌀攀渀琀攀爀䈀甀琀琀漀渀猀⠀琀爀甀攀⤀㬀ഀ
਍        椀昀 ⠀挀漀爀爀攀挀琀匀挀愀氀攀圀 㰀 　⸀㠀⤀ 挀漀爀爀攀挀琀匀挀愀氀攀圀 ⴀ㴀 　⸀　㔀㬀ഀ
਍        儀匀琀爀椀渀最 爀愀搀椀甀猀刀愀琀攀 㴀 儀匀琀爀椀渀最㨀㨀渀甀洀戀攀爀⠀㈀㔀 ⨀ 挀漀爀爀攀挀琀匀挀愀氀攀圀⤀㬀ഀ
਍        儀匀琀爀椀渀最 戀甀琀琀漀渀匀琀礀氀攀 㴀 ∀儀倀甀猀栀䈀甀琀琀漀渀笀∀ഀ
            "color: rgb(136, 137, 141);"਍            ∀戀愀挀欀最爀漀甀渀搀ⴀ挀漀氀漀爀㨀 爀最戀愀⠀㈀㄀㜀Ⰰ ㈀㄀㜀Ⰰ ㈀㄀㜀⤀㬀∀ഀ
            "color: white;"਍            ∀戀漀爀搀攀爀ⴀ猀琀礀氀攀㨀 漀甀琀猀攀琀㬀∀ഀ
            "border-width: 5px;"਍            ∀戀漀爀搀攀爀ⴀ爀愀搀椀甀猀㨀 ∀ ⬀ 爀愀搀椀甀猀刀愀琀攀 ⬀ ∀瀀砀㬀∀ഀ
            "border-color:white;"਍            ∀洀椀渀ⴀ眀椀搀琀栀㨀 㐀攀洀㬀∀ഀ
            "padding: 10 10 10 10;"਍            ∀洀愀爀最椀渀㨀 　 ㄀㐀 　 㜀㬀∀ഀ
            "}"਍ഀ
            "QPushButton:hover:pressed{"਍            ∀挀漀氀漀爀㨀 眀栀椀琀攀㬀∀ഀ
            "background-color: rgb(159,34,65);"਍            ∀戀漀爀搀攀爀ⴀ眀椀搀琀栀㨀 㔀瀀砀㬀∀ഀ
            "border-radius: " + radiusRate + "px;"਍            ∀戀漀爀搀攀爀ⴀ挀漀氀漀爀㨀 眀栀椀琀攀㬀∀ഀ
            "}"਍ഀ
            "QPushButton:hover{"਍            ∀挀漀氀漀爀㨀 眀栀椀琀攀㬀∀ഀ
            "background-color: rgb(177, 177, 177);"਍            ∀戀漀爀搀攀爀ⴀ眀椀搀琀栀㨀 㔀瀀砀㬀∀ഀ
            "border-radius: " + radiusRate + "px;"਍            ∀戀漀爀搀攀爀ⴀ挀漀氀漀爀㨀 眀栀椀琀攀㬀∀ഀ
            "}";਍ഀ
        closeButton->setStyleSheet(buttonStyle);਍ഀ
        lblCautionMessage = new QLabel();਍        氀戀氀䌀愀甀琀椀漀渀䴀攀猀猀愀最攀ⴀ㸀猀攀琀吀攀砀琀⠀洀攀猀猀愀最攀⤀㬀ഀ
        lblCautionMessage->setAlignment(Qt::AlignCenter);਍ഀ
        dialogLayout->addWidget(lblCautionMessage);਍        搀椀愀氀漀最䰀愀礀漀甀琀ⴀ㸀愀搀搀圀椀搀最攀琀⠀挀氀漀猀攀䈀甀琀琀漀渀⤀㬀ഀ
        dialogLayout->setAlignment(lblCautionMessage, Qt::AlignCenter);਍        搀椀愀氀漀最䰀愀礀漀甀琀ⴀ㸀猀攀琀䄀氀椀最渀洀攀渀琀⠀挀氀漀猀攀䈀甀琀琀漀渀Ⰰ 儀琀㨀㨀䄀氀椀最渀䌀攀渀琀攀爀⤀㬀ഀ
        dialogLayout->setContentsMargins(0, 50 * correctScaleH, 0, 30 * correctScaleH);਍        搀椀愀氀漀最䰀愀礀漀甀琀ⴀ㸀猀攀琀匀瀀愀挀椀渀最⠀㄀㔀⤀㬀ഀ
਍        氀戀氀䌀愀甀琀椀漀渀䴀攀猀猀愀最攀ⴀ㸀猀攀琀匀琀礀氀攀匀栀攀攀琀⠀∀儀䰀愀戀攀氀 笀昀漀渀琀 㨀 戀漀氀搀 ㈀　瀀砀㬀紀∀⤀㬀ഀ
਍        挀漀渀渀攀挀琀⠀挀氀漀猀攀䈀甀琀琀漀渀Ⰰ 匀䤀䜀一䄀䰀⠀愀挀挀攀瀀琀攀搀⠀⤀⤀Ⰰ 洀开䌀愀甀琀椀漀渀䐀椀愀氀漀最Ⰰ 匀䰀伀吀⠀栀椀搀攀䐀椀愀氀漀最⠀⤀⤀⤀㬀ഀ
        connect(closeButton, SIGNAL(accepted()), this, SLOT(exitCautionForm()));਍        挀漀渀渀攀挀琀⠀挀氀漀猀攀䈀甀琀琀漀渀Ⰰ 匀䤀䜀一䄀䰀⠀愀挀挀攀瀀琀攀搀⠀⤀⤀Ⰰ 琀栀椀猀Ⰰ 匀䰀伀吀⠀猀攀琀䄀挀挀攀瀀琀攀搀䘀氀愀最⠀⤀⤀⤀㬀ഀ
        connect(closeButton, SIGNAL(rejected()), m_CautionDialog, SLOT(hideDialog()));਍        挀漀渀渀攀挀琀⠀挀氀漀猀攀䈀甀琀琀漀渀Ⰰ 匀䤀䜀一䄀䰀⠀爀攀樀攀挀琀攀搀⠀⤀⤀Ⰰ 琀栀椀猀Ⰰ 匀䰀伀吀⠀攀砀椀琀䌀愀甀琀椀漀渀䘀漀爀洀⠀⤀⤀⤀㬀ഀ
        connect(closeButton, SIGNAL(rejected()), this, SLOT(setRejectedFlag()));਍    紀ഀ
}਍ഀ
void CustomDialogSetting::setTextMessage(QString message)਍笀ഀ
    lblCautionMessage->setText(message);਍紀ഀ
਍瘀漀椀搀 䌀甀猀琀漀洀䐀椀愀氀漀最匀攀琀琀椀渀最㨀㨀甀瀀搀愀琀攀圀椀搀最攀琀⠀⤀ഀ
{਍紀ഀ
਍瘀漀椀搀 䌀甀猀琀漀洀䐀椀愀氀漀最匀攀琀琀椀渀最㨀㨀猀栀漀眀䌀愀甀琀椀漀渀䘀漀爀洀⠀⤀ഀ
{਍    洀开䌀愀甀琀椀漀渀䐀椀愀氀漀最ⴀ㸀猀栀漀眀䐀椀愀氀漀最⠀⤀㬀ഀ
    loop.exec();਍紀ഀ
਍瘀漀椀搀 䌀甀猀琀漀洀䐀椀愀氀漀最匀攀琀琀椀渀最㨀㨀猀攀琀甀瀀䘀漀爀洀⠀⤀ഀ
{਍ഀ
}਍ഀ
void CustomDialogSetting::exitCautionForm()਍笀ഀ
    loop.exit();਍ഀ
    emit closed();਍紀ഀ
਍瘀漀椀搀 䌀甀猀琀漀洀䐀椀愀氀漀最匀攀琀琀椀渀最㨀㨀猀攀琀䄀挀挀攀瀀琀攀搀䘀氀愀最⠀⤀ഀ
{਍    椀猀匀攀氀攀挀琀椀漀渀 㴀 琀爀甀攀㬀ഀ
}਍ഀ
void CustomDialogSetting::setRejectedFlag()਍笀ഀ
    isSelection = false;਍紀ഀ

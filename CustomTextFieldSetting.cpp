#include "CustomTextFieldSettig.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include "Customtextfield.h"

TextFieldSettingsEditor::TextFieldSettingsEditor(QWidget *parent) : QWidget(parent)
{
	m_textField = new CustomTextField(parent);
}

TextFieldSettingsEditor::~TextFieldSettingsEditor()
{
	delete m_textField;
}

void TextFieldSettingsEditor::initTextField(int width, int height, int sx, int sy, QString textHolder, QString textLine, QString labelText)
{
	double correctScaleW = width / 2560.0;
	double correctScaleH = height / 1400.0;

	m_textField->move(sx, sy);
	m_textField->setFixedWidth(width * correctScaleW);
	m_textField->setFixedHeight(height * correctScaleH);

	m_textField->setText(textLine);
	m_textField->setLabel(labelText);
	m_textField->setPlaceholderText(textHolder);

	m_textField->setDisabled(false);
	m_textField->setShowLabel(true);
	m_textField->setUseThemeColors(true);
	m_textField->setShowInputLine(true);
}

void TextFieldSettingsEditor::setDisable(bool value)
{
	m_textField->setDisabled(value);
}

void TextFieldSettingsEditor::setShowInputLine(bool value)
{
	m_textField->setShowInputLine(value);
}

void TextFieldSettingsEditor::setShowLabel(bool value)
{
	m_textField->setShowLabel(value);
}

void TextFieldSettingsEditor::setTextColor(QColor color)
{
	m_textField->setTextColor(color);
}

void TextFieldSettingsEditor::setInkColor(QColor color)
{
	m_textField->setInkColor(color);
}

void TextFieldSettingsEditor::setInputLineColor(QColor color)
{
	m_textField->setInputLineColor(color);
}

void TextFieldSettingsEditor::setLabelColor(QColor color)
{
	m_textField->setLabelColor(color);
}

void TextFieldSettingsEditor::selectColor()
{
	QColorDialog dialog;
	if (dialog.exec()) {
		QColor color = dialog.selectedColor();
		QString senderName = sender()->objectName();
		if ("textColorToolButton" == senderName) {
			m_textField->setTextColor(color);
		}
		else if ("inkColorToolButton" == senderName) {
			m_textField->setInkColor(color);
		}
		else if ("inputLineColorToolButton" == senderName) {
			m_textField->setInputLineColor(color);
		}
		else if ("labelColorToolButton" == senderName) {
			m_textField->setLabelColor(color);
		}
	}
	setupForm();
}

void TextFieldSettingsEditor::updateWidget()
{
}

void TextFieldSettingsEditor::setupForm()
{
}

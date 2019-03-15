#ifndef TEXTFIELDSETTINGSEDITOR_H
#define TEXTFIELDSETTINGSEDITOR_H

#include <QWidget>

class CustomTextField;

class TextFieldSettingsEditor : public QWidget
{
	Q_OBJECT

public:
	explicit TextFieldSettingsEditor(QWidget *parent = 0);
	~TextFieldSettingsEditor();
	void initTextField(int width, int height, int sx, int sy, QString textHolder, QString textLine, QString labelText);
	void setTextColor(QColor color);
	void setInkColor(QColor color);
	void setInputLineColor(QColor color);
	void setLabelColor(QColor color);
	void setShowInputLine(bool value);
	void setShowLabel(bool value);
	void setDisable(bool value);

protected slots:
	void setupForm();
	void updateWidget();
	void selectColor();

private:
	CustomTextField       *m_textField;
};

#endif // TEXTFIELDSETTINGSEDITOR_H

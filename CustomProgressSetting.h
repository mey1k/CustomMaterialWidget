#ifndef PROGRESSSETTINGSEDITOR_H
#define PROGRESSSETTINGSEDITOR_H

#include <QWidget>

class CustomProgress;

class ProgressSettingsEditor : public QWidget
{
	Q_OBJECT

public:
	explicit ProgressSettingsEditor(QWidget *parent = 0);
	~ProgressSettingsEditor();

	void initProgress(int width, int height);
	void setMode(int mode);
	void setValue(int value);
	void setDisable(bool value);
	void setColor(QColor color);

protected slots:
	void setupForm();
	void updateWidget();
	void selectColor();

private:
	CustomProgress       *m_progress;
};

#endif // PROGRESSSETTINGSEDITOR_H

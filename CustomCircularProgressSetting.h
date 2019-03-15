#ifndef CIRCULARPROGRESSSETTINGSEDITOR_H
#define CIRCULARPROGRESSSETTINGSEDITOR_H

#include <QWidget>

class CustomCircularProgress;

class CircularProgressSettingsEditor : public QWidget
{
	Q_OBJECT

public:
	explicit CircularProgressSettingsEditor(QWidget *parent = 0);
	~CircularProgressSettingsEditor();

	void initProgress(int width, int height);
	void setMode(int mode);
	void setColor(QColor color);
	void setDisable(bool value);
	void setValue(int value);

protected slots:
	void setupForm();
	void updateWidget();
	void selectColor();

private:
	CustomCircularProgress    *m_progress;
	
};

#endif // CIRCULARPROGRESSSETTINGSEDITOR_H

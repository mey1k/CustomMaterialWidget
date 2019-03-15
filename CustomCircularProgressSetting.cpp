#include "CustomCircularProgressSetting.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include "CustomCircularProgress.h"

CircularProgressSettingsEditor::CircularProgressSettingsEditor(QWidget *parent) : QWidget(parent)
{
	m_progress = new CustomCircularProgress(parent);
}

CircularProgressSettingsEditor::~CircularProgressSettingsEditor()
{
}

void CircularProgressSettingsEditor::setupForm()
{
}

void CircularProgressSettingsEditor::updateWidget()
{
}

void CircularProgressSettingsEditor::initProgress(int width, int height)
{
	double correctScaleW = width / 2560.0;
	double correctScaleH = height / 1400.0;

	m_progress->setProgressType(Material::IndeterminateProgress);
	m_progress->setDisabled(false);
	m_progress->setValue(0);
	m_progress->setLineWidth(5 * correctScaleW);
	m_progress->setSize(100 * correctScaleW);
	m_progress->setUseThemeColors(true);

	m_progress->move(width - (600 * correctScaleW), height - (180 * correctScaleH));
	m_progress->setFixedSize(200 * correctScaleW, 200 * correctScaleH);
}

void CircularProgressSettingsEditor::setColor(QColor color)
{
	m_progress->setColor(color);
}

void CircularProgressSettingsEditor::setDisable(bool value)
{
	m_progress->setDisabled(value);
}

void CircularProgressSettingsEditor::setValue(int value)
{
	m_progress->setValue(value);
}

void CircularProgressSettingsEditor::setMode(int mode)
{
	if(mode == 0)
		m_progress->setProgressType(Material::IndeterminateProgress);
	else
		m_progress->setProgressType(Material::DeterminateProgress);
}

void CircularProgressSettingsEditor::selectColor()
{
	QColorDialog dialog;
	if (dialog.exec()) {
		QColor color = dialog.selectedColor();
		QString senderName = sender()->objectName();
		if ("colorToolButton" == senderName) {
			m_progress->setColor(color);
		}
	}
	setupForm();
}

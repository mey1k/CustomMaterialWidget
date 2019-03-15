#include "CustomProgressSetting.h"
#include <QColorDialog>
#include "Customprogress.h"
#include "Customtheme.h"

ProgressSettingsEditor::ProgressSettingsEditor(QWidget *parent) : QWidget(parent)
{
	m_progress = new CustomProgress(parent);
}

ProgressSettingsEditor::~ProgressSettingsEditor()
{
}

void ProgressSettingsEditor::initProgress(int width, int height)
{
	double correctScaleW = width / 2560.0;
	double correctScaleH = height / 1400.0;

	m_progress->setProgressType(Material::DeterminateProgress);

	m_progress->setDisabled(false);
	m_progress->setValue(0);
	m_progress->setUseThemeColors(true);

	m_progress->move(width - (250 * correctScaleW), height - (200 * correctScaleH));
	m_progress->setFixedWidth(200 * correctScaleW);
}

void ProgressSettingsEditor::setValue(int value)
{
	m_progress->setValue(value);
}

void ProgressSettingsEditor::setColor(QColor color)
{
	m_progress->setProgressColor(color);
}

void ProgressSettingsEditor::setMode(int mode)
{
	if (mode == 0)
		m_progress->setProgressType(Material::DeterminateProgress);
	else
		m_progress->setProgressType(Material::IndeterminateProgress);
}

void ProgressSettingsEditor::setDisable(bool value)
{
	m_progress->setDisabled(value);
}

void ProgressSettingsEditor::setupForm()
{
}

void ProgressSettingsEditor::updateWidget()
{
}

void ProgressSettingsEditor::selectColor()
{
	QColorDialog dialog;
	if (dialog.exec()) {
		QColor color = dialog.selectedColor();
		QString senderName = sender()->objectName();
		if ("progressColorToolButton" == senderName) {
			m_progress->setProgressColor(color);
		}
		else if ("backgroundColorToolButton" == senderName) {
			m_progress->setBackgroundColor(color);
		}
	}
	setupForm();
}

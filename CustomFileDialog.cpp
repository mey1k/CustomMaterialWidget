#include <CustomFileDialog.h>
#include <QLabel>
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QTreeView>
#include <QFileSystemModel>
#include <QPushButton>
#include <QLineEdit>

///
/// \brief CDirSelectionDlg::CDirSelectionDlg
/// \param initialPath
/// \param parent
/// mode 0 Only File, mode 1 Only Directories
///

CDirSelectionDlg::CDirSelectionDlg(const QString initialPath, QWidget *parent, QString mode, Theme *singletonTheme) : QDialog(parent), m_initialPath(initialPath)
{
	theme = singletonTheme;

	double correctScaleW = screenWidth / 2560.0;
	double correctScaleH = screenHeight / 1400.0;

	double factor = (correctScaleH + correctScaleW) / 2;
	double buttonFactor = 1;

	if (factor >= 1.2)
	{
		factor = 1.5;
		buttonFactor = 1;
	}
	else if (factor <= 0.8)
	{
		factor = 0.8;
		buttonFactor = 0.8;
	}

	int fontSize = 14 * factor;
	int buttonBoxSize = 8 * buttonFactor;

	setStyleSheet("QFrame#windowFrame{"
		"background-color: rgba(255, 255, 255, 220);"
		"border-width: 3px;"
		"border-radius: 10px;"
		"border-color: white;"
		"font: "+ QString::number(fontSize) +"px;"
		"}"
	);

	//QString treeStyle = "QTreeView{"
	//	"background-color: rgba(255, 255, 255, 100);"
	//	"border-width: 3px;"g
	//	"border-radius: 10px;"
	//	"border-color: white;"
	//	"font: 14px;"
	//	"}";

	QString themeColor = "rgb(159,34,65)";

	if (theme != nullptr)
	{
		if (theme->themeType == Theme::ThemeType::whiteRed)
		{
			themeColor = "rgb(159,34,65)";
		}
		else
			themeColor = "rgb(42,125,225)";
	}

	QString buttonStyle = "QPushButton{"
		"color: rgb(136, 137, 141);"
		"background-color: rgba(255, 255, 255);"
		"border-style: outset;"
		"border-width: 1px;"
		"border-radius: 15px;"
		"border-color: white;"
		"padding: 6px;"
		"min-width: "+ QString::number(buttonBoxSize) +"em;"
		"}"
		"QPushButton:pressed{"
		"color: white;"
		"background-color: "+ themeColor +";"
		"border-width: 1px;"
		"border-radius: 15px;"
		"border-color: white;"
		"}"
		"QPushButton:focus:pressed{"
		"color: white;"
		"border-width: 1px;"
		"border-radius: 15px;"
		"background-color: "+themeColor+";"
		"outline : 0;"
		"}"
		"QPushButton:hover{"
		"color:white;"
		"background-color: rgb(137,138,141);"
		"}";

	QString treeStyle = "QTreeView {"   // new this apply -> be inherited in parent styleSheet..
		"border: none;"
		"outline: none;"
		"background-color: rgba(255, 255, 255, 100);"
		"border-width: 3px;"
		"border-radius: 10px;"
		"border-color: white;"
		"font: "+ QString::number(fontSize) +"px;"
		"color: rgb(136, 137, 141);"
		"}"

		"QTreeView::item:hover{"
		"background: qlineargradient(spread:pad, x1:0, y1:0.529, x2:1, y2:0.534455, stop:0 rgba(177, 177, 177, 247), stop:1 rgba(255, 255, 255, 240));"
		"border: 0.5px;"
		"border-radius: 3px;"
		"border-color: transparent;"
		"}"

		"QTreeView::item:selected:active{"
		"background: qlineargradient(spread:pad, x1:0, y1:0.529, x2:1, y2:0.534455, stop:0 "+themeColor+", stop:1 rgba(255, 255, 255, 240));"
		"border: 0.5px;"
		"border-radius: 3px;"
		"border-color: transparent;"
		"}"

		"QScrollBar {"
		"border: none;"
		"background-color: none;"
		"}"

		"QScrollBar:horizontal {"
		"height: 16px;"
		"margin: 2px 16px 2px 16px;"
		"border: 1px solid #31363B;"
		"border-radius: 4px;"
		"background-color: #232629;"
		"}"

		"QScrollBar::handle:horizontal {"
		" background-color: #4D545B;"
		"border: 1px solid #31363B;"
		" border-radius: 4px;"
		"min-width: 8px;"
		"}"

		"QScrollBar::handle:horizontal:hover {"
		"background-color: #179AE0;"
		" border: 1px solid #179AE0;"
		" border-radius: 4px;"
		"  min-width: 8px;"
		"}"

		"QScrollBar::add-line:horizontal {"
		"margin: 0px 0px 0px 0px;"
		" border-image: url(:/SurgicalGuide/res/Icon/Scroll/right_arrow_disabled.png);"
		"width: 10px;"
		"height: 10px;"
		"subcontrol-position: right;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::sub-line:horizontal {"
		"margin: 0px 3px 0px 3px;"
		"border-image: url(:/SurgicalGuide/res/Icon/Scroll/left_arrow_disabled.png);"
		"height: 10px;"
		"width: 10px;"
		"subcontrol-position: left;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::add-line:horizontal:hover,"
		"QScrollBar::add-line:horizontal:on {"
		"border-image: url(:/SurgicalGuide/res/Icon/Scroll/right_arrow.png);"
		"height: 10px;"
		"width: 10px;"
		"subcontrol-position: right;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::sub-line:horizontal:hover,"
		"QScrollBar::sub-line:horizontal:on {"
		"border-image: url(:/SurgicalGuide/res/Icon/Scroll/left_arrow.png);"
		"height: 10px;"
		"width: 10px;"
		"subcontrol-position: left;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::up-arrow:horizontal,"
		"QScrollBar::down-arrow:horizontal {"
		" background: none;"
		"}"

		"QScrollBar::add-page:horizontal,"
		"QScrollBar::sub-page:horizontal {"
		" background: none;"
		"}"

		"QScrollBar:vertical {"
		"background-color: #ffffff;"
		"width: 13px;"
		"margin: 13px 2px 13px 2px;"
		"border: 1px solid #ffffff;"
		"border-radius: 3px;"
		"}"

		"QScrollBar::handle:vertical {"
		"background-color: #4D545B;"
		"border: 1px solid #31363B;"
		"min-height: 4px;"
		"max-height: 12px;"
		"border-radius: 3px;"
		"}"

		"QScrollBar::handle:vertical:hover {"
		"background-color: #179AE0;"
		"border: 1px solid #179AE0;"
		"border-radius: 3px;"
		"min-height: 8px;"

		"}"

		"QScrollBar::sub-line:vertical {"
		"margin: 3px 0px 3px 0px;"
		"border-image: url(:/SurgicalGuide/res/Icon/Scroll/up_arrow_disabled.png);"
		"height: 0px;"
		"width: 0px;"
		"subcontrol-position: top;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::add-line:vertical {"
		"margin: 3px 0px 3px 0px;"
		"border-image: url(:/SurgicalGuide/res/Icon/Scroll/down_arrow_disabled.png);"
		"height: 0px;"
		"width: 0px;"
		"subcontrol-position: bottom;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::sub-line:vertical:hover,"
		"QScrollBar::sub-line:vertical:on {"
		" border-image: url(:/SurgicalGuide/res/Icon/Scroll/up_arrow.png);"
		"height: 0px;"
		"width: 0px;"
		"subcontrol-position: top;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::add-line:vertical:hover,"
		"QScrollBar::add-line:vertical:on {"
		"border-image: url(:/SurgicalGuide/res/Icon/Scroll/down_arrow.png);"
		"height: 0px;"
		"width: 0px;"
		"subcontrol-position: bottom;"
		"subcontrol-origin: margin;"
		"}"

		"QScrollBar::up-arrow:vertical,"
		"QScrollBar::down-arrow:vertical {"
		"background: none;"
		"}"

		"QScrollBar::add-page:vertical,"
		"QScrollBar::sub-page:vertical {"
		"background: none;"
		"}";


	QString labelStyle = "QLabel {" // new() apply
		"background-color: transparent;"
		"padding: 10px;"
		"color: rgb(136, 137, 141);"
		"}";

	QString lineEditStyle = "QLineEdit {" // new() apply
		"border-bottom-width: 1px;"
		"border-bottom-style: solid;"
		"border-radius: 1px;"
		"border-color: rgb(136, 137, 141);"
		"background-color: transparent;"
		"padding: 10px;"
		"}";

	setMinimumSize(200, 300);
	resize(400, 430);
	m_model = new QFileSystemModel(parent);

	auto rootIdx = m_model->setRootPath(m_initialPath);

	if (mode == "Dir")
	{
		m_model->setFilter(QDir::Dirs | QDir::Drives | QDir::NoDotAndDotDot | QDir::AllDirs);
	}

	else if (mode == "File")
	{
		m_model->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::AllDirs);
		m_model->setNameFilters(QStringList() << "*.stl");
		m_model->setNameFilterDisables(false);
	}

	m_treeView = new QTreeView(this);
	m_treeView->setStyleSheet(treeStyle);
	m_treeView->setModel(m_model);
	m_treeView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_treeView->setHeaderHidden(true);
	m_treeView->setSortingEnabled(true);
	m_treeView->sortByColumn(0, Qt::AscendingOrder);

	for (int i = 1; i < m_model->columnCount(); i++)    // don't show Size, Type, etc.
		m_treeView->setColumnHidden(i, true);

	m_treeView->scrollTo(rootIdx);
	m_treeView->selectionModel()->setCurrentIndex(rootIdx, QItemSelectionModel::Current | QItemSelectionModel::Select);

	if (mode == "File")
		connect(m_treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CDirSelectionDlg::onCurrentFileChanged);
	else if (mode == "Dir")
		connect(m_treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &CDirSelectionDlg::onCurrentDirChanged);

	auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	buttonBox->setCenterButtons(true);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &CDirSelectionDlg::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &CDirSelectionDlg::reject);
	m_OKbutton = buttonBox->button(QDialogButtonBox::Ok);
	m_OKbutton->setEnabled(false);
	m_OKbutton->setDefault(false);

	//buttonBox->setFixedWidth(400 * (2.0/3.0));

	buttonBox->setStyleSheet(buttonStyle);
	/*QRect rect(buttonBox->geometry().x-180, buttonBox->geometry().y, 150, 50);
	buttonBox->setGeometry(rect);*/

	auto label = new QLabel(tr("Directory Name:"));

	if (mode == "File")
		label->setText(tr("File Name:"));

	label->setStyleSheet(labelStyle);

	m_folderName = new QLineEdit();
	m_folderName->setReadOnly(true);
	m_folderName->setText(QFileInfo(m_initialPath).fileName());
	m_folderName->setStyleSheet(lineEditStyle);

	auto pathLayout = new QHBoxLayout();
	pathLayout->addWidget(label);
	pathLayout->addSpacing(10);
	pathLayout->addWidget(m_folderName);

	auto mainLayout = new QVBoxLayout();
	mainLayout->addWidget(m_treeView);
	mainLayout->addSpacing(10);
	mainLayout->addLayout(pathLayout);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(buttonBox);
	mainLayout->addSpacing(10);

	m_treeView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	buttonBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	mainLayout->setStretch(0, 9);
	mainLayout->setStretch(2, 2);
	mainLayout->setStretch(4, 2);

	auto frame = new QFrame();
	frame->setLayout(mainLayout);

	auto frameLayout = new QHBoxLayout();
	frame->setObjectName("windowFrame");
	frameLayout->addWidget(frame);

	//buttonBox->setGeometry(((this->geometry().x() + this->width() / 2) - buttonBox->width() / 2), buttonBox->geometry().y(), buttonBox->width(), buttonBox->height());

	setLayout(frameLayout);
}

void CDirSelectionDlg::onCurrentDirChanged()
{
	auto fileInfo = m_model->fileInfo(m_treeView->selectionModel()->currentIndex());
	m_folderName->setText(fileInfo.fileName());

	m_OKbutton->setEnabled(fileInfo.isDir());
	m_OKbutton->setDefault(fileInfo.isDir());
}

void CDirSelectionDlg::onCurrentFileChanged()
{
	auto fileInfo = m_model->fileInfo(m_treeView->selectionModel()->currentIndex());
	m_folderName->setText(fileInfo.fileName());

	m_OKbutton->setEnabled(fileInfo.isFile());
	m_OKbutton->setDefault(fileInfo.isFile());
}

QDir CDirSelectionDlg::directory() const
{
	return QDir(m_model->fileInfo(m_treeView->selectionModel()->currentIndex()).absoluteFilePath());
}

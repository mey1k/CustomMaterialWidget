#ifndef  _CUSTOMFILEDIALOG_H_
#define _CUSTOMFILEDIALOG_H_

#include <qapplication.h>
#include <QtWidgets/qdialog.h>
#include <qdir.h>
#include <Theme.h>
#include <qdesktopwidget.h>

class QTreeView;
class QFileSystemModel;
class QLineEdit;
class QPushButton;

class CDirSelectionDlg : public QDialog {
	Q_OBJECT

public:
	CDirSelectionDlg(const QString initialPath, QWidget *parent = nullptr, QString mode = "File", Theme *singletonTheme = nullptr);
	QDir directory() const;

private:
	QTreeView * m_treeView;
	QFileSystemModel *m_model;
	QLineEdit *m_folderName;
	QPushButton *m_OKbutton;
	QString m_initialPath;

	QRect rec = QApplication::desktop()->availableGeometry();
	int screenWidth = rec.width();
	int screenHeight = rec.height();

	Theme *theme = nullptr;

public slots:
	void onCurrentDirChanged();
	void onCurrentFileChanged();
};

#endif
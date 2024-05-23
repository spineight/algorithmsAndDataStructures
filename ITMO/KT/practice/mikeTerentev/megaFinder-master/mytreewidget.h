#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H


#include <qcommonstyle.h>
#include <qtreewidget.h>
#include "QKeyEvent"
#include "mainwindow.h"
#include <qdesktopservices.h>
#include <qdebug.h>
#include <qapplication.h>
#include "QClipboard"
#include "progressdialog.h"
#include "textviewer.h"
#include <QFileInfoList>
#include <QMessageBox>
#include <QThread>
#include <qprogressbar.h>
#include <QDir>
class MyTreeWidget : public QTreeWidget {
    Q_OBJECT
public:
    const int DIR_COL = 1;
    const int NAME_COL = 0;

    virtual ~MyTreeWidget(){
    }

   explicit MyTreeWidget(QWidget *parent = nullptr):QTreeWidget (parent) {
        setUniformRowHeights(1);
    }


    void addFilesFromDir(QPair<QString, QList<QString> > &path);

    void removeFile(QTreeWidgetItem *child);

    QString getItemName(QTreeWidgetItem *item);


    QTreeWidgetItem *getSelectedFile() {
        return selectedFile;
    }

    void setSelectedFile(QTreeWidgetItem *x) {
        selectedFile = x;
    }

    void setMainWindow(main_window* mv){
        mainwindow = mv;
    }

    void addFilesFromDirs(QVector<QPair<QString, QList<QString> > > &list);

    void deleteDir(const QString &dir);
public slots:

    void fileSelected(QTreeWidgetItem *curFile);

    void keyPressEvent(QKeyEvent *event);

private:

    QCommonStyle style;
    main_window* mainwindow;
    QTreeWidgetItem *selectedFile = nullptr;
    void setItemParameters(QTreeWidgetItem *item, QFileInfo &file_info);
};

#endif // MYTREEWIDGET_H

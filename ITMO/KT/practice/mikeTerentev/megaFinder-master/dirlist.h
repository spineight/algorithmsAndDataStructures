#ifndef DIRLIST_H
#define DIRLIST_H

#include "mainwindow.h"

#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qtreewidget.h>
#include<qdebug.h>
#include <qevent.h>
class DirList : public QTreeWidget
{
       Q_OBJECT
public:
    DirList(QWidget *parent = nullptr):QTreeWidget(parent){}
    ~DirList() = default;

    void setMainWindow(main_window* mv){
        mainwindow = mv;
    }
public slots:
  void addFileDir( QString dir);
  void deleteDir(QString dir);
  void fileClicked(QTreeWidgetItem * item);

  void keyPressEvent(QKeyEvent *event);
private:
    QTreeWidgetItem * selectedDir = nullptr;
    main_window* mainwindow;
};

#endif // DIRLIST_H

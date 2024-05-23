#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include "fileindexer.h"
#include "progressdialog.h"
#include "trigramsrepository.h"
#include "trigramssearcher.h"

#include <memory>
#include <qmainwindow.h>
#include <qcommonstyle.h>
#include <QTreeWidgetItem>
#include <QFileSystemWatcher>
#include <QFutureWatcher>

typedef QVector<QPair<QString,QList<QString>>> qstring_list;

namespace Ui {
    class MainWindow;
}

class main_window : public QMainWindow {
    Q_OBJECT

public:


    explicit main_window(QWidget *parent = nullptr);

    ~main_window();


    void findNextFile();
    void block(bool isBlock);
    public
    slots:
    void disNextPrev(bool x);
    void updateFile(QString path);
    void updateDirectory(QString dir);
    void changePattern();
    void  find();
    void fileClicked(QTreeWidgetItem *widget);
    void openFile(QString path);
    void addPreprocessedDir(QString curDir);
    void addFileDirectory(QString dir = "");
    void prev();
    void foundDuplicate(QString dir);
     void removeDirectory(QString dir);
     void finishedSearch(QVector<QPair<QString, QList<QString> > > info, bool fin);
     void endRemoving();
     private
       slots:

    void show_about_dialog();   
    void next();
signals:
    void stopSearching();
    void stopIndexing();
private:
    QThread thread;
    QString processingDir;
    bool isUpdateProcess = false;
    QFutureWatcher<void> result;
    TrigramsSearcher* searcher;
    QFileSystemWatcher* watcher;
    TrigramsRepository* trigramsRepository;
    QString pattern;
    FileIndexer indexer;
    QCommonStyle style;
    std::unique_ptr <Ui::MainWindow> ui;
    void clear();
};

#endif // MAINWINDOW_H

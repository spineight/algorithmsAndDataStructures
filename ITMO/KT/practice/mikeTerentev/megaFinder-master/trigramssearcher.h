#ifndef TRIGRAMSSEARCHER_H
#define TRIGRAMSSEARCHER_H

#include "fileindexer.h"
#include "trigramsrepository.h"

#include <qstring.h>
#include <QMap>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QDialog>
#include <QDirIterator>
#include <QThread>
#include <qfilesystemwatcher.h>


class TrigramsSearcher:public   QObject
{
    Q_OBJECT
public:
    TrigramsSearcher(QString dir,TrigramsRepository* trigramsRepository,  QFileSystemWatcher* watcher) :
        trigramsRepository(trigramsRepository),  watcher(watcher), dir(dir)
    {}

   const QString getDir(){
        return dir;
    }
   QMap<QString,QSet<uint64_t>>& getData(){
        return  dirData;
    }

   bool isSearchCompleted(){
       return isCompleted;
   }
   QList<QString> getFilePaths(){
       return filePaths;
   }

   void setPattern(QString p){
       pattern = p;
   }
public slots:
    void indexDir();
    QSet<uint64_t> getFileTrigrams();

    void find();
    void removeDirectory();
signals:
     void updateBar(int);
     void filesCounted(int);
     void fileDone(int);
     void finishedSearch(QVector<QPair<QString,QList<QString>>>);
     void addPreprocessedDir(QString);
     void foundDuplicate(QString);
     void fileIndexing();
     void finished(int);
     void finished();
     void finished(QVector<QPair<QString,QList<QString>>>,bool);
     void finishedAll(QString);
private:

    TrigramsRepository* trigramsRepository;
    FileIndexer indexer;
    QMap<QString,QSet<uint64_t>> dirData;
    QFileSystemWatcher* watcher;
    QList<QString> filePaths;
    QString dir;
    QString pattern;
    bool isCompleted = false;
};

#endif // TRIGRAMSSEARCHER_H

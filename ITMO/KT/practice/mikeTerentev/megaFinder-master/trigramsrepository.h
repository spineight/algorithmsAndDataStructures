#ifndef PATTERNSEARCHER_H
#define PATTERNSEARCHER_H

#include <qset.h>
#include "QString"
#include "QMap"
#include <qdiriterator.h>
#include <QDebug>
#include <QList>
#include <QPair>
#include <QThread>
class TrigramsRepository : public QObject
{
Q_OBJECT

public:
    const int  BUFFER_SZ =  4096;
    TrigramsRepository();
    bool  contains(const QString &path,QString qpattern);
    const QMap<QString,QMap<QString,QSet<uint64_t>>>& getTrigramData(){
        return trigramsData;
    }
    bool canAddDir(QString path);
    void deleteDir(QString dir);
    QVector<QPair<QString, QList<QString> > > find(QString pattern);
    void insertFile(QString filePath, QSet<uint64_t> tdata);
    int getFilesAmount(){
        return filesAmount;
    }
signals:
    void intertuptionRequest();
    void fileDone(int);
public slots:
    QString findDirByPath(QString path);
    void insert(QString dir, QMap<QString, QSet<uint64_t> > tdata);
private:
    int filesAmount = 0;
    QMap<QString,QMap<QString,QSet<uint64_t>>> trigramsData;
    //<dir,<file, trigrams>>

};

#endif // PATTERNSEARCHER_H

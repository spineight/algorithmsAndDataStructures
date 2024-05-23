#ifndef TBUFFEREDREADER_H
#define TBUFFEREDREADER_H

#include <QFile>
#include <qstring.h>
#include <qtextstream.h>



class TBufferedReader
{
public:
    TBufferedReader(QString filePath);
    ~TBufferedReader();
    uint64_t nextTrigram();
    bool hasNextTrigram();
    bool isTextFile();
    bool canOpen();
private:
    bool isReadble = false;
    QByteArray::iterator it;
    int size;
    QFile* file;
    uint64_t hash;
    QByteArray byteLine;
    int pointer;
};

#endif // TBUFFEREDREADER_H

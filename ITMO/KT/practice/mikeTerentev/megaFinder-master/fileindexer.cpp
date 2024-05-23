#include "fileindexer.h"
#include "tbufferedreader.h"
#include <QDebug>
FileIndexer::FileIndexer(std::string pattern):pattern(pattern){}

QSet<uint64_t> FileIndexer::findTrigramsOfFile(const QString& file)
{
    QSet<uint64_t> data;
    TBufferedReader reader(file);
    if(!reader.canOpen()){
        qDebug()<<"Can't open ---->"<<file <<"<----";
        return  data;
    }
    if(!reader.isTextFile()){
        //qDebug()<<"FILE IS BINARY"<<file;
        return data;
    }
    while(reader.hasNextTrigram()){
        uint64_t curTrigram = reader.nextTrigram();
        data.insert(curTrigram);
     }
     return  data;
 }

QSet<uint64_t> FileIndexer::findTrigramsOfString(const std::string& line){
    size_t pointer = 0;
    QSet<uint64_t> result;
    if(line.size()<3){
        result.insert(makeTrigram(line));
    }
    else{
        while (pointer + 2 < line.size()){
            localHash=0;
            for (size_t j = 0; j < 3; ++j) {
                 localHash = (localHash << 8);
                 localHash += static_cast<unsigned char>(line[pointer + j]);
            }
            result.insert(localHash);
            pointer++;
        }
    }

    return result;
}

uint64_t FileIndexer::makeTrigram(const std::string& info){
    localHash=0;
    for (int j = 0; j < info.size() && j < 3; ++j) {
         localHash = (localHash << 8);
         localHash += static_cast<unsigned char>(info[j]);
    }
    return localHash;
}

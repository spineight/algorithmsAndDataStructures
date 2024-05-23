#include "tbufferedreader.h"

#include <QDebug>
    TBufferedReader::TBufferedReader(QString filePath){
        file = new QFile(filePath);
        if (!file->exists()){
           isReadble = false;
           return;
        }
        isReadble = file->open(QIODevice::ReadOnly | QIODevice::Text);
        if (isReadble){
            byteLine = file->readAll();
            it = byteLine.begin();
            size = byteLine.size();
            pointer = 0;
        }
    }
    bool TBufferedReader::canOpen(){
        return isReadble;
    }

    uint64_t TBufferedReader::nextTrigram(){
        hash = static_cast<unsigned char>(*it);
        for(int i=0; i<2;i++){
             it++;
             hash = (hash << 8) +  static_cast<unsigned char>(*it);
        }
        it--;
        pointer++;
        return hash;
    }

    bool TBufferedReader::hasNextTrigram(){
        return  (pointer + 2 < size) ? true : false;
    }
    TBufferedReader::~TBufferedReader(){
        delete file;
    }

    bool TBufferedReader::isTextFile(){
        for(auto it = byteLine.begin(); it != byteLine.end(); it++){
            if(*it == '\0'){
                return false;
            }
        }
        return true;
    }

#include "fileindexer.h"
#include "trigramsrepository.h"
#include <QTextStream>
#include <QDialog>
#include <algorithm>

TrigramsRepository::TrigramsRepository(){
    //no actions
}

bool TrigramsRepository::canAddDir(QString path){
    if(path.isEmpty()){
        qDebug()<<"PATH EMPTY!";
        return 0;
     }
     for (auto& keyDir : trigramsData.keys()){
         if (keyDir.contains(path) || path.contains(keyDir)){
             return false;
         }
     }
     return true;
}


void TrigramsRepository::deleteDir(QString dir){
    filesAmount -= trigramsData[dir].size();
    trigramsData.remove(dir);
     qDebug()<<"remove : "<< dir<<"Map size: "<<trigramsData.size();
}

void TrigramsRepository::insertFile(QString filePath, QSet<uint64_t> tdata){
    QString directory = findDirByPath(filePath);
    trigramsData[directory].insert(filePath, tdata);
}
void TrigramsRepository::insert(QString dir, QMap<QString,QSet<uint64_t>> tdata){
    filesAmount +=tdata.size();
    trigramsData.insert(dir, tdata);
}
QVector<QPair<QString,QList<QString>>> TrigramsRepository::find(QString qpattern){
    int n = 0;
    std::string pattern = qpattern.toStdString();
     QVector<QPair<QString,QList<QString>>> result;
     FileIndexer indexer;
     QSet<uint64_t> patternTrigrams =indexer.findTrigramsOfString(pattern);
     for (auto curDir = trigramsData.begin(); curDir != trigramsData.end(); curDir++){
         QList<QString> filesList;
         for (auto curFile = curDir.value().begin(); curFile != curDir.value().end(); curFile++){
             if (QThread::currentThread()->isInterruptionRequested()){
                 qDebug()<<"====>InterruptionRequested<====";
                return result;
             }
             n++;
             bool isMatch = true;
             QString filePath = curFile.key();
             if( pattern.size() >= 3){
                 for (auto& patternTrigram : patternTrigrams){
                     if (!curFile.value().contains(patternTrigram)){
                         isMatch = false;
                     }
                 }
             }
             else {
                  isMatch = true;
             }
             if (isMatch){
                 QFile file(filePath);
                 if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) continue ;
                 QTextStream stream(&file);
                 std::string std_text = stream.readAll().toStdString();
                 auto it = std::search(std_text.begin(), std_text.end(),
                                    std::boyer_moore_searcher(
                                       pattern.begin(),pattern.end()));
                 if (it == std_text.end()){
                     continue;
                 }
                //if (contains(filePath,qpattern)) {
                     filesList.append(filePath);
                // }
             }
             emit fileDone(n);
          }
        result.push_back(qMakePair(curDir.key(),filesList));
     }
     return result;
 }

QString TrigramsRepository::findDirByPath(QString path){
    for (auto curDir = trigramsData.begin(); curDir != trigramsData.end(); curDir++){
        if(path.contains(curDir.key())){
            return curDir.key();
        }
    }
    qDebug()<<"LOGICAL ERROR NOT FOUND DIR BY PATH";
    return "";
}


bool TrigramsRepository::contains(const QString &path, QString qpattern) {
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QString buffer;
        while (buffer.append(stream.read(BUFFER_SZ)).size() >= qpattern.size()) {
            for (int i = 0; i < BUFFER_SZ - qpattern.size() + 1; i++) {
                int j = 0;
                while (qpattern[j] == buffer[i + j] && j < qpattern.size()) {
                    j++;
                }
                if (j == qpattern.size()) {
                    file.close();
                    return true;
                }
            }
            buffer = buffer.mid(buffer.size() - qpattern.size() + 1, qpattern.size() - 1);
        }
    }
    file.close();
    return false;
}

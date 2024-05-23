#include "trigramssearcher.h"


void TrigramsSearcher::find(){
    qDebug()<< "=====>started<====";
    emit filesCounted(trigramsRepository->getFilesAmount());
    auto foundData = trigramsRepository->find(pattern);
    if (QThread::currentThread()->isInterruptionRequested()){
        emit finished(foundData,false);
        return;
    }
    qDebug()<<"=====>finished<====";
    emit finished(foundData,true);
}

void TrigramsSearcher::indexDir(){
    if (!trigramsRepository->canAddDir(dir)){
        emit foundDuplicate(dir);
        emit finished(QDialog::Accepted);
        return;
    }
     qDebug()<<"add : "<< dir <<"Map size inc";
     int amount = 0;
     QDirIterator pre_it(dir, QDir::Files  | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
      while (pre_it.hasNext()) {
          pre_it.next();
          amount++;
     }
     emit filesCounted(amount);

   QDirIterator it(dir, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
           if (QThread::currentThread()->isInterruptionRequested()){
              emit finished(QDialog::Accepted);
              return;
           }
           QFileInfo  file =(it.next());
           QString filePath(file.absoluteFilePath());
           //qDebug()<<filePath;
           if (file.isSymLink()) {
               continue;
           }
           QSet<uint64_t> fileData = indexer.findTrigramsOfFile(filePath);
           if (!fileData.isEmpty()){
              dirData.insert(filePath, fileData);
              filePaths.append(filePath);
           }
           emit fileIndexing();
       }
       trigramsRepository->insert(dir,dirData);
       watcher->addPaths(filePaths);
       watcher->addPath(dir);
       qDebug()<<"Watching directories : "<<watcher->directories().size()<<"files : "<<watcher->files().size();
       emit addPreprocessedDir(dir);
       emit finished(QDialog::Accepted);
}

QSet<uint64_t> TrigramsSearcher::getFileTrigrams(){
    return indexer.findTrigramsOfFile(dir);
}
void TrigramsSearcher::removeDirectory(){
    int n = 0;
    watcher->removePath(dir);
    QDirIterator it(dir, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
     while (it.hasNext()) {
        emit updateBar(++n);
        QFileInfo file = it.next();
        if (file.isSymLink()) {
            continue;
        }
        watcher->removePath(file.absoluteFilePath());
        //qDebug()<<"remove file : "<< file.absoluteFilePath();
     }
    qDebug()<<"Watching directories : "<<watcher->directories().size()<<"files : "<<watcher->files().size();
    trigramsRepository->deleteDir(dir);
    emit finished();
}

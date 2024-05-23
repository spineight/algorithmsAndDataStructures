
#include "mytreewidget.h"


void MyTreeWidget::addFilesFromDir(QPair<QString,QList<QString>>& dir){
     if (!dir.second.size()){
         return;
     }
     QTreeWidgetItem *headerItem = new QTreeWidgetItem(this);
     QList<QTreeWidgetItem*> children;
     headerItem->setText(DIR_COL,dir.first);
     for (auto& path : dir.second){
         QFileInfo file(path);
         QTreeWidgetItem *item = new QTreeWidgetItem();
         item->setIcon(NAME_COL, style.standardIcon(QStyle::SP_FileIcon));
         setItemParameters(item, file);
        children.append(item);
     }
     headerItem->addChildren(children);
     addTopLevelItem(headerItem);
}

void MyTreeWidget::addFilesFromDirs(QVector<QPair<QString,QList<QString>>>& list){
    clear();
    for (auto& dir : list){
        addFilesFromDir(dir);
    }
}

void MyTreeWidget::deleteDir(const QString& dir){
      QTreeWidgetItemIterator it(this);
      while(*it){
          qDebug()<<(*it)->text(DIR_COL);
          if ((*it)->text(DIR_COL) == dir){
              delete *it;
              break;
          }
          it++;
      }
}

void MyTreeWidget::fileSelected(QTreeWidgetItem *curFile) {
     selectedFile = curFile;
     qDebug()<<"changed selected item";
}


void MyTreeWidget::removeFile(QTreeWidgetItem *child) {
    QString delFilePath = getItemName(child);
    QFile file(delFilePath);
    if (!file.remove()) {
        QMessageBox::warning(this, "Can't delete file",
                             QString("File \n\n %1 \n\n can't be removed.").arg(delFilePath),
                             QMessageBox::Ok);
    }
}

QString MyTreeWidget::getItemName(QTreeWidgetItem *item) {

    return QString("%1/%2").arg(item->text(DIR_COL), item->text(NAME_COL));
}


void MyTreeWidget::keyPressEvent(QKeyEvent * event){
    QString x =event->text();
    qDebug() << Qt::Key(event->key());
    QTreeWidget::keyPressEvent(event);
    if ( event->key() == Qt::Key_Return){
       mainwindow->openFile(getItemName(selectedFile));
    }
}
void MyTreeWidget::setItemParameters(QTreeWidgetItem *item, QFileInfo &file_info) {
    item->setText(DIR_COL, file_info.path());
    item->setText(NAME_COL, file_info.fileName());
}

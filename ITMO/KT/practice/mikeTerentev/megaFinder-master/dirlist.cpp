#include "dirlist.h"






void DirList::addFileDir( QString dir){
    QTreeWidgetItem* x = new QTreeWidgetItem(this);
    x->setText(0,dir);
    addTopLevelItem(x);
}
void DirList::deleteDir(QString dir){
   auto x = findItems(dir,Qt::MatchContains,0);
    delete x[0];
}
void DirList::fileClicked(QTreeWidgetItem * item){
    selectedDir = item;
    qDebug()<<"dirClicked changed in dir list";
}


void DirList::keyPressEvent(QKeyEvent * event){
    QString x =event->text();
    if ( event->key() == Qt::Key_Backspace){
        mainwindow->removeDirectory(selectedDir->text(0));
        return;
    }
    if ( event->key() == Qt::Key_N){
        mainwindow->addFileDirectory();
    }
    qDebug() << Qt::Key(event->key());

    QTreeWidget::keyPressEvent(event);
}

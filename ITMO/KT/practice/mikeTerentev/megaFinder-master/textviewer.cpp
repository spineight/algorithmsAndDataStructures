#include "textviewer.h"

#include <QMessageBox>
#include <QTextCursor>

void TextViewer::save(){
    if(document()->isModified()){

    }
}
void TextViewer::search()
{
       positions.clear();
        amount = 0;
        currentUsage=0;
        extraSelections.clear();
        moveCursor(QTextCursor::Start);
        while(find(line))
        {
            amount++;
            QTextEdit::ExtraSelection extra;
            extra.format.setBackground(color);
            extra.cursor = textCursor();
            positions.push_back(textCursor().position());
            extraSelections.append(extra);
        }

   setExtraSelections(extraSelections);
   moveCursor(QTextCursor::Start);
}

void TextViewer::prev(){
    qDebug()<<"search next place";
    if (amount == 0)
        return;
    currentUsage--;
    if(currentUsage < 1){
        currentUsage = amount;
    }
    QTextCursor cursor(textCursor());
    cursor.setPosition(positions[currentUsage - 1]);
    cursor.setPosition(positions[currentUsage - 1] - line.length(),QTextCursor::KeepAnchor);
    setTextCursor(cursor);
}

void TextViewer::next(){
   qDebug()<<"search next place";
   if (amount == 0)
       return;
   currentUsage++;
   if(currentUsage > amount){
       currentUsage = 1;
   }
   QTextCursor cursor(textCursor());
   cursor.setPosition(positions[currentUsage - 1]);
   cursor.setPosition(positions[currentUsage - 1] - line.length(),QTextCursor::KeepAnchor);
   setTextCursor(cursor);
  }

void TextViewer::openFile(QString path){
    filePath = path;
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Can't open file",
                             QString("File \n\n %1 \n\n can't be opened.").arg(filePath),
                             QMessageBox::Ok);
    }
    QTextStream ReadFile(&file);
    document()->setPlainText(ReadFile.readAll());
    search();
    isChanged = false;
}

void TextViewer::enableFlag(){
    qDebug()<<"text modifited";
    isChanged = true;
}

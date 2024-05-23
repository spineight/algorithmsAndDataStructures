#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include <QTextBrowser>

#include <QDebug>
#include <QFile>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QTextCursor>
class TextViewer : public QTextEdit
{
     Q_OBJECT
public:
    TextViewer(QWidget *parent = nullptr):QTextEdit(parent){
        setReadOnly(true);
        moveCursor(QTextCursor::Start);
    }
    ~TextViewer()=default;
    void search();

    void setLine(const QString& tx){
        line = tx;
        //line = *(tx.split('\n').begin());
        qDebug()<<"modline"<<line;
    }
    void save();

    int getAmount(){
        return amount;
    }

    int getCurrentUsage(){
        return currentUsage;
    }
    const QString& getFilePath(){
        return filePath;
    }
    void prev();
public slots:
    void openFile(QString path);

    void next();
    void enableFlag();
private:
    QVector<int> positions;
    QTextCursor mainCursor;
   QList<QTextEdit::ExtraSelection>::iterator it;
    bool isChanged = false;
    int amount, currentUsage = 0;
    QString line;
    QString filePath;
    QList<QTextEdit::ExtraSelection> extraSelections;
    QColor color = QColor(Qt::yellow).lighter(120);

};

#endif // TEXTVIEWER_H

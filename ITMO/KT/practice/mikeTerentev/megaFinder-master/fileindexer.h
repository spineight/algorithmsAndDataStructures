#ifndef FINDERALGORITHM_H
#define FINDERALGORITHM_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QSet>


class FileIndexer : public QObject
{
    Q_OBJECT
public:
    FileIndexer(std::string pattern);

    FileIndexer() = default;

    std::string getLine()
    {
        return pattern;
    }
    void setLine(const std::string& text)
    {
        pattern = text;
    }
    QSet<uint64_t> findTrigramsOfString(const std::string& line);
    uint64_t makeTrigram(const std::string&info);
private:
   QSet<std::string> getDirectories(){
        return directories;
    }

private:
    uint localHash;
    QSet<std::string> directories;
    std::string pattern;
    QList<std::string> foundFiles;
public slots:
    QSet<uint64_t> findTrigramsOfFile(const QString &file);
};

#endif // FINDERALGORITHM_H

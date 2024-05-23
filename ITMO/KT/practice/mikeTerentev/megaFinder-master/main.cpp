
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "mainwindow.h"
#include "tbufferedreader.h"
#include "QDebug"
int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    main_window w;
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("Mega Finder");
    parser.addHelpOption();
    parser.addVersionOption();
    w.show();
    return app.exec();
}

#include <QCoreApplication>
#include "filemanager.h"
#include <thread>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> paths_list = {"fileName1.txt", "fileName1.txt"};
    //QList<QString> paths_list = {};
    FileManager manager(paths_list);
    QObject::connect(&manager, SIGNAL(fileChanged(std::string)), &manager, SLOT(printLog(std::string)));
    manager.addFile("fileName3.txt");
    manager.addFile("fileName3.txt");
    manager.addFile("fileName4.txt");
    manager.addFile("fileName5.txt");

    //manager.checkFiles();
    while (true) {
        manager.checkFiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return a.exec();
}

#include <QCoreApplication>
#include "filemanager.h"
#include <thread>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QString> paths_list = {"fileName1.txt", "fileName2.txt"};
    //QList<QString> paths_list = {};
    FileManager& manager = FileManager::getInstance(paths_list);
    //FileManager manager();
    FileManager& manager2 = FileManager::getInstance();
    manager.addFile("fileName3.txt");
    QObject::connect(&manager, SIGNAL(fileChanged(std::string)), &manager, SLOT(printLog(std::string)));
    manager.addFile("fileName3.txt");
    manager.addFile("fileName3.txt");
    manager2.addFile("fileName4.txt");
    manager2.addFile("fileName5.txt");

    while (true) {
        //manager.checkFiles();
        manager.checkFiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return a.exec();
}

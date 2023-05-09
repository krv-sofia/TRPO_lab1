#include <QCoreApplication>
#include "filemanager.h"
#include <thread>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileManager manager;
    QObject::connect(&manager, SIGNAL(fileChanged(std::string)), &manager, SLOT(printLog(std::string)));
    manager.addFile("fileName1.txt");
    manager.addFile("fileName2.txt");
    manager.addFile("fileName3.txt");

    while (true) {
        manager.checkFiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return a.exec();
}

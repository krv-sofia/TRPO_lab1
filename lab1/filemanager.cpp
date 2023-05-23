#include "filemanager.h"
#include <iostream>
#include <QFileInfo>
#include <QDebug>

FileManager::FileManager(const QList<QString> paths) {
    if (paths.length() > 0) {
        for (auto i = paths.constBegin(); i != paths.constEnd(); ++i) {
             FileInfo fileInfo = *i;
             QFileInfo file(*i);
             this->_files_info.push_back(fileInfo);
             this->_files_list.push_back(file.absoluteFilePath());
         }
    } else {
        FileManager();
    }
}

void FileManager::addFile(QString path)
{
     QFileInfo newFile(path);
     if (_files_list.contains(newFile.absoluteFilePath())) {
         emit fileChanged("You are already tracking this file");
         return;
     }
     FileInfo newFileInfo(path);
     _files_info.push_back(newFileInfo);
     _files_list.push_back(newFile.absoluteFilePath());
     emit fileChanged("\nFile '" + newFileInfo.getFileName().toStdString() + "' was added.");
}



void FileManager::checkFiles()
{
    int i = 0;
    for (auto &filePath : _files_list) {
        QFileInfo fileInfo(filePath);
        FileInfo temp = _files_info[i];
        if (temp._doesExist && fileInfo.exists()) {
                 if (_files_info[i]._size != fileInfo.size()) {
                     emit fileChanged("\nFile '" + temp.getFileName().toStdString() + "' was changed \nfrom " + std::to_string(temp.getFileSize()) + " bytes" +
                                      + " to " + std::to_string(fileInfo.size()) + " bytes");
                     _files_info[i]._size = fileInfo.size();
                 }
             } else if (temp._doesExist && !fileInfo.exists()) {
                 emit fileChanged("\nFile '" + temp.getFileName().toStdString() + "' was deleted.");
                 _files_info[i]._doesExist = false;
             } else if (!temp._doesExist && fileInfo.exists()){
                 emit fileChanged("\nFile '" + temp.getFileName().toStdString() + "' was created.");
                 _files_info[i]._doesExist = true;
                 _files_info[i]._size = fileInfo.size();
             }
        i++;
    }
}

void FileManager::printLog(std::string str)
{
    std::cout << str << std::endl;
}

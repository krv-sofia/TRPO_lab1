#include "filemanager.h"
#include <iostream>
#include <QFileInfo>
#include <QDebug>

FileManager::FileManager(const QList<QString> paths) {
    if (paths.length() > 0) {
        for (auto i = paths.constBegin(); i != paths.constEnd(); ++i) {
             FileInfo fileInfo = *i;
             this->_files_info.push_back(fileInfo);
         }
    } else {
        FileManager();
    }
}

void FileManager::addFile(QString path)
{
    QFileInfo newFile(path);
     for (auto i = _files_info.constBegin(); i != _files_info.constEnd(); ++i) {
         if (i->_fileName == newFile.absoluteFilePath()) {
             emit fileChanged("You are already tracking this file");
             return;
         }
     }
     FileInfo newFileInfo(path);
     _files_info.push_back(newFileInfo);
     emit fileChanged("\nFile '" + newFileInfo._fileName.toStdString() + "' was added.");
}



void FileManager::checkFiles()
{
    int i = 0;
       for (auto &files : _files_info) {
           QFileInfo fileInfo(files._fileName);
           FileInfo temp = _files_info[i];
           if (temp._doesExist && fileInfo.exists()) {
                    if (_files_info[i]._size != fileInfo.size()) {
                        emit fileChanged("\nFile '" + temp._fileName.toStdString() + "' was changed \nfrom " + std::to_string(temp._size) + " bytes" +
                                         + " to " + std::to_string(fileInfo.size()) + " bytes");
                        _files_info[i]._size = fileInfo.size();
                    }
                } else if (temp._doesExist && !fileInfo.exists()) {
                    emit fileChanged("\nFile '" + temp._fileName.toStdString() + "' was deleted.");
                    _files_info[i]._doesExist = false;
                } else if (!temp._doesExist && fileInfo.exists()){
                    emit fileChanged("\nFile '" + temp._fileName.toStdString() + "' was created.");
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

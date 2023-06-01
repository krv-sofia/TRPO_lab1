#include "filemanager.h"
#include <iostream>
#include <QFileInfo>
#include <QDebug>

FileManager::FileManager(const QList<QString> paths) {
    if (paths.length() > 0) {
        for (auto i = paths.constBegin(); i != paths.constEnd(); ++i) {
            if (!_files_info.isEmpty()) {
                QFileInfo temp(*i);
                for (int j = 0; j < _files_info.length(); ++j) {
                    if (temp.absoluteFilePath() == _files_info[j]._fileName) {
                        return;
                    }
                }
            }
            FileInfo fileInfo(*i);
            _files_info.push_back(fileInfo);
        }
    } else {
        FileManager();
    }
}

void FileManager::addFile(QString path)
{
    FileInfo newFileInfo(path);
    for (auto i = _files_info.constBegin(); i != _files_info.constEnd(); ++i) {
        if (i->_fileName == newFileInfo._fileName) {
            //emit fileChanged("You are already tracking this file");
            return;
        }
    }

     _files_info.push_back(newFileInfo);
     //emit fileChanged("\nFile '" + newFileInfo._fileName.toStdString() + "' size: " + std::to_string(newFileInfo._size));
}



void FileManager::checkFiles()
{
    int i = 0;
    for (auto &files : _files_info) {
        QFileInfo fileInfo(files._fileName);
        //FileInfo temp = _files_info[i];
        if (files._doesExist && fileInfo.exists()) {
            if (_files_info[i]._size != fileInfo.size()) {
                 emit fileChanged("\nFile '" + files._fileName.toStdString() + "' was changed \nfrom " + std::to_string(files._size) + " bytes" +
                                  + " to " + std::to_string(fileInfo.size()) + " bytes");
                 _files_info[i]._size = fileInfo.size();
            }
         } else if (files._doesExist && !fileInfo.exists()) {
             emit fileChanged("\nFile '" + files._fileName.toStdString() + "' was deleted.");
             _files_info[i]._doesExist = false;
            } else if (!files._doesExist && fileInfo.exists()) {
                 emit fileChanged("\nFile '" + files._fileName.toStdString() + "' was created.");
                 _files_info[i]._doesExist = true;
                 _files_info[i]._size = fileInfo.size();
        }
        emit fileChanged("\nFile '" + files._fileName.toStdString() + "' size: " + std::to_string(files._size));
        i++;
    }

}

void FileManager::printLog(std::string str)
{
    std::cout << str << std::endl;
}

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QFile>
#include <QObject>
#include <QFileInfo>

class FileManager : public QObject {
    Q_OBJECT
public:
    FileManager() {}
    FileManager(const QList<QString> paths);
    void addFile(const QString path);
    void checkFiles();

public slots:
    void printLog(std::string str);
signals:
    void fileChanged(std::string str);

private:
    struct FileInfo {
    public:
        bool _doesExist;
        qint64 _size;
        QString _fileName;

        FileInfo(QString path) {
            QFileInfo _file(path);
            _fileName = _file.absoluteFilePath();
            _doesExist = _file.exists();
            _size = _file.size();
        }
    };

    QList<FileInfo> _files_info;
};
#endif // FILEMANAGER_H

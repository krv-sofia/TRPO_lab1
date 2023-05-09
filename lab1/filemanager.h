#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QFile>
#include <QObject>
#include <QFileInfo>

class FileManager : public QObject {
    Q_OBJECT
public:
    FileManager() {};
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
            _fileName = path.section("/",-1,-1);
            _doesExist = _file.exists() && _file.isFile();
            _size = _file.exists() ? _file.size() : 0;
        }
        QString getFileName() {
            return _fileName;
        }
        int getFileSize() {
            return _size;
        }
    };

    QList<FileInfo> _files_info;
    QList<QString> _files_list;
};
#endif // FILEMANAGER_H

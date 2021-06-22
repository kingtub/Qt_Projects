#ifndef OTHER_HPP
#define OTHER_HPP

#include<QString>
#include<QDir>
#include<QDirIterator>
#include<QFileInfo>

// 计算一个文件夹的硬盘大小
unsigned long long calSize(const QString &dirPath) {
    unsigned long long size = 0;
    QDir dir(dirPath);
    if(!dir.exists()) {
        return 0;
    }

    QDirIterator ite(dirPath, QDir::AllEntries|QDir::NoDotAndDotDot);
    while(ite.hasNext()) {
        ite.next();
        QFileInfo fileInfo = ite.fileInfo();
        if(fileInfo.isDir()) {
            size += calSize(ite.filePath());
        } else if(fileInfo.isFile()) {
            size += fileInfo.size();
        }
    }

    return size;
}

#endif // OTHER_HPP

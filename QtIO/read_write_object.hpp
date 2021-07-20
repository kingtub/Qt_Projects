#ifndef READ_WRITE_OBJECT_HPP
#define READ_WRITE_OBJECT_HPP

#include<QString>
#include<QFile>
#include<iostream>
#include<QDataStream>
#include<QMap>

namespace read_write_object {
    void saveObj(const QString &fileName)
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly)) {
            std::cerr<<qPrintable(fileName)<<":file can not open!"<<std::endl;
            return;
        }
        QDataStream ds(&file);
        ds.setVersion(QDataStream::Qt_5_9);
        QMap<QString, int> map;
        map.insert("Hello", 3);
        map.insert("Well", 5);
        map.insert("Kate", 10);
        quint32 j = 15;
        ds<<quint32(0x12345678)<<map<<j;
        // 我们不必明确地关闭这个文件，因为当QFile变量离开它的作用域时，文件会自动关闭。
        // 如果想检验数据是否被真正写入，可以调用flush()并检查其返回值（若返回值为true，则表示成功写入数据）。
    }

    void readObj(const QString &fileName) {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)) {
            std::cerr<<qPrintable(fileName)<<":file can not open!"<<std::endl;
            return;
        }
        QDataStream ds(&file);
        ds.setVersion(QDataStream::Qt_5_9);
        quint32 magic;
        QMap<QString, int> m;
        quint32 j;
        ds >> magic;
        if(magic != quint32(0x12345678)) {
            std::cerr<<"Not my file!"<<std::endl;
            return;
        }
        ds >> m >> j;
        QMapIterator<QString, int> ite(m);
        while(ite.hasNext()) {
            ite.next();
            std::cerr<<"key="<<ite.key().toStdString()<<", value="<<ite.value()<<std::endl;
        }
        std::cerr<<"j is "<<j<<std::endl;
    }

    //如果想一次读取或者写入一个文件，可以完全不用QDataStream而使用QIODevice的write()和readAll()函数。
    // 例如：
    bool copy_file(const QString &infile, const QString &outfile) {
        QFile fin(infile);
        if(!fin.open(QIODevice::ReadOnly)) {
            std::cerr<<"Can not open file:"<<qPrintable(infile)<<std::endl;
            return false;
        }

        QFile fout(outfile);
        if(!fout.open(QIODevice::WriteOnly)) {
            std::cerr<<"Can not open file:"<<qPrintable(outfile)<<std::endl;
            return false;
        }
        fout.write(fin.readAll());
        return fin.error() == QFile::NoError && fout.error() == QFile::NoError;
    }
}
#endif // READ_WRITE_OBJECT_HPP

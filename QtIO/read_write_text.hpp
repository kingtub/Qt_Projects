#ifndef READ_WRITE_TEXT_HPP
#define READ_WRITE_TEXT_HPP
#include<QString>
#include<QFile>
#include<iostream>
#include<QTextStream>
namespace read_write_text {
    // QTextStream使用16位QChar类型基本数据单元。除了字符和字符串之外，QTextStream还支持C++基本数字类型，
    // 它可以进行基本数字类型和字符串之间的转换。
    void read_text(const QString &filename) {
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            std::cerr<<"Can not open file"<<std::endl;
            return;
        }
        QTextStream in(&file);
        in.setCodec("utf-8");
        std::cerr<<"Readed:"<<qPrintable(in.readAll())<<std::endl;
    }

    bool write_text(const QString &filename) {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly)) {
            std::cerr<<"Can not open file"<<std::endl;
            return false;
        }
        QTextStream out(&file);
        out<<"annie are you ok, are you ok annie?"<<336;
        return true;
    }

    void read_text_by_line(const QString &filename) {
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            std::cerr<<"Can not open file"<<std::endl;
            return;
        }
        QTextStream in(&file);
        in.setCodec("utf-8");
        while(!in.atEnd()) {
            std::cerr<<qPrintable(in.readLine())<<std::endl;
        }
    }

    void read_text_by_char(const QString &filename) {
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)) {
            std::cerr<<"Can not open file"<<std::endl;
            return;
        }
        QString s;
        QTextStream in(&file);
        QChar c;
        while(!in.atEnd()) {
            in >> c;
            s.append(c);
        }
        std::cerr<<s.toStdString()<<std::endl;
    }
}
#endif // READ_WRITE_TEXT_HPP

#ifndef DO_JSON_HPP
#define DO_JSON_HPP
#include<QByteArray>
#include<QString>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonValue>
#include<QJsonParseError>
#include<iostream>

void testJson(const char *str) {
    QByteArray ba(str);
    QJsonParseError parserError;
    QJsonDocument jdoc = QJsonDocument::fromJson(ba, &parserError);
    if(jdoc.isNull()) {
        std::cerr<<parserError.errorString().toStdString()<<std::endl;
    } else if(jdoc.isObject()) {
        QJsonObject obj = jdoc.object();
        QJsonObject::const_iterator begin = obj.constBegin();
        QJsonObject::const_iterator end = obj.constEnd();
        while(begin != end) {
            std::cerr<<begin.key().toStdString()<<" : "
                    <<begin.value().toString().toStdString()<<std::endl;
            begin++;
        }
    } else if(jdoc.isArray()) {
        QJsonArray arr = jdoc.array();
        int count = arr.size();
        for(int i = 0; i < count; i++) {
            QJsonValue value = arr.at(i);
            if(value.isObject()) {
                QJsonObject obj = value.toObject();
                QJsonObject::const_iterator begin = obj.constBegin();
                QJsonObject::const_iterator end = obj.constEnd();
                while(begin != end) {
                    std::cerr<<begin.key().toStdString()<<" : "
                            <<begin.value().toInt()<<std::endl;
                    begin++;
                }
            }
        }
    }
}

#endif // DO_JSON_HPP

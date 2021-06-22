#include <QCoreApplication>
#include<iostream>
#include "read_write_object.hpp"
#include "read_write_text.hpp"
#include "other.hpp"
#include "do_json.hpp"

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //test1();
    //test2();

    //test3();
    //test4();

    //test5();
    //test6();

    //test7();

    test8();

    return a.exec();
}

void test1()
{
    read_write_object::saveObj("data.d");
    read_write_object::readObj("data.d");
}

void test2()
{
    if(read_write_object::copy_file("read_write_object.hpp", "read_write_object.hpp.copy")) {
        std::cout<<"Copy ok"<<std::endl;
    } else {
        std::cout<<"Copy not ok"<<std::endl;
    }
}

void test3()
{
    read_write_text::read_text("read_write_text.hpp");
}

void test4()
{
    read_write_text::write_text("mygen.txt");
    read_write_text::read_text("mygen.txt");
}

void test5()
{
    read_write_text::read_text_by_line("read_write_text.hpp");
}

void test6()
{
    read_write_text::read_text_by_char("read_write_text.hpp");
}

void test7() {
    std::cerr<<"Size: "<<calSize("F:\Qt_SpreadSheet")<<std::endl;
}

void test8() {
    testJson("{\"name\": \"cxh\", \"sex\": \"1\"}");
    testJson("[{\"azimuth_angle\":79,\"distance\":124,\"intensity\":35},{\"azimuth_angle\":267,\"distance\":239,\"intensity\":53}]");
}

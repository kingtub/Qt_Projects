#include <QCoreApplication>
#include"qvector_u.hpp"
#include"qlist_u.hpp"
#include"qmap_u.hpp"
#include"qalgorithms.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qvector_u::hello1();
    qlist_u::hello1();
    qlist_u::hello2();

    qmap_u::he();

    qalgorithms::hello();
    return a.exec();
}

#ifndef QMAP_U_HPP
#define QMAP_U_HPP
#include<QMap>
#include<QString>
using namespace std;
namespace qmap_u
{
    void he() {
        QMap<QString, int> map1;
        map1.insert("hello", 1);
        map1.insert("good", 2);
        map1.insert("ert", 3);

        QMap<QString, int> map2;
        map2["hello"] = 1;
        map2["good"] = 2;
        map2["ert"] = 3;

        QList<QString> ks = map1.keys();
        QList<int> vs = map1.values();

        QMapIterator<QString, int> i(map2);
        while(i.hasNext()) {
            i.next();
            cout<<"key="<<i.key().toStdString()<<", value="<<i.value()<<endl;
        }

        QMutableMapIterator<QString, int> mi(map1);
    }
}
#endif // QMAP_U_HPP

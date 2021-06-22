#ifndef QLIST_U_HPP
#define QLIST_U_HPP
#include<iostream>
#include<QList>
using namespace std;
namespace qlist_u
{
    void hello1()
    {
        cout<<"-----------hello1 start--------"<<endl;
        QList<double> list;
        list << 3.14159<<1.414<<1.732;

        QListIterator<double> iterator(list);
        while(iterator.hasNext()) {
            cout<< iterator.next()<<endl;
        }

        QListIterator<double> i2(list);
        i2.toBack();
        while(i2.hasPrevious()) {
            cout<<i2.previous()<<endl;
        }

        auto b = list.begin();
        auto e = list.end();
        while(b != e) {
            cout<<*b<<endl;
            b++;
        }

        cout<<"-----------hello1 end--------"<<endl;
    }

    void hello2()
    {
        cout<<"-----------hello2 start----------"<<endl;
        QList<double> list, second;
        list << 3.14159<<-1.414<<-1.732<<5<<10;
        second << 3.14159<<-1.414<<-1.732<<5<<10;

        QMutableListIterator<double> r1(list), r2(second);
        while (r1.hasNext()) {
            if(r1.next() < 0.0) {
                // remove方法总是针对刚刚跳过的项。
                r1.remove();
            }
        }

        r2.toBack();
        while (r2.hasPrevious()) {
            if(r2.previous() < 0.0) {
                // remove方法总是针对刚刚跳过的项。
                r2.remove();
            }
        }



        QListIterator<double> iterator(list);
        while(iterator.hasNext()) {
            cout<< iterator.next()<<endl;
        }

        QListIterator<double> i2(second);
        i2.toBack();
        while(i2.hasPrevious()) {
            cout<<i2.previous()<<endl;
        }

        cout<<"-----------hello2 end----------"<<endl;
    }
}

#endif // QLIST_U_HPP

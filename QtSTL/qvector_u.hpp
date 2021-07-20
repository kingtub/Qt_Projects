#ifndef QVECTOR_U_HPP
#define QVECTOR_U_HPP

#include<QVector>
#include<iostream>
using namespace std;
namespace qvector_u {
    void hello1()
    {
        QVector<int> v1(3);
        v1[0] = 1;
        v1[1] = 2;
        v1[2] = 3;

        QVector<int> v2;
        v2.append(4);
        v2.append(5);
        v2.append(6);


        QVector<int> v3;
        v3 << 7 << 8 << 9;

        for(int i = 0; i < v1.size();i++) {
            cout<<v1[i]<<endl;
        }

        for(int i = 0; i < v2.size();i++) {
            cout<<v2[i]<<endl;
        }

        for(int i = 0; i < v3.size();i++) {
            cout<<v3[i]<<endl;
        }
        QVector<QVector<int>> vv;
    }
}


#endif // QVECTOR_U_HPP

#ifndef QALGORITHMS_HPP
#define QALGORITHMS_HPP
#include<QtAlgorithms>
#include<QStringList>
#include<iostream>
namespace qalgorithms {
    void hello()
    {
        QStringList sList;
        sList<<"Emma"<<"Karl"<<"James"<<"Marietie";
        QStringList::iterator i1 = qFind(sList.begin(), sList.end(), "Karl");
        QStringList::iterator i2 = qFind(sList.begin(), sList.end(), "rui");
        if(i1 != sList.end()) {
            cout<<"Found it"<<endl;
        } else {
            cout<<"Not Found"<<endl;
        }

        if(i2 != sList.end()) {
            cout<<"Found it"<<endl;
        } else {
            cout<<"Not Found"<<endl;
        }
    }
}

#endif // QALGORITHMS_HPP

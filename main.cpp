#include "DoubleLinkedList.h"


            int main()
            {
                DoubleLinkedList<int> myList({1,2,3,4,5});
                for(int i=6;i<=10;i++)
                    myList.addBack(i);

                std::cout<<myList<<std::endl;

                myList.removeFront();
                myList.removeBack();

                std::cout<<"After remove:"<<myList<<std::endl;

                DoubleLinkedList<int> temp=myList.filter([](int x)->bool
                                                {
                                                    return x%2==0;
                                                });
                std::cout<<"Filter:"<<temp<<std::endl;

                myList.forEach([](int& x)->void
                               {
                                   x=x%2;
                               });
                std::cout<<"ForEach:"<<myList<<std::endl;

                temp=myList.map([](const int& x)->int
                                {
                                   return 4+4*x;
                                });
                std::cout<<"Map:"<<temp<<std::endl;


                myList.clear();
                myList=DoubleLinkedList<int>({1,2,3,4,5});
                std::cout<<"After clear:"<<myList<<std::endl;

                for(DoubleLinkedList<int>::iterator it=myList.begin();it!=myList.end();++it)
                    *it=8;
                std::cout<<"After using non-constant iterators:"<<myList<<std::endl;

                 for(DoubleLinkedList<int>::const_iterator it=myList.cbegin();it!=myList.cend();++it)
                    std::cout<<*it<<'-';

                return 0;
            }

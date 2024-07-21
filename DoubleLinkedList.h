#ifndef DOUBLELINKEDLIST_H_INCLUDED
#define DOUBLELINKEDLIST_H_INCLUDED

#include <iostream>
#include <iterator>
#include <functional>
#include <exception>
#include <initializer_list>

            template<typename T>
            class DoubleLinkedList
            {
                struct Node
                {
                    Node* left;
                    Node* right;
                    T data;
                    Node():left(nullptr),right(nullptr),data(T()) {}
                    Node(Node* left,Node* right,const T& data):left(left),right(right),data(data) {}
                };

                Node* head;
                Node* tail;
                int length;

            public:
                class iterator:public std::iterator<std::bidirectional_iterator_tag,T>
                {
                    Node* node;
                public:
                    iterator(Node* node=nullptr):node(node) {}
                    iterator& operator++() {node=node->right;return *this;}
                    iterator operator++(int) {iterator temp=(*this);++(*this);return temp;}
                    iterator& operator--() {node=node->left;return *this;}
                    iterator& operator--(int) {iterator temp=(*this);--(*this);return temp;}
                    bool operator==(const iterator& temp) const {return node==temp.node;}
                    bool operator!=(const iterator& temp) const {return node!=temp.node;}
                    T& operator*() const {return node->data;}
                };


                class const_iterator:public std::iterator<std::bidirectional_iterator_tag,T>
                {
                    const Node* node;
                public:
                    const_iterator(const Node* node=nullptr):node(node) {}
                    const_iterator& operator++() {node=node->right;return *this;}
                    const_iterator operator++(int) {const_iterator temp = (*this);++(*this);}
                    const_iterator& operator--() {node=node->left;return *this;}
                    const_iterator& operator--(int) {const_iterator temp=(*this);--(*this);return temp;}
                    bool operator==(const const_iterator& other) const {return node==other.node;}
                    bool operator!=(const const_iterator& other) const {return node!=other.node;}
                    const T& operator*() const {return node->data;}
                };

                DoubleLinkedList();
                DoubleLinkedList(const std::initializer_list<T>&);
                DoubleLinkedList(const DoubleLinkedList<T>&);
                DoubleLinkedList(DoubleLinkedList<T>&&);
                DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>&);
                DoubleLinkedList<T>& operator=(DoubleLinkedList<T>&&);
                ~DoubleLinkedList();

                void addBack(const T&) noexcept;
                void addFront(const T&) noexcept;
                void removeBack() noexcept(false);
                void removeFront() noexcept(false);
                void clear() noexcept;

                void sort() noexcept;//
                void forEach(const std::function<void(T&)>&) noexcept;//
                DoubleLinkedList<T> filter(const std::function<bool(const T&)>&);//
                DoubleLinkedList<T> map(const std::function<T(const T&)>&);//

                inline int size() const noexcept {return length;}

                iterator begin() {return iterator(head);}
                iterator end() {return iterator(nullptr);}
                const_iterator cbegin() const {return const_iterator(head);}
                const_iterator cend() const {return const_iterator(nullptr);}

                template<typename Y>
                friend std::ostream& operator<<(std::ostream&,const DoubleLinkedList<Y>&);

            private:
                void copy(const DoubleLinkedList<T>&) noexcept;
                void move(DoubleLinkedList<T>&&) noexcept;
                void destroy() noexcept;
            };


            template<typename T>
            void DoubleLinkedList<T>::copy(const DoubleLinkedList<T>& other) noexcept
            {
                destroy();
                Node* temp=other.head;
                for(int i=1;i<=other.length();i++)
                {
                    addBack(temp->data);
                    temp=temp->right;
                }
            }


            template<typename T>
            void DoubleLinkedList<T>::destroy() noexcept
            {
                if(length!=0)
                {
                    while(head!=nullptr)
                    {
                        Node* temp=head;
                        head=head->right;
                        delete temp;
                        temp=nullptr;
                    }
                    tail=nullptr;
                    length=0;
                }
            }


            template<typename T>
            void DoubleLinkedList<T>::move(DoubleLinkedList<T>&& other) noexcept
            {
                destroy();
                head=other.head;
                tail=other.tail;
                length=other.length;

                other.tail=other.head=nullptr;
                other.length=0;
            }


            template<typename T>
            DoubleLinkedList<T>::DoubleLinkedList():head(nullptr),tail(nullptr),length(0) {}


            template<typename T>
            DoubleLinkedList<T>::DoubleLinkedList(const std::initializer_list<T>& other):DoubleLinkedList()
            {
                for(const auto& value:other)
                    addBack(value);
            }


            template<typename T>
            DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other):DoubleLinkedList()
            {
                copy(other);
            }


            template<typename T>
            DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>&& other):DoubleLinkedList()
            {
                move(std::move(other));
            }


            template<typename T>
            DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& other)
            {
                if(this!=&other)
                {
                    destroy();
                    copy(other);
                }
                return *this;
            }


            template<typename T>
            DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList<T>&& other)
            {
                if(this!=&other)
                {
                    destroy();
                    move(std::move(other));
                }
                return *this;
            }


            template<typename T>
            DoubleLinkedList<T>::~DoubleLinkedList()
            {
                destroy();
            }


            template<typename T>
            std::ostream& operator<<(std::ostream& output,const DoubleLinkedList<T>& other)
            {
                for(auto it=other.head;it!=nullptr;it=it->right)
                    output<<it->data<<"  ";
                return output;
            }


            template<typename T>
            void DoubleLinkedList<T>::addBack(const T& value) noexcept
            {
                Node* ptr=new Node(tail,nullptr,value);
                ++length;
                if(head==nullptr)
                    head=tail=ptr;
                else
                {
                    tail->right=ptr;
                    tail=ptr;
                }

            }


            template<typename T>
            void DoubleLinkedList<T>::addFront(const T& data) noexcept
            {
                Node* ptr=new Node(nullptr,head,data);
                if(size()==0)
                    head=tail=ptr;
                else
                {
                    head->left=ptr;
                    head=ptr;
                }
                ++length;
            }


            template<typename T>
            void DoubleLinkedList<T>::removeBack() noexcept(false)
            {
                if(size()==0)
                    throw std::runtime_error("List is empty!");

                Node* ptr=tail;
                --length;

                if(head==tail)
                    head=tail=nullptr;
                else
                {
                    tail=tail->left;
                    tail->right=nullptr;
                }

                ptr->left=nullptr;
                delete ptr;
                ptr=nullptr;
            }


            template<typename T>
            void DoubleLinkedList<T>::removeFront() noexcept(false)
            {
                if(size()==0)
                    throw std::runtime_error("List is empty!");

                Node* ptr=head;
                --length;

                if(head==tail)
                    head=tail=nullptr;
                else
                {
                    head=head->right;
                    head->left=nullptr;
                }

                ptr->right=nullptr;
                delete ptr;
                ptr=nullptr;
            }


            template<typename T>
            void DoubleLinkedList<T>::forEach(const std::function<void(T&)>& function) noexcept
            {
                for(Node* ptr=head;ptr!=nullptr;ptr=ptr->right)
                    function(ptr->data);
            }


            template<typename T>
            DoubleLinkedList<T> DoubleLinkedList<T>::filter(const std::function<bool(const T&)>& function)
            {
                DoubleLinkedList<T> result;
                for(Node* ptr=head;ptr!=nullptr;ptr=ptr->right)
                    if(function(ptr->data))
                        result.addBack(ptr->data);
                return result;
            }


            template<typename T>
            DoubleLinkedList<T> DoubleLinkedList<T>::map(const std::function<T(const T&)>& function)
            {
                DoubleLinkedList<T> result;
                for(Node* ptr=head;ptr!=nullptr;ptr=ptr->right)
                    result.addBack(function(ptr->data));
                return result;
            }


            template<typename T>
            void DoubleLinkedList<T>::clear() noexcept
            {
                destroy();
            }

















#endif // DOUBLELINKEDLIST_H_INCLUDED

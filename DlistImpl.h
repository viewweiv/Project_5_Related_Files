//
// Created by uvuuview on 2021/7/28.
//

#ifndef PROJECT_5_RELATED_FILES_DLISTIMPL_H
#define PROJECT_5_RELATED_FILES_DLISTIMPL_H

//tod
template <class T>
bool Dlist<T>::isEmpty() const{
    return (first==nullptr);
}

//tod
template <class T>
void Dlist<T>::insertFront(T *op){
    auto *node_inserted = new node;
    node_inserted->op = op;
    node_inserted->prev= nullptr;
    node_inserted->next=first;
    if (isEmpty()){
        first = node_inserted;
        last=first;
    } else{
        first->prev=node_inserted;
        first=node_inserted;
    }
}

//tod
template <class T>
void Dlist<T>::insertBack(T *op){
    auto *node_inserted = new node;
    node_inserted->op = op;
    node_inserted->prev = last;
    node_inserted->next = nullptr;
    if (isEmpty()){
        first = node_inserted;
        last=first;
    } else{
        last->next=node_inserted;
        last=node_inserted;
    }
}

//tod
template <class T>
T *Dlist<T>::removeFront(){
    if (isEmpty()){
        throw EmptyList();
    }
    T *op_removed = first->op;
    if (first==last){
        delete first;
        first= nullptr;
        last=first;
    } else{
        node *node_removed=first;
        first=first->next;
        first->prev= nullptr;
        delete node_removed;
    }
    return op_removed;
}

//tod
template <class T>
T *Dlist<T>::removeBack(){
    if (isEmpty()){
        throw EmptyList();
    }
    T *op_removed = last->op;
    if (first==last){
        delete last;
        last= nullptr;
        first=last;
    } else{
        node *node_removed=last;
        last=last->prev;
        last->next = nullptr;
        delete node_removed;
    }
    return op_removed;
}

//tod
template <class T>
void Dlist<T>::removeAll(){
    while (!isEmpty()){
        T* op = this->removeFront();
        delete op;
    }
}

//tod
template <class T>
void Dlist<T>::copyAll(const Dlist &l){
    if (!isEmpty()){
        removeAll();
    }
    if (l.first){
        node *l_node=l.first;
        while (l_node){
            T *op=new T(*l_node->op);
            insertBack(op);
            l_node=l_node->next;
        }
    }
}

//tod
template <class T> // constructor
Dlist<T>::Dlist(): first(nullptr), last(nullptr){}

//tod
template <class T>
Dlist<T>::Dlist(const Dlist &l): first(nullptr), last(nullptr){
    copyAll(l);
}             // copy constructor

//tod
template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l){
    if (this!=&l){
        removeAll();
        copyAll(l);
    }
    return *this;
}  // assignment operator

//tod
template <class T>
Dlist<T>::~Dlist(){
    removeAll();
}

#endif //PROJECT_5_RELATED_FILES_DLISTIMPL_H

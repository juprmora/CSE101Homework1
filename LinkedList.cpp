//
// Created by Juan-Fernando Prado Morales on 5/5/21.
//

#include "LinkedList.h"
#include <iostream>
#include <string>
template <class NodeType>
LinkedList<NodeType>::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->n = 0; //size
}

template <class NodeType>
LinkedList<NodeType>::LinkedList( const LinkedList<NodeType>& that){
    //create the new list
    Node<NodeType> *ptr = that.head;
    while (ptr != nullptr) {
        //instance of Node
        this->insert_back(ptr->data);
        ptr = ptr->next;
    }
}


template <class NodeType>
LinkedList<NodeType>::~LinkedList<NodeType>() {
    this->clear();
}

template <class NodeType>
LinkedList<NodeType> & LinkedList<NodeType>::operator=( const LinkedList<NodeType> &that) {
    if (this == &that) {
        return *this;
    }
    this->clear();
    //create the new list

    Node<NodeType> *ptr = that.head;

    while (ptr != nullptr ) {
        std::cout << "node copied" <<std::endl;
        //instance of Node

        this->insert_back(ptr->data);

        if (ptr->next == nullptr){
            ptr = nullptr;
        }
        else {
            ptr = ptr->next;
        }
    }
    return *this;

}

template <class NodeType>
int LinkedList<NodeType>::size(){
    return this->n;
}
template <class NodeType>
int LinkedList<NodeType>::size() const{
    return this->n;
}

template <class NodeType>
bool LinkedList<NodeType>::empty() {
    return this->n != 0;
}



template <class NodeType>
void LinkedList<NodeType>::insert_front(const NodeType &item) {
    Node<NodeType> *curr = new Node<NodeType>();
    curr->data = item;

    if (this->head != nullptr)
        this->head->prev = curr;

    curr->next = this->head;
    this->head = curr;

    if (this->tail == nullptr){
        this->tail = curr;
    }
    this->n++;
}
template <class NodeType>
void LinkedList<NodeType>::insert_front(Node< NodeType>* pos) {
    //Node<NodeType> *curr = new Node<NodeType>();
    //curr->data = item;

    if (this->head != nullptr)
        this->head->prev = pos;
        pos->prev = nullptr;
    pos->next = this->head;
    this->head = pos;

    if (this->tail == nullptr){
        this->tail = pos;
        pos->next = nullptr;
    }
    this->n++;
}

template <class NodeType>
void LinkedList<NodeType>::insert_back(Node< NodeType>* pos) {
    //Node<NodeType>* curr = new Node<NodeType>();
    //curr->data = item;
    if(this->tail != nullptr){
        this->tail->next = pos;
        pos->next = nullptr;
    }
    pos->prev = this->tail;
    this->tail = pos;
    if(this->head == nullptr){
        this->head = pos;
        pos->prev = nullptr;
    }
    this->n++;
}


template <class NodeType>
void LinkedList<NodeType>::insertFromPrev(Node<NodeType>* pos, Node<NodeType>* data){
    if(pos->prev == nullptr){
        this->head = data;
    }else{
        pos->prev->next = data;
    }
    data->next = pos;
    data->prev = pos->prev;
    pos->prev = data;
    this->n++;
}

template <class NodeType>
void LinkedList<NodeType>::insertFromPrev(ListIterator<NodeType>& pos, ListIterator<NodeType>& data){
    if(pos.v->prev == nullptr){
        this->head = data.v;
    }else{
        pos.v->prev->next = data.v;
    }
    data.v->next = pos.v;
    data.v->prev = pos.v->prev;
    pos.v->prev = data.v;

    this->n++;
}


template<class NodeType>
void LinkedList<NodeType>::insertFromNext(Node<NodeType>* pos, Node<NodeType>* data){
    if (pos->next == nullptr){
        this->tail = data;
    }else{
        pos->next->prev = data;
    }
    data->next = pos->next;
    data->prev = pos;
    pos->next = data;
    this->n++;
}

template<class NodeType>
void LinkedList<NodeType>::insertFromNext(ListIterator<NodeType>& pos, ListIterator<NodeType>& data){
    if (pos.v->next == nullptr){
        this->tail = data.v;
    }else{
        pos.v->next->prev = data.v;
    }
    data.v->next = pos.v->next;
    data.v->prev = pos.v;
    pos.v->next = data.v;
    this->n++;
}

template <class NodeType>
NodeType LinkedList<NodeType>::remove_front() {
    if(this->head != nullptr){
        NodeType returnable = this->head->data;
        Node<NodeType>* ptr = this->head->next;
        delete this->head;
        this->n--;

        this->head = ptr;
        if(this->head != nullptr){
            this->head->prev = nullptr;
        }
        if(this->n == 1){
            this->tail = this->head;
        }
        return returnable;
    }
}

template <class NodeType>
void LinkedList<NodeType>::erase(ListIterator<NodeType>& loc){
    if(this->head == this->tail){
        this->clear();
    }
    else{
        //more than one node

        //set next to prev
        if (loc.v->next != nullptr) {
            loc.v->next->prev = loc.v->prev;
        }else{
            loc.v->prev->next = nullptr;
            this->tail = loc.v->prev;
        }
        if (loc.v->prev != nullptr) {
            loc.v->prev->next = loc.v->next;
        }else{
            loc.v->next->prev = nullptr;
            this->head = loc.v->next;
        }

        delete loc.v;
        loc.v = nullptr;
        this->n--;

    }
}

template <class NodeType>
void LinkedList<NodeType>::insert_back(const NodeType &item) {
    Node<NodeType>* curr = new Node<NodeType>();
    curr->data = item;
    if(this->tail != nullptr){
        this->tail->next = curr;
    }
    curr->prev = this->tail;
    this->tail = curr;
    if(this->head == nullptr){
        this->head = curr;
    }
    this->n++;
}

template <class NodeType>
NodeType LinkedList<NodeType>::remove_back() {
    if (this->tail != nullptr) {
        NodeType returnable = this->tail->data;
        Node<NodeType> *ptr = this->tail->prev;
        delete this->tail;
        this->tail = ptr;
        this->tail->next = nullptr;
        this->n--;

        if (this->n == 1){
            this->head = this->tail;
        }
        return returnable;
    }
}


template<class NodeType>
void LinkedList<NodeType>::clear(){
    Node<NodeType>* next_save = nullptr;
    if (this->head != nullptr) {
        while (this->head->next != nullptr) {
            next_save = this->head->next;
            delete this->head;
            this->head = next_save;
        }
        delete this->head;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->n = 0;
}

template<class NodeType>
int LinkedList<NodeType>::contains(NodeType& item) {
    Node<NodeType>* curr = this->head;
    int counter = 0;
    while(curr != nullptr){
        if((*curr).data == item){
            counter++;
        }
        curr = (*curr).next;
    }
    return counter;
}

template<class NodeType>
Node<NodeType>* LinkedList<NodeType>::firstRef(NodeType& item) {
    Node<NodeType>* curr = this->head;
    while(curr != nullptr){
        if((*curr).data == item){
            return curr;
        }
        curr = (*curr).next;
    }
    return nullptr;
}

template<class NodeType>
int LinkedList<NodeType>::contains(const NodeType&  item) const {
    Node<NodeType>* curr = this->head;
    int counter = 0;
    while(curr != nullptr){
        if((*curr).data == item){
            counter++;
        }
        curr = (*curr).next;
    }
    return counter;
}

template <class NodeType>
Node<NodeType>* LinkedList<NodeType>::front(){
    return this->head;
}

template <class NodeType>
Node<NodeType>* LinkedList<NodeType>::back(){
    return this->tail;
}

template <class NodeType>
Node<NodeType>* LinkedList<NodeType>::pop_lol(Node<NodeType>* ptr){
    Node<NodeType>* next = ptr->next;
    Node<NodeType>* prev = ptr->prev;

    if(next != nullptr){
        next->prev = prev; // assign next->prev to prev
    }
    else{
        //if next is a nullptr, then ptr is the tail. so we must update the tail
        this->tail = prev;
    }

    if(prev != nullptr ){
        prev->next = next;
    }
    else{
        this->head = next;
    }
    this->n--;
    return ptr;

}


template <class NodeType>
void LinkedList<NodeType>::print(){
    Node<NodeType>* curr = this->head;
    std::cout << "LIST: ";
    while(curr != nullptr){
        std::cout << curr->data << curr->counter<<" ";
        curr = curr->next;
    }
    std::cout << std::endl;
}




template<class U>
LinkedList<U> list_union(const LinkedList <U> &u, const LinkedList <U> &v){

    LinkedList<U> combined = u;

    Node<U>* v_ptr = v.front();
    for (int i = 0; i < v.size(); i++){
        if (!(u.contains( v_ptr->data ))){
            combined.insert_back(v_ptr->data);
        }
        v_ptr = (*v_ptr).next;
    }
    return combined;
}



template<class U>
LinkedList<U> list_intersection(const LinkedList <U> &u, const LinkedList <U> &v){
    LinkedList<U> shared = LinkedList<U>();

    Node<U>* v_ptr = v.front();
    for (int i = 0; i < v.size(); i++){
        if (u.contains( v_ptr->data)){
            shared.insert_back(v_ptr->data);
        }
        v_ptr = v_ptr->next;
    }
    return shared;
}


template<class U>
LinkedList<U> list_pop(const LinkedList <U> &u,  LinkedList <U> &v){
    LinkedList<U> shared = LinkedList<U>();

    Node<U>* v_ptr = v.front();
    Node<U> *temp;
    while(v_ptr != nullptr){
        if (u.contains( v_ptr->data)){
            shared.insert_back(v_ptr->data);
            if(v_ptr->next != nullptr and v_ptr->prev != nullptr){
                v_ptr->next->prev = v_ptr->prev;
                v_ptr->prev->next = v_ptr->next;
            }
            else if(v_ptr->prev != nullptr) {
                v_ptr->prev->next = nullptr;
            }
            else if(v_ptr->next != nullptr) {
                v_ptr->next->prev = nullptr;
            }

            if (v_ptr->next != nullptr) {
                temp = v_ptr->next;
            }
            else{
                temp = nullptr;
            }
            v_ptr = temp;
            v.n--;

        }else {
            v_ptr = v_ptr->next;
        }
    }
    return shared;
}


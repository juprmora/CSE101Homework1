//
// Created by Juan-Fernando Prado Morales on 5/5/21.
//

#ifndef ASSGMT5_LINKEDLIST_H
#define ASSGMT5_LINKEDLIST_H


template <class NodeType >
struct Node{
    NodeType data;
    Node<NodeType>* next = nullptr;
    Node<NodeType>* prev = nullptr;
    int counter = 1;
};


template <class NodeType>
class ListIterator {
public:
    NodeType& operator*();
    bool operator==(const ListIterator<NodeType>& p) const;
    bool operator!= (const ListIterator<NodeType>& p) const;
    bool operator< (const ListIterator<NodeType>& p) const;
    ListIterator<NodeType>& operator ++();
    ListIterator<NodeType>& operator --();
    friend class NodeList;
    Node<NodeType>* v;
    ListIterator<NodeType>(Node<NodeType>* u);
};


template <class NodeType >
class LinkedList {
    public:
        //copy constructor and assignment
        LinkedList();
        LinkedList <NodeType> (const LinkedList <NodeType>& that);
        LinkedList <NodeType>& operator=( const LinkedList <NodeType >& that);
        virtual ~LinkedList(); //delete all nodes
        int size (); // return node count
        int size() const;
        bool empty (); // check if empty
        void insert_front(const NodeType& item);
        void insert_front(Node <NodeType>* pos);
        NodeType remove_front ();
        void insert_back(const NodeType& item);
        void insert_back(Node<NodeType>* pos);

        NodeType remove_back ();
        void clear (); // remove all nodes
        Node<NodeType>* front();
        Node<NodeType>* pop_lol(Node<NodeType>* ptr);
        Node<NodeType>* back();
        int contains(NodeType& item);
        int contains(const NodeType& item) const ;
        Node<NodeType>* firstRef(NodeType& item);
        void erase(ListIterator<NodeType>& loc);
        void insertFromPrev(Node<NodeType>* pos, Node<NodeType>* data);
        void insertFromNext(Node<NodeType>* pos, Node<NodeType>* data);
        void insertFromPrev(ListIterator<NodeType>& pos, ListIterator<NodeType>& data);
        void insertFromNext(ListIterator<NodeType>& pos, ListIterator<NodeType>& data);
        void print();

        //friend class StackList<NodeType>;
        template<class U>
        friend LinkedList<U> list_union(const LinkedList<U>& u, const LinkedList<U>& v);
        template<class U>
        friend LinkedList<U> list_intersection(const LinkedList<U>& u,  const LinkedList<U>& v);
        template<class U>
        friend LinkedList<U> list_pop(const LinkedList<U>& u,  LinkedList<U>& v);
        //
// construct an empty list


    private:
        Node<NodeType> *head = nullptr;
        Node<NodeType> *tail = nullptr;
        int n = 0;
        // optional tail , useful for back
};


#endif //ASSGMT5_LINKEDLIST_H

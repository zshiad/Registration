#ifndef DOUBLYLINKEDLIST
#define DOUBLYLINKEDLIST
#include <iostream>
using namespace std;
//the iterator not very convenient when use it in for loop
//you will see in many for loop there is complex to check the when iterator
//goes to the end of the list
template <typename Item>
struct Node{
public:
  Item item;
  Node<Item>* next;
  Node<Item>* prev;
};

template <typename Item> 
class DoublyLinkedList {
private:
  Node<Item>* head;
  Node<Item>* rear;
  int _size;
  Node<Item>* sentinel;//use when empty
public: 
   DoublyLinkedList();         
   DoublyLinkedList(const DoublyLinkedList<Item>&); 
   DoublyLinkedList<Item>& operator=(const DoublyLinkedList<Item>&);
   ~DoublyLinkedList();
   
   int insertInorder(const Item&);//insert with order not just add. aot allow repeat
   int insertInorderallowrepeat(const Item&);
   //this one allow repeat. when repeat it will insert in front os all equal element  
   void addFirst(const Item&);   
   void addLast(const Item&);   
   Item removeFirst();         
   Item removeLast();  
   void setsize(int);
   
   Node<Item>* gethead()const;
   Node<Item>* getrear()const;
   Node<Item>* getsentinel()const;
   int size()const; 
   
   bool isEmpty()const;            
   void clear();

class Iterator{//Iterator of DoublyLinkedList
   friend class DoublyLinkedList<Item>;
public:
  Iterator();
  Iterator(Node<Item>* ptr,DoublyLinkedList<Item>*);
  Iterator(const Iterator&);
  ~Iterator();
  
  Node<Item>* getNoteptr()const;
  DoublyLinkedList<Item>* getlist()const;
  
  Iterator& operator=(const Iterator&);
  Iterator& operator++();
  Iterator operator++(int);
  Iterator& operator--();
  Iterator operator--(int);
  Iterator operator-(int);
  Iterator operator+(int);
  bool  operator==(const Iterator& )const;
  bool  operator!=(const Iterator& )const;
  Item& operator *();
  Node<Item>* operator-> ()const ;
  
  bool isDummy(); //point to nothing
  void setDummy(); //point to nothing
  void insert(const Item&);//use Iterator to insert
  void deletecurrent();//use Iterator to delete
private:
  Node<Item>* ptr; 
  Node<Item>* node;//avoid overflow
  DoublyLinkedList<Item>* list;
};
   Item* search(const Item&);//search item equal with input and return its reference
   void deletebyequal(const Item&);//delete all item equal with input
   Iterator begin();
   Iterator end();
   Iterator iterator(); //return an Iterator point to head
};



template <typename Item> 
DoublyLinkedList<Item>::DoublyLinkedList(){
  _size=0;
  Node<Item>* sentinel=new Node<Item>;
  sentinel->next=NULL;
  sentinel->prev=NULL;
  head=sentinel;
  rear=sentinel;
}

template <typename Item> 
DoublyLinkedList<Item>::DoublyLinkedList(const DoublyLinkedList<Item>& dll){
  _size=0;
  Node<Item>* sentinel=new Node<Item>;
  sentinel->next=NULL;
  sentinel->prev=NULL;
  head=sentinel;
  rear=sentinel;
  Node<Item>* dll_current=dll.gethead();
  for(int i=0;i<dll.size();i++){
    this->addLast(dll_current->item);
    dll_current=dll_current->next;
  }
}

template <typename Item> 
DoublyLinkedList<Item>& DoublyLinkedList<Item>::operator=(const DoublyLinkedList<Item>&dll){
  this->~DoublyLinkedList();
  _size=0;
  Node<Item>* sentinel=new Node<Item>;
  sentinel->next=NULL;
  sentinel->prev=NULL;
  head=sentinel;
  rear=sentinel;
  Node<Item>* dll_current=dll.gethead();
  for(int i=0;i<dll.size();i++){
    this->addLast(dll_current->item);
    dll_current=dll_current->next;
  }
  return *this;
}

template <typename Item> 
bool DoublyLinkedList<Item>::isEmpty()const{
  if(_size==0){
    //cout<<"the doublylinkedlist is empty"<<endl;
    return 1;
  }
  else{return 0;}
}

template <typename Item> 
int DoublyLinkedList<Item>::size()const{
  return _size;
}

template <typename Item> 
Node<Item>* DoublyLinkedList<Item>::gethead()const{
  return head;
}

template <typename Item> 
Node<Item>* DoublyLinkedList<Item>::getrear()const{
  return rear;
}

template <typename Item> 
Node<Item>* DoublyLinkedList<Item>::getsentinel()const{
  return sentinel;
}

template <typename Item> 
void DoublyLinkedList<Item>::addFirst(const Item& item){
  Node<Item>* newptr =new Node<Item>;
  newptr->item=item;
  if(_size==0){
     newptr->next=newptr;
     newptr->prev=newptr;
     head=newptr;
     rear=newptr;
  } 
  else{
  newptr->next=head;
  newptr->prev=rear;
  head->prev=newptr;
  rear->next=newptr;
  head=newptr;
  }
  _size++;
}

template <typename Item> 
void DoublyLinkedList<Item>::addLast(const Item& item){
  Node<Item>* newptr =new Node<Item>;
  newptr->item=item;
  if(_size==0){
     newptr->next=newptr;
     newptr->prev=newptr;
     head=newptr;
     rear=newptr;
  }
  else{
  newptr->next=head;
  newptr->prev=rear;
  head->prev=newptr;
  rear->next=newptr;
  rear=newptr;
  }
  _size++;
}

template <typename Item> 
Item DoublyLinkedList<Item>::removeFirst(){
  Item item;
  if(_size>=2){
  Node<Item>* newptr =head;
  item=head->item;
  (head->next)->prev=rear;
  head=head->next;
  rear->next=head;
  delete newptr;
  newptr=NULL;
  _size--;}
  else if(_size==1){
  Node<Item>* newptr =head;
  item=head->item;
  head=sentinel;
  rear=sentinel;
  delete newptr;
  newptr=NULL;
  _size--;
  }
  else{
    cout<<"the doublylinkedlist is empty"<<endl;
  }
  return item;
}

template <typename Item> 
Item DoublyLinkedList<Item>::removeLast(){
  Item item;
  if(_size>=2){
  Node<Item>* newptr =rear;
  item=rear->item;
  (rear->prev)->next=head;
  rear=rear->prev;
  head->prev=rear;
  delete newptr;
  newptr=NULL;
  _size--;}
  else if(_size==1){
  Node<Item>* newptr =rear;
  item=rear->item;
  head=sentinel;
  rear=sentinel;
  delete newptr;
  newptr=NULL;
  _size--;
  }
  else{
    cout<<"the doublylinkedlist is empty"<<endl;
  }
  return item;
}

template <typename Item>
typename DoublyLinkedList<Item>::Iterator DoublyLinkedList<Item>::iterator(){
  DoublyLinkedList<Item>::Iterator itr(head,this);
  return itr;
}

template <typename Item> 
DoublyLinkedList<Item>::~DoublyLinkedList(){
  while(_size>0){
    removeFirst();
  }
  head=NULL;
  rear=NULL;
  sentinel=NULL;
}

template <typename Item> 
int DoublyLinkedList<Item>::insertInorder(const Item& item){
  if(_size==0){
    addFirst(item);
    return 1;
  }
  else if((rear->item)<item){
   addLast(item);
   return 1; 
  }
  else if((head->item)>item){
   addFirst(item);
   return 1; 
  }
  else{
    Iterator itr=begin();
    for(;;++itr){
      if(*itr==item)
      {return 0;}
      else if(*itr>item){
	itr.insert(item);
	return 1;
      }  
    }
  }
}

template <typename Item> 
int DoublyLinkedList<Item>::insertInorderallowrepeat(const Item& item){
  if(_size==0){
    addFirst(item);
    return 1;
  }
  else if((rear->item)<item){
   addLast(item);
   return 1; 
  }
  else if((head->item)>item||(head->item)==item){
   addFirst(item);
   return 1; 
  }
  else{
    Iterator itr=begin();
    for(;;++itr){
      if(*itr>item||*itr==item){
	itr.insert(item);
	return 1;
      }  
    }
  }
}


template <typename Item> 
void DoublyLinkedList<Item>::clear(){
  while(_size>0){
    removeFirst();
  }
}

template <typename Item>
typename DoublyLinkedList<Item>::Iterator DoublyLinkedList<Item>::begin(){
  DoublyLinkedList<Item>::Iterator itr(head,this);
  return itr;
}

template <typename Item>
typename DoublyLinkedList<Item>::Iterator DoublyLinkedList<Item>::end(){
  DoublyLinkedList<Item>::Iterator itr(rear,this);
  return itr;
}

template <typename Item> 
void DoublyLinkedList<Item>::setsize(int i){
  _size=i;
}


template <typename Item>
DoublyLinkedList<Item>::Iterator::Iterator(){
  node=new Node<Item>;
  ptr=node;
}

template <typename Item> 
DoublyLinkedList<Item>::Iterator::Iterator(Node<Item>* ptr,DoublyLinkedList<Item>* list)
  :ptr(ptr),list(list){
    node=new Node<Item>;
}

template <typename Item>
DoublyLinkedList<Item>::Iterator::Iterator(const Iterator& iterator)
  :ptr(iterator.getNoteptr()),list(iterator.getlist()){
  node=new Node<Item>;
}
 
template <typename Item>
DoublyLinkedList<Item>::Iterator::~Iterator(){delete node;node=NULL;}

template <typename Item>
Node<Item>* DoublyLinkedList<Item>::Iterator::getNoteptr()const{return ptr;}

template <typename Item>
DoublyLinkedList<Item>* DoublyLinkedList<Item>::Iterator::getlist()const{
  return DoublyLinkedList<Item>::Iterator::list;  
}
  
template <typename Item>
typename DoublyLinkedList<Item>:: Iterator& DoublyLinkedList<Item>::Iterator::operator=(const Iterator& iterator){
  ptr=iterator.getNoteptr();
  list=iterator.getlist();
  return *this;
}
template <typename Item>
typename DoublyLinkedList<Item>::Iterator& DoublyLinkedList<Item>::Iterator::operator++(){
  if(!list->isEmpty()){ptr=ptr->next;}
  return *this;
}
template <typename Item>
typename DoublyLinkedList<Item>::Iterator DoublyLinkedList<Item>::Iterator::operator++(int){
  Iterator temp(ptr,list);
  if(!list->isEmpty()){ptr=ptr->next;}
  return temp;
}

template <typename Item>
typename DoublyLinkedList<Item>::Iterator& DoublyLinkedList<Item>::Iterator::operator--(){
  if(!list->isEmpty()){ptr=ptr->prev;}
  return *this;
}

template <typename Item>
typename DoublyLinkedList<Item>::Iterator DoublyLinkedList<Item>::Iterator::operator--(int){
  Iterator temp(ptr,list);
  if(!list->isEmpty()){ptr=ptr->prev;}
  return temp;
}

template <typename Item>
typename DoublyLinkedList<Item>::Iterator DoublyLinkedList<Item>::Iterator::operator-(int i){
  for(;i>0;i--){
    if(!list->isEmpty()){ptr=ptr->prev;}
  }
  return *this;
}

template <typename Item>
typename DoublyLinkedList<Item>::Iterator DoublyLinkedList<Item>::Iterator::operator+(int i){
  for(;i>0;i--){
    if(!list->isEmpty()){ptr=ptr->next;}
  }
  return *this;
}
  
template <typename Item>
void DoublyLinkedList<Item>::Iterator::insert(const Item& item){
  Node<Item>* newptr =new Node<Item>;
  newptr->item=item;
  newptr->next=ptr;
  newptr->prev=ptr->prev;
  ptr->prev=newptr;
  (newptr->prev)->next=newptr;
  list->setsize(list->size()+1);
}

template <typename Item>
void DoublyLinkedList<Item>::Iterator::deletecurrent(){
  if(list->size()>0){
    if(this->ptr==list->getsentinel()){
      cout<<"Try to delete sentinel"<<endl;
    }
    else if(list->size()>1){
      if(ptr==list->getrear()){
	ptr=ptr->prev;
	list->removeLast();
      }
      else if(ptr==list->gethead()){
	ptr=ptr->prev;
	list->removeFirst();
      }
      else{
	Node<Item>* temp=this->ptr;
	(ptr->prev)->next=temp->next;
	(ptr->next)->prev=temp->prev; 
	ptr=ptr->prev;
	list->setsize(list->size()-1);
	delete temp;
	temp=NULL;
      }
    }
    else{
      list->removeLast();
      this->ptr=list->getsentinel();
    }
  }
}

template <typename Item>
bool  DoublyLinkedList<Item>::Iterator::operator==(const Iterator& iterator)const{
  if(ptr==iterator.getNoteptr()){return 1;}
  else{return 0;}
}

template <typename Item>
bool  DoublyLinkedList<Item>::Iterator::operator!=(const Iterator& iterator)const{
  if(ptr==iterator.getNoteptr()){return 0;}
  else{return 1;}
}

template <typename Item>
Item& DoublyLinkedList<Item>::Iterator::operator *(){return ptr->item;}

template <typename Item>
Node<Item>* DoublyLinkedList<Item>::Iterator::operator-> ()const {return ptr;}

template <typename Item>
bool  DoublyLinkedList<Item>::Iterator::isDummy(){
  if(ptr==list->getsentinel()){
    ptr=list->gethead();
    return 1;}
  else{return 0;}
}

template <typename Item>
void  DoublyLinkedList<Item>::Iterator::setDummy(){
  ptr=list->getsentinel();
}

template <typename Item>
Item* DoublyLinkedList<Item>::search(const Item & item){
  typename DoublyLinkedList<Item>::Iterator itr;
  itr = this->begin();
  if (this->size()==1){
    if(*itr == item) {
        return &(*itr);
      }
  }
  else if(this->size()>1){
    for(;itr != this->end()&&itr.getNoteptr()!=sentinel ; ++itr) {
      if(*itr == item) {
        return &(*itr);
      }
    }
    if(*itr == item) {
        return &(*itr);
      }
  }
  return NULL;
}

template <typename Item>
void DoublyLinkedList<Item>::deletebyequal(const Item & item){
  typename DoublyLinkedList<Item>::Iterator itr;
  itr = this->begin();
  if(this->size()==1){
    if(*itr == item) {
        itr.deletecurrent();
    }
  }
  else if(this->size()>1){
    for(;itr != this->end()&&itr.getNoteptr()!=sentinel ; ++itr) {
      if(*itr == item) {
        itr.deletecurrent();
      }
    }
    if(*itr == item) {
        itr.deletecurrent();
      }
  }
}
#endif 


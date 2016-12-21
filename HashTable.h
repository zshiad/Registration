#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "DoublyLinkedList.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
// the hashtable has no iterator. So it need to improve.
template <typename T>
class HashTable {
private:
  int numbuckets, _size;
  vector<DoublyLinkedList<T> > buckets;//memory
  T eletype;//use to get hashtable type
  typename DoublyLinkedList<T>::Iterator searchbyIterator(const string&);
  //use doublelinkedlist Iterator to search
public:
  HashTable();
  ~HashTable();
  HashTable(int);//input is num of buckets

  int insert(const T&);
  int insertallowrepeat(const T&);
  int deleteByKey(const string&);//delete the first item equal with input
  int deleteall(const string&);//delete all items equal with input
  T* search(const string&);//search item use key and return its pointer
  DoublyLinkedList<T> searchall(const string&);
  //search all items use key and return its pointer
  void clear();
  bool isEmpty() const;
  int size() const;
  int num_buckets() const;
  T gettype() const;//get hashtable type
  DoublyLinkedList<T>* getbuckets(int);//get buckets[i] pointer
  void setsize(int);
  DoublyLinkedList<T> returnAll() ;//return all item
  void printAll();//use to print all item
};

template <typename T>
HashTable<T>::HashTable():numbuckets(0), _size(0),buckets(NULL){
}

template <typename T>
HashTable<T>::~HashTable() {}

template <typename T>
HashTable<T>::HashTable(int i): numbuckets(i), _size(0){
 buckets.resize(numbuckets);
}

template <typename T>
int HashTable<T>::insert(const T& item) {
  int index = T::Hash(item);
  int num = buckets[index].insertInorder(item);
  if(num >0) {
    _size++;
  }
  return num ;
}

template <typename T>
int HashTable<T>::insertallowrepeat(const T& item) {
  int index = T::Hash(item);
  int num = buckets[index].insertInorderallowrepeat(item);
  if(num >0) {
    _size++;
  }
  return num ;
}

template <typename T>
int HashTable<T>::deleteByKey(const string& str) {
  typename DoublyLinkedList<T>::Iterator itr;
  itr = searchbyIterator(str);
  if (itr.isDummy()) {
    return 0;
  }
  else{
    itr.deletecurrent();
    _size--;
    return 1;
  }
}

template <typename T>
T* HashTable<T>::search(const string& str) {
  typename DoublyLinkedList<T>::Iterator itr;
  itr = searchbyIterator(str);
  if(itr.isDummy()) {
    return NULL;
  }
  else {
    return &(*itr);
  }
}

template <typename T>
typename DoublyLinkedList<T>::Iterator HashTable<T>::searchbyIterator(const string& str) {
  int index = T::Hash(eletype, str);
  typename DoublyLinkedList<T>::Iterator itr;
  itr = buckets[index].begin();
  if((buckets[index].size()==1)){
    if(*itr == str) {
        return itr;
      }
  }
  else if((buckets[index].size()>1)){
    for(;itr != buckets[index].end()&&
      itr.getNoteptr()!=buckets[index].getsentinel(); ++itr) {
      if(*itr == str) {
        return itr;
      }
    }
    if(*itr == str) {
        return itr;
      }
  }
  itr.setDummy();
  return itr;
}

template <typename T>
void HashTable<T>::clear() {
  int i;
  for(i = 0;  i <  numbuckets; i++) {
    buckets[i].clear();
  }
  _size = 0;
}

template <typename T>
bool HashTable<T>::isEmpty() const {
  return _size == 0;
}

template <typename T>
int HashTable<T>::size() const {
  return _size;
}

template <typename T>
void HashTable<T>::setsize(int i){
  _size=i;
}

template <typename T>
T HashTable<T>::gettype() const {
  return eletype;
}

template <typename T>
DoublyLinkedList<T>* HashTable<T>::getbuckets(int i){
  return &(this->buckets[i]);
}

template <typename T>
int HashTable<T>::num_buckets() const {
  return numbuckets;
}

template <typename T>
DoublyLinkedList<T> HashTable<T>::returnAll()  {
  DoublyLinkedList<T> result;
  for(int i = 0; i <  numbuckets; i++) {
    typename DoublyLinkedList<T>::Iterator itr;
    if((buckets[i].size()>0)) {
      itr = buckets[i].begin();
      for (; itr != buckets[i].end()&&
	itr.getNoteptr()!=buckets[i].getsentinel(); ++itr) {
        result.insertInorder(*itr);
      }
      result.insertInorder(*itr);
    }
  }
  return result;
}

template <typename T>
DoublyLinkedList<T> HashTable<T>::searchall(const string& str) {
  DoublyLinkedList<T> result;
  int index = T::Hash(eletype, str);
  typename DoublyLinkedList<T>::Iterator itr;
  if((buckets[index].size()>0)){
    itr = buckets[index].begin();
  for(;itr != buckets[index].end()&&
    itr.getNoteptr()!=buckets[index].getsentinel(); ++itr) {
    if(*itr == str) {
      result.insertInorderallowrepeat((*itr));
    }
  }
    if(*itr == str) {
      result.insertInorderallowrepeat((*itr));
    }
  }
  return result;
}

template <typename T>
int HashTable<T>::deleteall(const string& str) {
  int index = T::Hash(eletype, str);
  typename DoublyLinkedList<T>::Iterator itr;
  if((buckets[index].size()>0)){
    itr = buckets[index].begin();
  for(; itr != buckets[index].end()&&
    itr.getNoteptr()!=buckets[index].getsentinel(); ++itr) {
    if(*itr == str) {
      itr.deletecurrent();
      _size--;
    }
  }
    if(*itr == str) {
      itr.deletecurrent();
      _size--;
    }
  }
  return 1;
}

template <typename T>
void HashTable<T>::printAll() {
  for(int i = 0; i  <  numbuckets; i++) {
    typename DoublyLinkedList<T>::Iterator itr;
    cout<< "numbuckets= "<<i<<": "<<endl;
    if((buckets[i].size()>0)) {
      itr = buckets[i].begin();
      for(; itr != buckets[i].end()&&
	itr.getNoteptr()!=buckets[i].getsentinel(); ++itr) {
        T::print(*itr);
      } 
      T::print(*itr);
      cout<<endl;
    }
  }
}

#endif



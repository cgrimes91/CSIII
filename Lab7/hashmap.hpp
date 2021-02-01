// implementation basic hashmap (unordered container)
// Chris Grimes
// 10/19/20

#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>
#include <iostream>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
   DefaultHash(size_t numBuckets = defaultNumBuckets);
   size_t hash(const T& key) const;
   size_t numBuckets() const { return numBuckets_; }
  void changeHash(size_t changed){numBuckets_=changed;}// used to rehash
  
private:
   // default number of buckets in the hash
   static const size_t defaultNumBuckets = 101; 
   size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets): numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
// note, this function does not work for C++ strings
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
   size_t res = 0;
   for (size_t i = 0; i < sizeof(key); ++i) {
      const unsigned char b = 
      *(reinterpret_cast<const unsigned char *>(&key) + i);
      res += b;
   }
   return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value, 
          typename Compare = std::equal_to<Key>,
          typename Hash = DefaultHash<Key>>
class hashmap{

public:
   typedef pair<const Key, Value> Element;

   // constructor
   // invokes constructors for comparison and hash objects
   hashmap(const Compare& comp = Compare(), 
	   const Hash& hash = Hash());

   Element* find(const Key& x);      // returns pointer to element with key x,
                                     // nullptr if not found
   std::pair <typename list<pair<const Key, Value>>::iterator, bool>  insert(const Element& x);    // inserts the key/value pair 
   std::pair <typename list<pair<const Key, Value>>::iterator, bool>  erase(const Key& x);         // erases element with key x, if exists
   Value& operator[] (const Key& x); // returns reference on value of
                                     // element with key, inserts if does not exist
  void rehash(size_t n);    //rehases provided n > than current numBuckets_
private:

   // helper function for various searches
   typename list<Element>::iterator findElement(const Key& x, const size_t bucket);

   size_t size_;   // number of elements in the container
   Compare comp_;  // comparison functor, equal_to by default
   Hash hash_;     // hash functor 

   // hash contents: vector of buckets
   // each bucket is a list containing key->value pairs
   vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
   hashmap<Key, Value, Compare, Hash>::hashmap(
   const Compare& comp, const Hash& hash):
   size_(0), comp_(comp), hash_(hash) {
      elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value, 
          typename Compare, typename Hash>
   typename list<pair<const Key, Value>>::iterator // return type
   hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket){

   // look for the key in the bucket
   for (auto it =  elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
      if (comp_(it->first, x))
	 return it;

   return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
   typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
   hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

   size_t bucket = hash_.hash(x);
   auto it=findElement(x, bucket);    // use the findElement() helper

   if (it != elems_[bucket].end()){
      // found the element. Return a pointer to it.
      return &(*it); // dereference the iterator to list 
   }               // then take the address of list element
   
   else // didn't find the element -- return nullptr
      return nullptr;
}


// finds the element with key x, inserts an
// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>
std::pair <typename list<pair<const Key, Value>>::iterator, bool>  hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {

   size_t bucket = hash_.hash(x.first);   
   auto it = findElement(x.first, bucket);    // try to find the element

   if(it != elems_[bucket].end()){//element is already present
     std::pair <typename list<pair<const Key, Value>>::iterator, bool> rtnval=std::make_pair(it, false);//returns iterator to existing element and a false bool
     return rtnval;
   }

   // if not found, insert a new one.
   else{
      ++size_;
      elems_[bucket].push_back(x);
      it= findElement(x.first, bucket);
      std::pair <typename list<pair<const Key, Value>>::iterator, bool> rtnval=std::make_pair(it, true);//returns iterator to new element and true bool
      return rtnval;
   } 
}


// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
std::pair <typename list<pair<const Key, Value>>::iterator, bool> hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {

   size_t bucket = hash_.hash(x);
   auto it = findElement(x, bucket);    // try to find the element
   if (it != elems_[bucket].end()) {    // the element exists, erase it
      it=elems_[bucket].erase(it);
      --size_;
      for(; bucket != hash_.numBuckets(); ++bucket){//for loop to decide the index of the vector
	for(it=elems_[bucket].begin(); it!= elems_[bucket].end();it++){//for loop to go through the linked list
	  if(it->first){//is there a key?
	    std::pair <typename list<pair<const Key, Value>>::iterator, bool> rtnval= std::make_pair(it, true);
	    return rtnval;
	  }
	}
      }
      it=elems_[bucket].end();
      std::pair <typename list<pair<const Key, Value>>::iterator, bool> rtnval=std::make_pair(it, true);//no successor found; iterator points to end of hashMap, bool is true
      return rtnval;
   }
   else{//element doesn't exist
     it=elems_[bucket].end();
     std::pair <typename list< pair<const Key, Value>>::iterator, bool> rtnval=std::make_pair(it, false);//iterator points to hashMap end, bool is false
       return rtnval;
     }
}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {

   Element* found = find(x);
   if (found == nullptr) { // if key not found, create new element with empty value
     std::pair <typename list<pair<const Key, Value>>::iterator, bool>  tmp= insert(make_pair(x, Value())); // calling default constructor on Value
     found = &(*tmp.first); //prevents second find()
   }
   return found->second;
}

// function to rehash provided n < numBuckets_    needs attention
template <typename Key, typename Value, typename Compare, typename Hash>
void hashmap< Key, Value, Compare, Hash>::rehash(size_t n){
  if(n <= hash_.numBuckets())//check to see if n < current hashing value
    return;
  else{
    vector<list<Element>> tmp(hash_.numBuckets());//temporary to hold elements while re-hash occurs
    int i=0; //tmp bucket tracker to fill
    for(size_t bucket=0; bucket != hash_.numBuckets(); ++bucket){//for loop to decide index of the vector
      int count=0;
      for(auto bucketIterator=elems_[bucket].begin(); count < elems_[bucket].size();){//for loop to go through linked list
	if(bucketIterator->first){//is there a key?
	  tmp[i].push_back(*bucketIterator);//put element in our tmp
	  bucketIterator=erase(bucketIterator->first).first;//erase old element and reassign iterator
	  ++count;//keeps track of linked list elements
	  }
	else{
	  bucketIterator++;//increments iterator when there is no key found
	  ++count;
	}
	}
      }
    elems_= vector<list<Element>>(n);//changes this's vector index size for rehash
    hash_.changeHash(n);//rehash
    for(auto myIterator=tmp[i].begin(); myIterator != tmp[i].end(); ++myIterator){//for loop to iterate through tmp
      insert(*myIterator);//reiserting elements
    }
  }
}

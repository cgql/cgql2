#pragma once

#include <type_traits>
#include <utility>

namespace cgql2 {

template<typename T>
class RAIIPtr {
public:
  RAIIPtr() = default;
  RAIIPtr(T* ptr) : ptr(ptr) {}
  ~RAIIPtr() {
    if(ptr) delete ptr;
  }

  RAIIPtr& operator=(T* ptr) { this->ptr = ptr; return *this; }
  T* operator->() const { return this->ptr; }
  T* get() const { return this->ptr; }
  typename std::add_lvalue_reference<T>::type operator*() const { return *this->ptr; }
private:
  T* ptr;
};

}

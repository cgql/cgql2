#pragma once

#include <utility>

namespace cgql2 {

template<typename T>
class Ptr {
public:
  Ptr() = default;
  Ptr(T* ptr) : ptr(ptr) {}
  Ptr(T value) : ptr(new T(value)) {}
  void assign(T value) {
    *this->ptr = value;
  }
  void assign(T* value) {
    this->ptr = value;
  }
  void destroy() const {
    if(ptr) delete ptr;
  }

  T* operator->() const { return this->ptr; }
  T* get() const { return this->ptr; }
private:
  T* ptr;
};

template<typename T, typename ... Args>
Ptr<T> makePtr(Args&& ... args) {
  Ptr<T> ptr(new T(std::forward<Args>(args)...));
  return ptr;
}

template<typename T>
class RAIIPtr : public Ptr<T> {
public:
  RAIIPtr(Ptr<T> ptr) {
    this->assign(ptr.get());
  }
  ~RAIIPtr() {
    this->destroy();
  }
};

}

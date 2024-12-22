#pragma once

#include <exception>
#include <iostream>

namespace bmstu {
template <typename T> class basic_string;

using string = basic_string<char>;
using u8string = basic_string<char8_t>;
using u16string = basic_string<char16_t>;
using u32string = basic_string<char32_t>;
using wstring = basic_string<wchar_t>;

template <typename T> class basic_string {
public:
  /// Конструктор по умолчанию
  basic_string(){
      size_ = 0;
      ptr_ = new T[1];
      ptr_[0] = 0;
  }

  basic_string(size_t size){
    size_ = size;
    ptr_ = new T[size_+1];
    for (size_t i = 0; i < size_; i++) {
      ptr_[i] = ' ';
    }
    ptr_[size_] = 0;
  }

  basic_string(std::initializer_list<T> il){
    size_ = il.size();
    ptr_ = new T[size_+1];
    size_t i = 0;
    for (auto obj : il) {
      ptr_[i] = obj;
      ++i;
    }
    ptr_[size_] = 0;
  }

  basic_string(const T* c_str) {
    size_ = strlen_(c_str);
    ptr_ = new T[size_ + 1];
    for (size_t i = 0; i < size_; ++i){
      ptr_[i] = c_str[i];
    }
    ptr_[size_] = 0;
  }

  basic_string(basic_string& other) {
    size_ = other.size();
    ptr_ = other.c_str();
    for (size_t i = 0; i < size_; ++i) {
      ptr_[i] = other.ptr_[i];
    }
    ptr_[size_] = 0;
  }

  basic_string(basic_string&& dying) {
    size_ = dying.size();
    ptr_ = dying.c_str();
    for (size_t i = 0; i < size_; ++i) {
      ptr_[i] = dying.ptr_[i];
    }
    ptr_[size_] = 0;
    dying.size_ = 0;
    dying.ptr_ = nullptr;
  }

  ~basic_string() {
    clean_();
  }

  T* c_str() const {
    if (ptr_ == nullptr) {
      return reinterpret_cast<const T*>("");
    } else {
      return ptr_;
    }
  }

  size_t size() const {
    return size_;
  }

  basic_string& operator=(basic_string&& dying) {
    if (this != &dying) {
      clean_();
      size_ = dying.size();
      ptr_ = new T[size_+1];
      for (size_t i = 0; i < size_; ++i) {
        ptr_[i] = dying.ptr_[i];
      }
      ptr_[size_] = 0;
      dying.size_ = 0;
      dying.ptr_ = nullptr;
    }
    return *this;
  }

  basic_string& operator=(const T* c_str) {
    while (c_str[size_] != 0) {
      size_++;
    }
    ptr_ = new T[size_+1];
    for (size_t i = 0; i < size_; ++i) {
      ptr_[i] = c_str[i];
    }
    ptr_[size_] = 0;
    return *this;
  }

  basic_string& operator=(basic_string& other) {
    if (this != &other) {
      clean_();
      size_ = other.size();
      ptr_ = new T[size_+1];
      for (size_t i = 0; i < size_; ++i) {
        ptr_[i] = other.ptr_[i];
      }
      ptr_[size_] = 0;
    }
    return *this;
  }

  friend basic_string<T> operator+(const basic_string<T>& left,
                                   const basic_string<T>& right) {
    basic_string<T> obj;
    obj.size_ = left.size() + right.size();
    obj.ptr_ = new T[obj.size()+1];
    for (size_t i = 0; i < left.size(); ++i) {
      obj.ptr_[i] = left.ptr_[i];
    }
    for (size_t i = 0; i < right.size(); ++i) {
      obj.ptr_[i+left.size()] = right.ptr_[i];
    }
    obj.ptr_[obj.size_] = 0;
    return obj;
  }

  template <typename S> friend S& operator<<(S& os, const basic_string& obj) {
    os << obj.c_str();
    return os;
  }

  template <typename S> friend S& operator>>(S& is, basic_string& obj) {
    is >> std::noskipws;
    T ch = 1;
    while (ch != 0) {
      ch = 0;
      is >> ch;
      if (ch != 0) {
        obj += ch;
      }
    }
    return is;
  }

  basic_string& operator+=(const basic_string& other) {
    size_ += other.size();
    T* prev_data = c_str();
    ptr_ = new T[size_+1];
    ptr_ = prev_data;
    for (size_t i = 0; i < other.size(); ++i) {
      ptr_[i+size_] = other.ptr_[i];
    }
    ptr_[size_] = 0;
    return *this;
  }

  basic_string& operator+=(T symbol) {
    size_++;
    T* prev_data = c_str();
    ptr_ = new T[size_+1];
    ptr_ = prev_data;
    ptr_[size_-1] = symbol;
    ptr_[size_] = 0;
    return *this;
  }

  T& operator[](size_t index) noexcept {
    return data()[index];
  }

  T& at(size_t index) {
    return data()[index];
  }

private:
  static size_t strlen_(const T* str) {
    size_t len_ = 0;
    while (str[len_] != 0) {
      len_++;
    }
    return len_;
  }

  void clean_() {
    size_ = 0;
    ptr_ = nullptr;
  }

  T* data() {
    return ptr_;
  }

  T* ptr_;
  size_t size_;
};
} // namespace bmstu
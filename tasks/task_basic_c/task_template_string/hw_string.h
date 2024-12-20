#pragma once
#include <iostream>

namespace bmstu {
template<typename T>
class basic_string;  /* объявляем класс */

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

template<typename T>
class basic_string {
private:
  size_t size_ = 0; /* переменная размера строки */
  T* data_ = nullptr; /* шаблон на динамический массив строки */

  /* Ищем длину */
  static size_t len_(const T* str) {
    size_t len = 0;
    while (str[len] != 0) {
      ++len;
    }
    return len;
  }

  /* Перегруженный поиск длины */
  static size_t len_(const basic_string& input) {
    return input.size_;
  }

  /* Очистка строки */
  void clean_() {
    size_ = 0;
    delete[] data_;
  }

  /* Трансляция данных */
  void copy_data_(const T* str) {
    for (size_t i = 0; i < len_(str); ++i) {
      data_[i] = str[i];
    }
    data_[size_] = 0;
  }

public:
  /* Шаблон-конструктор */
  basic_string() {
    size_ = 0;
    data_ = new T[1];
    data_[0] = 0;
  }

  /* Запрещаем неявное приведение типа */
  explicit basic_string(size_t size) {
    size_ = size;
    data_ = new T[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = ' ';
    }
    data_[size_] = 0;
  }

  /* На случай, когда строка задана так: {В, О, Р, О, Б, Е, Й} */
  basic_string(std::initializer_list<T> list) {
    size_ = list.size();
    data_ = new T[size_ + 1];
    size_t i = 0;
    for (auto& item : list) {
      data_[i] = item;
      ++i;
    }
    data_[size_] = 0;
  }

  /* Конструктор с параметром "cи строкой" */
  basic_string(const T* c_str) {
    size_ = len_(c_str);
    data_ = new T[size_ + 1];
    copy_data_(c_str);
  }

  /* Копирующий конструктор */
  basic_string(const basic_string& other) {
    size_ = other.size_;
    data_ = new T[size_ + 1];
    copy_data_(other.c_str());
  }

  /* Конструктор перемещения без исключений */
  basic_string(basic_string&& dying) noexcept {
    data_ = dying.data_;
    size_ = dying.size_;
    dying.data_ = nullptr;
    dying.size_ = 0;
  }

  /* Деструктор */
  ~basic_string() {
    clean_();
  }

  /* Геттер на си-строку, результат не игнорируется */
  [[nodiscard]] const T* c_str() const { /* Константный тип на константный объект */
    return (data_ != nullptr) ? data_ : reinterpret_cast<const T*>(""); /* Интерпретируем const char[1], передаваемый как (""), как последовательность бит типа const T* */
    /* Интерпретация в тип const T* нужна вот для чего:
     * изначально data_ объявлен как T*, а мы принимаем const char[1], поэтому и делаем интерпретацию
     * */
  }

  /* Геттер на размер */
  [[nodiscard]] size_t size() const {
    return size_;
  }

  /* Оператор копирующего присваивания
   * метод класса, который вызывается, когда одному уже существующему объекту
   * присваивается значение другого существующего объекта того же класса
   * возвращаем ссылку на объект типа basic_string
   * */
  basic_string& operator=(const basic_string& other) { /* Ключевое слово operator= обозначает оператор */
    /* other - ссылка на объект, значение которого будет присвоено текущему объекту
     * this - указатель, ссылающийся на текущий объект, для которого вызывается оператор копирования
     * */
    if (*this == other) {
      return *this;
    } else {
      clean_();
      size_ = other.size_;
      data_ = new T[size_ + 1];
      copy_data_(other.c_str());
      data_[size_] = 0;
      return *this;
    }
  }

  /* Оператор перемещающего присваивания
   * basic_string&& other - rvalue-ссылка на временный объект other
   * */
  basic_string& operator=(basic_string&& other) noexcept {
    if (this == &other) {
      return *this;
    } else {
      delete[] data_; /* Освобождаем старую data_ */
      size_ = other.size_;
      data_ = other.data_;
      other.data_ = nullptr;
      other.size_ = 0;
      return *this;
    }
  }

  /* Оператор присваивания C-строки */
  basic_string& operator=(const T* c_str) {
    clean_();
    size_ = len_(c_str);
    data_ = new T[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = c_str[i];
    }
    data_[size_] = 0;
    return *this;
  }

  /* Оператор конкатенации строк в новую строку
   * friend - обозначает, что функция operator+ является дружественной к классу basic_string,
   * это позволяет получать доступ к приватным полям объектов класса
   * */
  friend bmstu::basic_string<T> operator+(const basic_string& left,
                                          const basic_string& right) {
    basic_string result;
    result.size_ = left.size_ + right.size_;
    result.data_ = new T[result.size_ + 1];
    result.copy_data_(left.c_str());
    for (size_t i = 0; i < right.size_; ++i) {
      result.data_[i + left.size_] = right.data_[i];
    }
    return result;
  }

  /* Оператор вывода
   * возвращаем ссылку на поток вывода
   * std::basic_ostream<T>& - ссылка на объект шаблонного класса потока вывода
   * std::basic_ostream<T>& os - ссылка на поток вывода, в который будет выводиться строка
   * const basic_string& obj - константная ссылка на объект типа basic_string
   * */
  friend std::basic_ostream<T>& operator<<(std::basic_ostream<T>& os,
                                           const basic_string& obj) {
    os << obj.c_str();
    return os;
  }

  /* Оператор ввода */
  friend std::basic_istream<T>& operator>>(std::basic_istream<T>& is,
                                           basic_string& obj) {
    is >> std::noskipws;  /* считываем все начальные пробелы */
    T symbol = 1;
    /* Считываем символы из потока до тех пор, пока не кончится сам поток */
    for (size_t i = 0; symbol != 0; ++i) {
      symbol = 0; /* гарантируем, что поток будет вводиться, пока не будет встречен его конец */
      is >> symbol; /* изменили значение символа вводом из потока */
      if (symbol != 0) {
        obj += symbol;
      }
    }
    return is;
  }

  /* Оператор конкатенации строки и строки */
  basic_string& operator+=(const basic_string& other) {
    *this = (*this + other);
    return *this;
  }

  /* Оператор конкатенации строки и символа */
  basic_string& operator+=(const T symbol) {
    T* prev_data = data_;
    ++size_;
    data_ = new T[size_ + 1];
    copy_data_(prev_data);
    delete[] prev_data;
    data_[size_ - 1] = symbol;
    data_[size_] = 0;
    return *this;
  }

  /* Оператор равенства двух строк */
  bool operator==(const basic_string& input) const {
    if (input.size_ != size_) return false;
    if (input.data_ == data_) return true;
    for (size_t i = 0; i < input.size_; ++i) {
      if (data_[i] != input[i]) {
        return false;
      }
    }
    return true;
  }

  /* Значение по индексу
   * [] - оператор индексации
   * const означает, что оператор не может поменять данные объекта
   * */
  T& operator[](const size_t index) const {
    if (index <= size_) {
      return data_[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }
};
}
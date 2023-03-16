#include "string.hpp"

String::String() : size_(0), capacity_(0), string_(nullptr) {}

String::String(int size_str, char ctr)
    : size_(size_str),
      capacity_(size_str * 2),
      string_(new char[size_str * 2 + 1]) {
  for (int i = 0; i < size_str; ++i) {
    string_[i] = ctr;
  }
  string_[size_str] = '\0';
}

String::String(const char* character)
    : size_(strlen(character)),
      capacity_(size_),
      string_(new char[strlen(character) + 1]) {
  memcpy(string_, character, size_);
  string_[size_] = '\0';
}

String::String(const String& string_cp) {
  size_ = string_cp.size_;
  capacity_ = string_cp.capacity_;
  string_ = new char[capacity_ + 1];
  if (string_cp.string_ != nullptr) {
    memcpy(string_, string_cp.string_, size_ + 1);
  }
}

String::~String() { delete[] string_; }

String& String::operator=(const String& str_cp) {
  if (this == &str_cp) {
    return *this;
  }
  capacity_ = str_cp.capacity_;
  size_ = str_cp.size_;
  delete[] string_;
  string_ = new char[capacity_ + 1];
  if (str_cp.string_ == nullptr) {
    return *this;
  }
  std::memcpy(string_, str_cp.string_, capacity_ + 1);
  return *this;
}

void String::Clear() { size_ = 0; }

void String::PushBack(char ctr) {
  ++size_;
  if (size_ > capacity_) {
    Reserve(2 * size_);
  }
  string_[size_ - 1] = ctr;
  string_[size_] = '\0';
}

void String::PopBack() {
  if (Empty()) {
    return;
  }
  --size_;
  string_[size_] = '0';
}

void String::Resize(size_t new_size) {
  if (capacity_ >= new_size) {
    size_ = new_size;
  } else {
    Reserve(new_size);
  }
  if (new_size != 0) {
    string_[new_size] = '\0';
  }
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  if (new_size > capacity_) {
    Reserve(new_size);
  }
  if (new_size > size_) {
    for (size_t i = size_; i <= new_size; ++i) {
      string_[i] = character;
    }
  }
  size_ = new_size;
}

void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    capacity_ = new_cap;
    char* str_new = string_;
    string_ = new char[capacity_ + 1];
    if (str_new != nullptr) {
      memcpy(string_, str_new, size_);
    }
    delete[] str_new;
    string_[size_] = '\0';
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
  }
}

void String::Swap(String& other) {
  size_t temp1 = size_;
  size_t temp2 = capacity_;
  char* temp3 = string_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  string_ = other.string_;
  other.size_ = temp1;
  other.capacity_ = temp2;
  other.string_ = temp3;
}

const char& String::operator[](size_t index) const { return string_[index]; }

char& String::operator[](size_t index) { return string_[index]; }

char& String::Front() { return *string_; }
char& String::Back() { return *(string_ + size_ - 1); }

char String::Front() const { return *string_; }
char String::Back() const { return *(string_ + size_ - 1); }

bool String::Empty() const { return (size_ == 0); }
size_t String::Size() const { return size_; }
size_t String::Capacity() const { return capacity_; }
const char* String::Data() const { return string_; }
char* String::Data() { return string_; }

bool String::operator<(const String& str) const {
  if (size_ != str.size_) {
    return (size_ < str.size_);
  }
  for (size_t i = 0; i <= size_; ++i) {
    if (string_[i] < str[i]) {
      return true;
    }
    if (string_[i] > str[i]) {
      return false;
    }
  }
  return false;
}

bool String::operator>(const String& str) const { return (str < *this); }
bool String::operator<=(const String& str) const { return (!(*this > str)); }
bool String::operator>=(const String& str) const { return (!(*this < str)); }
bool String::operator==(const String& str) const { return (!(*this < str) && !(*this > str)); }
bool String::operator!=(const String& str) const { return (!(*this == str)); }

String& String::operator+=(const String& str) {
  if (capacity_ < str.size_ + size_) {
    Reserve(2 * (str.size_ + size_));
  }
  if (string_ == nullptr) {
    return *this;
  }
  memcpy(string_ + size_, str.string_, str.size_ + 1);
  size_ += str.size_;
  return *this;
}

String operator+(const String& str1, const String& str2) {
  String cpy = str1;
  cpy += str2;
  return cpy;
}

String operator*(const String& str, int n) {
  String temp = str;
  temp *= n;
  return temp;
}

String& String::operator*=(int n) {
  String temp = *this;
  int sizemult = size_;
  *this = "";
  Reserve(n * sizemult);
  for (int i = 0; i < n; ++i) {
    *this += temp;
  }
  return *this;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> res;
  size_t vit = 0;
  char* current = string_;
  String temp;
  while (current != nullptr) {
    int length = strstr(string_ + vit, delim.string_) - current;
    if (length == 0) {
      res.push_back("");
      vit += length + delim.size_;
      current += length + delim.size_;
      continue;
    }
    if (length < 0) {
      res.push_back(current);
      return res;
    }
    temp.Resize(length);
    memcpy(temp.string_, current, length);
    temp.string_[length] = '\0';
    vit += length + delim.size_;
    current += length + delim.size_;
    res.push_back(temp);
  }
  return res;
}

String String::Join(const std::vector<String>& strings) const {
  String res = "";
  if (!strings.empty()) {
    for (size_t i = 0; i < strings.size() - 1; ++i) {
      res += strings[i];
      res += *this;
    }
    return res += strings[strings.size() - 1];
  }
  return "";
}

std::ostream& operator<<(std::ostream& ost, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    ost << str.Data()[i];
  }
  return ost;
}

std::istream& operator>>(std::istream& ist, String& str) {
  char ctr;
  str.Clear();
  while (!(ist.eof()) && (ist.get(ctr))) {
    str.PushBack(ctr);
  }
  return ist;
}

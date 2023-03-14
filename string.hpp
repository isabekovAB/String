#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

class String {
 public:
  String();
  String(int, char);
  String(const char*);
  String(const String&);
  String& operator=(const String&);
  ~String();
  
  void Clear();
  void PushBack(char);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  
  const char& operator[](size_t) const;
  char& operator[](size_t);
  char& Front();
  char& Back();
  char Front() const;
  char Back() const;
  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  const char* Data() const;
  char* Data();

  bool operator<(const String&) const;
  bool operator>(const String&) const;
  bool operator<=(const String&) const;
  bool operator>=(const String&) const;
  bool operator==(const String&) const;
  bool operator!=(const String&) const;

  String& operator+=(const String&);
  String& operator*=(int);

  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>&) const;

 private:
  char* string_;
  size_t size_;
  size_t capacity_;
};

std::ostream& operator<<(std::ostream& ost, const String& str);
std::istream& operator>>(std::istream& is, String& str);

String operator+(const String&, const String&);
String operator*(const String&, int);

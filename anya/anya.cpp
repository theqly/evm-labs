#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class string{
 public:
  //конструктор
  string(size_t initial_capacity) {
    capacity = initial_capacity;
    memory = (char*)malloc(capacity);
    std::cout << "constructor" << std::endl;
  }

  /*string (const string & other_str){ //& это ссылочный тип, почти как указатель но подругому
    std::cout << "copy ctor!" << std::endl;
  }
  string & operator == (const string& other_str){
    std::cout << "operator" << std::endl;
  }*/

  //деструктор
  ~string() {
    free(memory);
    std::cout << "destructor" << std::endl;
  }

  void append(char c){
    if(size < capacity){
      memory[size] = c;
      size++;
    } else{
      memory = (char*)realloc(memory, capacity);
      capacity *= 2;
      memory[size] = c;
      size++;
    }
  }

  void show(){
    for(int i = 0; i < size; ++i){
      std::cout << memory[i];
    }
    std::cout << std::endl;
  }

  private:
    size_t capacity = 0;
    size_t size = 0;
    char* memory = nullptr;
};

int main(){

  string s1 = string(4);
  char c;
  for(int i = 0; i < 8; ++i){
    std::cin >> c;
    s1.append(c);
  }
  s1.show();
  return 0;
  /*string s(100500);
  string s2 = s;

  s.append('a');
  //приватная часть нам недоступна. не можем сказать что s.capacity = 200;, оно не скомпилируется
  string s3(10);
  s3 = s;*

  //??????????????
  // КНИГА - СУПЕРСЕКРЕТНАЯ ТЕХНОЛОГИЯ (не нужны истерически гуглить формы всяких школьников)
  // "язык программирования с++" Страуструп Б. 4ИЗД.еще методичка типа "краткий курс".на АНГЛИЙСКОМ
  // МЫ НЕ ИДИОТЫ, МЫ УМЕЕМ ЧИТАТЬ (ШКОЛЬНИКОВ НЕ СЛУШАТЬ) ШИЛ ЧИТАТЬ НЕ НАДО.*/
}
#include <iostream>

void Menu(); // prints menu 

int main() {
  Menu();

  return (0);
}

void Menu() {
  std::cout << "\n\n";
  std::cout << "l - Load From File" << std::endl;
  std::cout << "a - Add User" << std::endl;
  std::cout << "r - Remove User" << std::endl;
  std::cout << "c - Change User Password" << std::endl;
  std::cout << "f - Find User" << std::endl;
  std::cout << "d - Dump HashTable" << std::endl;
  std::cout << "s - HashTable Size" << std::endl;
  std::cout << "w - Write to Password File" << std::endl;
  std::cout << "x - Exit program" << std::endl;
  std::cout << "\nEnter choice : ";
}
#include <iostream>

std::string hexdecode(std::string);

int main(){
  std::string s1 = "a";
  std::cout << s1 << "\n";
  std::cout << hexdecode(s1);
  return 0;
}

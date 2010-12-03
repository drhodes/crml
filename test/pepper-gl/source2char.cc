#include <string>
#include <vector>
#include <iostream>
#include <cstring>

char** main(int argc, char** argv)
{
  // handy typedefs just to save some typing
  typedef std::vector<std::string> strvec_t;
  typedef std::vector<std::string>::iterator strveciter_t;

  strvec_t strvec;

  // fill the string vector with some sample strings
  strvec.push_back("Hello"); strvec.push_back(", ");
  strvec.push_back("world"); strvec.push_back("... ");
  strvec.push_back("How "); strvec.push_back("are ");
  strvec.push_back("you "); strvec.push_back("today");
  strvec.push_back("?");

  // print out the strings (just for sanity)
  for (strveciter_t ii=strvec.begin(); ii!=strvec.end(); ++ii)
    cout << *ii;
  cout << endl;

  // allocate memory for an array of character strings
  char** cstr = new char*[strvec.size()];

  // for each string, allocate memory in the character array and copy
  for (unsigned long i=0; i<strvec.size(); i++) {
    cstr[i] = new char[strvec[i].size()+1];
    strncpy(cstr[i], strvec[i].c_str(), strvec[i].size());
  }

  // print out the newly copied strings
  for (unsigned long i=0; i<strvec.size(); i++) cout << cstr[i];
  cout << endl;

  // free dynamic memory
  for (unsigned long i=0; i<strvec.size(); i++) delete[] cstr[i];
  delete[] cstr;

  return 0;
}

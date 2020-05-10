#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  ifstream myFile("myFile.txt");
  string uppercase;
  int charCount = 0;
  string lengthChecker = "";
  bool skip = false;
  
  for (string line; getline(myFile, line); ){    
    for (int i = 0; i <= line.length(); i++){
      
      // skip if non-alpha
      skip = false;
      if (isalpha(line[i]) == 0 && line[i] != ' '){
        skip = true;
      // if alhpa, uppercase and add to string
      } else if (lengthChecker.length() >= 10 && line[i] == ' ') {
        cout << lengthChecker << "\n";
        lengthChecker.erase();
      // else if space and <10, skip
      } else if (lengthChecker.length() < 10 && line[i] == ' ') {
        lengthChecker.erase();
      // if the length of string >= 10, display it
      } else if (skip == false){
        uppercase = toupper(line[i]);
        lengthChecker += uppercase;
      } 
    }
  }
}
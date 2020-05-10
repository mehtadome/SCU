#include <iostream>
#include <string>

using namespace std;

int main() {
  std::cout << "Hello World!\n";

  // Program 2
  string myString;
  bool isValid, isLength;
  isValid = false;
  isLength = false;
  

  // keep running program for as long as it is false
  while (isValid == false && isLength == false){
    // grab the input
    cout << "Enter a string of 10 digits (0-9) with no spaces: ";
    getline(cin, myString);

    // make sure that length is 10
    if (myString.length() != 10){
      cout << "Please enter ONLY 10 digits\n";
    } else {
      // correct length, check for spaces
      isLength = true;
      for (int i = 0; i <= myString.length(); i++){
        if (myString[i] == ' '){
          cout << "\nThere was a space!\n";
          // reset both checkers
          isValid = false;
          isLength = false;
          break;
        } 
        // no values were a space
        } else if (myString[myString.length()] != ' '){
          isValid = true;
        }
      }
    } // else end
    
  } // while end
  // Print string in reverse
  cout << "String in reverse: ";
  for (int i = myString.length(); i >= 0; i--){
    cout << myString[i];
  }
  cout << "\n";
  

}
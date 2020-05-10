// quite unsure how to use <random> for cpp so i used this link to get code 
//  for generating the number http://www.cplusplus.com/forum/beginner/98214/
// 
// The code after [...] is all mine

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int main() {

  cout << "I will guess your number between 1-20\n";
  bool isNum = false;
  string input;
  int count = 1;

  while (isNum == false){
    
    // This block I used to see how to work with a random num generator [...
    int randNum;
    srand(time(0));
    randNum = rand()%20+1; // random # from 1-20
    // ...]

    cout << "Is your number " << randNum << "? ";
    cout << "Enter Y/N please: ";
    getline(cin, input);

    // while will break if correct response given after an //    incorrect one
    while (input == "y" || input == "n" || input == "yes" ||   input == "no"){
      cout << "Please enter Y/N: ";
      getline(cin, input);
    }

    // correct response given
    if (input == "Y") {
      cout << "I got it in " << count << " tries! ";
      isNum = true;
    } else {
      count += 1;
      isNum = false;
    }
  }
}



#include <iostream>

using namespace std;

int main() {
  int alphCount, nonAlphCount;
  string input;

  alphCount = 0, nonAlphCount = 0;

  cout << "Enter anything: ";
  getline(cin, input);

  // loop and check if alph/not alph
  for (int i = 0; i < input.length(); i++){
    if (isalnum(input[i])){
      alphCount += 1;
    } else {
      nonAlphCount += 1;
    }
  }
  // print count values
  cout << "Alpha Numeric: " << alphCount << "\n";
  cout << "Non-Alpha Numeric: " << nonAlphCount << "\n";
}
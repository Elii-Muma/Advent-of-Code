#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <chrono>

/**@todo the issue right now is that everythin has to be done from right to left not left to right
 * for addition the numbers are actually left aligned
 * for multiplication the numbers are right aligned
 * if its mulitplication just get the last digit
 */

std::vector<long> processStringArr(std::vector<std::string> arr){

  std::vector<long> temp;
  int strLen = arr[0].length();

  while(strLen >= 0){
    int index = strLen - 1;
    std::string strNum{""};

    for(int i=0; i<arr.size(); i++){
      std::string currStr = arr[i];
      char c = currStr[index];

      if(std::isdigit(c)){
        strNum.push_back(c);
      }
    }

    if(!strNum.empty())
      temp.push_back(std::stol(strNum));
    strLen--;
  }

  return temp;
}

int main()
{

  auto startTimer = std::chrono::high_resolution_clock::now();

  std::ifstream inputFile;
  inputFile.open("../day_six/resources/input.txt");

  if (!inputFile.is_open())
  {
    std::cout << "FILE_FAILED_TO_OPEN\n";
    system("pause");
    return -1;
  }

  std::string inputLine;
  std::vector<std::string> input;
  int maxLineLen = 0; 

  while (std::getline(inputFile, inputLine))
  {
    std::cout << "LEN: " << inputLine.length() << "\n";
    if(maxLineLen < inputLine.length())
      maxLineLen = inputLine.length();

    input.push_back(inputLine);
  }

  std::vector<std::vector<std::string>> numbers;
  int numArrIndex{0}; //index of current array being accessed, increases when we're done with a set
  int numSpaces{0}; 
  bool isSpaceA{false}, isSpaceB{false}, isSpaceC{false}, isSpaceD{false};  

  for(int j=0; j<maxLineLen; j++){//MAX NUMBER OF CHARACTERS
    for(int i=0; i<input.size()-1; i++){ // the actual line
      //for each character we iterate over all the lines
      std::string currLineString = input[i];
      char c = currLineString[j];
      //i is also the current number in the inner array that we wabt to access
      //since the total number of "numbers" in an array is equal to the total number of rows in the input
      //expand outer array
      if(numArrIndex >= numbers.size())
        numbers.resize(numArrIndex + 1);

      //expand current inner array
      if(i >= numbers[numArrIndex].size())
        numbers[numArrIndex].resize(i + 1);

      std::vector<std::string> currArr = numbers[numArrIndex];
      std::string currNumStr = numbers[numArrIndex][i];

      //c is either a number or a space
      if(std::isdigit(c)){
        currNumStr.push_back(c);
      // }else if(c == ' ' && !currNumStr.empty() && checkForDigit(currNumStr)){
      //   numSpaces++;
      }else if(c == ' '){
        currNumStr.append("X");
        if(i == 0 && !isSpaceA) 
          isSpaceA = true;
        if(i == 1 && !isSpaceB) 
          isSpaceB = true;
        if(i == 2 && !isSpaceC) 
          isSpaceC = true;
        if(i == 3 && !isSpaceD) 
          isSpaceD = true;
      }
      // std::cout << "putting " << currNumStr << " in " << numArrIndex << "\n";
      numbers[numArrIndex][i] = currNumStr;
    }

    if(isSpaceA && isSpaceB && isSpaceC && isSpaceD ){
      numArrIndex++;
      isSpaceA = false;
      isSpaceB = false;
      isSpaceC = false;
      isSpaceD = false;
      //maybe add the operator too?
    }
  }

  //ADD OPERATORS
  std::vector<char> operators;
  for(auto c : input[input.size()-1]){ // the actual line
    if(c != ' ')
      operators.push_back(c);
  }



  long long finalResult{0};
  for (int i = 0; i < operators.size(); i++)
  {
    // std::cout<<"------OLD NUMBERS------\n";
    // for (auto num : numbers[i]){
    //   std::cout << "index [" << i << "] num:" << num << "\n";
    // }
    // std::cout << "operator[" << operators[i] << "]\n";

    std::vector<long> temp = processStringArr(numbers[i]);
    long long result = 0;
    switch (operators[i])
    {
    case '*':
      result = 1;
      // std::cout<<"------NEW NUMBERS------\n";
      for (auto n : temp){
        // std::cout << "index [" << i << "] num:" << n << "\n";
        result *= n;
      }
      finalResult += result;
      // std::cout<<"result: "<< result << "\n";
      // std::cout<<"------------\n\n";
      break;
    case '+':
      // std::cout<<"------NEW NUMBERS------\n";
      for (auto n : temp){
        // std::cout << "index [" << i << "] num:" << n << "\n";
        result += n;
      }
      finalResult += result;
      // std::cout<<"result: "<< result << "\n";
      // std::cout<<"------------\n\n";
      break;
    
    default:
      break;
    }
  }

  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;

  std::cout << "=============EXECUTION STATS================\n"
            << "FINAL RESULT: " << finalResult << "\n"
            << "EXECUTION TIME: " << elapsedTime.count() << "\n";

  system("pause");
  return 0;
}
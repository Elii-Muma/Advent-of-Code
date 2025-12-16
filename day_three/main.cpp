#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

int main()
{
  auto startTimer = std::chrono::high_resolution_clock::now();

  std::ifstream inputFile;
  inputFile.open("../resources/input.txt");
  if (!inputFile.is_open())
  {
    std::cerr << "ERR_OPENING_FILE\n";
    system("pause");
    return -1;
  }

  std::vector<std::string> finalDigits;
  std::string inputLine{""};
  long long sum{0};
  int inputNums{0};
  while (std::getline(inputFile, inputLine))
  {
    inputNums++;
    std::string tempMax{""};
    std::string finalNum{""};
    int freeStartPtr{0};
    int freeEndPtr{0};
    int safeStartPtr{0};
    int posIndex{0};
    try
    {
      std::cout << "\n================START========================= \n";
      std::cout << "line: " << inputLine << "\n";
      tempMax = inputLine[0];

      freeStartPtr = 0;
      safeStartPtr = inputLine.length() - 12;
      freeEndPtr = safeStartPtr;

      while(true)
      {
        //posindex is the position of the selected digit from the free side
        int index = posIndex;
        std::cout << "FROM_POSITION: " << posIndex << "\n";

        std::string currStr{inputLine[index]};
        std::cout<< "\nCURR STRING: " << currStr << "\n";
        std::cout<<"line length: " << inputLine.length() << "\n\n";

        long long curr = std::stoll(currStr);
        std::string free_side = inputLine.substr(index, safeStartPtr - index);
        std::string safe_side = inputLine.substr(safeStartPtr);
        std::cout << "FREE SIDE: [" << free_side << "] \n";
        std::cout << "SAFE SIDE: [" << safe_side << "] \n";

        if (finalNum.length() >= 12)
        {
          break;
        }
        for (int j = index + 1; j < freeEndPtr; j++)
        {
          std::string nxtStr{inputLine[j]};
          long long next = std::stoll(nxtStr);
          // FIND THE FIRST DIGIT BEFORE WE GET TO 12
          if (curr < next)
          {
            curr = next;
            tempMax = std::to_string(curr);
            posIndex = j+1;
          }
        }
        std::cout << "HIGH_NUM_ON_FREE_SIDE: " << curr << "\n"
                  << "<-POS: " << posIndex << "\n";
        // we have the highest number on free side
        // check if said highest number is > or < the first number on safe side
        std::string safeNumStr(1, inputLine[safeStartPtr]);
        std::cout << "safe string : " << inputLine[safeStartPtr] << "\n";
        long long safeNum = std::stoll(safeNumStr);

        std::cout << "TO_COMPARE: " << curr << " <c|s> " << safeNum << "<-"
                  << " | @_POS: " << safeStartPtr << "\n";

        if (curr >= safeNum)
        {
          std::cout << "\nCURR LARGER: " << curr << " <c|s> " << safeNum << "\n";
          finalNum += std::to_string(curr);
          std::cout << "append_to_finalNum: " << finalNum << "\n";
          safeStartPtr++;
          freeEndPtr = safeStartPtr;
          if(index == posIndex){
            posIndex++;
          }
          std::cout << "new_safe_ptr: " << safeStartPtr << "\n";
        }
        else if (curr < safeNum)
        {
          std::cout << "SAFE LARGER: " << curr << " <c|s> " << safeNum << "\n";
          finalNum += inputLine.substr(safeStartPtr);
          break;
        }
      }
      std::cout << "\nFINAL_NUM: " << finalNum << "\n";
      finalDigits.push_back(finalNum);
      sum += std::stoll(finalNum);
      std::cout << "\n================END======================= \n\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  std::cout << "\n================DIGITS======================= \n\n";
  for (std::string digit : finalDigits)
  {
    std::cout << digit << "\n";
  }
  std::cout << "\n|->FINAL SUM: " << sum << "\n";

  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;
  std::cout << "\n================EXECUTION STATS======================= \n\n";
  std::cout << "EXECUTION TIME: " << elapsedTime.count() << "\n"
            << "INPUT SIZE: " << inputNums << "\n";

  system("pause");
  return 0;
}
#include <iostream>
#include <utility>
#include <fstream>
#include <string>

int main()
{

  std::ifstream inputFile;
  inputFile.open("../day_three/resources/input.txt");
  if (!inputFile.is_open())
  {
    std::cerr << "ERR_OPENING_FILE\n";
    system("pause");
    return -1;
  }

  std::string inputLine{""};
  std::string tempMax{""};
  std::string firstNum{""}, secondNum{""};
  int sum{0};
  int posIndex{0};
  while (std::getline(inputFile, inputLine))
  {
    try
    {
      std::cout << "line: " << inputLine << "\n";
      tempMax = inputLine[0];
      for (int i = 0; i < inputLine.length(); i++)
      {
        std::string nxtStr{inputLine[i]};
        int curr = std::stoi(tempMax);
        int next = std::stoi(nxtStr);
        if (curr < next && i < inputLine.length() - 1)
        {
          std::cout<<"found higher num: " << curr << "|" << next <<"\n";
          std::cout <<"at pos: " << i << "\n";
          curr = next;
          tempMax = std::to_string(curr);
          posIndex = i;
        }
      }
      firstNum = tempMax;
      std::cout << "first highest number: " << firstNum << "\n";
      tempMax = inputLine[posIndex+1];
      std::cout<<"starting from position: " << posIndex+1 << "\n";
      for (int i = posIndex+1; i < inputLine.length(); i++)
      {
        std::string nxtStr{inputLine[i]};
        int curr = std::stoi(tempMax);
        int next = std::stoi(nxtStr);
        if (curr < next)
        {
          std::cout<<"found higher num: " << curr << "|" << next <<"\n";
          curr = next;
          tempMax = std::to_string(curr);
        }
      }
      secondNum = tempMax;
      std::string finalNum = firstNum + secondNum;
      sum += std::stoi(finalNum);
      std::cout << "final number: " << finalNum << "\n\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  std::cout << "\nFINAL SUM: " << sum << "\n";

  system("pause");
  return 0;
}
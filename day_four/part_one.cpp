#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

int main()
{

  auto startTimer = std::chrono::high_resolution_clock::now();

  std::ifstream inputFile;
  inputFile.open("../day_four/resources/test.txt");

  if (!inputFile.is_open())
  {
    std::cout << "FAILED_TO_OPEN_FILE\n";
    system("pause");
    return -1;
  }

  std::string inputLine;
  while (std::getline(inputFile, inputLine))
  {
    for (char c : inputLine){
      if (c == '@'){
        std::cout << "X";
      }else if (c == '.'){
        std::cout << "0";
      }
    }
    std::cout << "\n";
  }

  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;
  std::cout << "\n================EXECUTION STATS=================\n";
  std::cout << "ELAPSED TIME: " << elapsedTime.count() << "\n";
  std::cout << "\n================================================\n";

  system("pause");
  return 0;
}
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

int main()
{

  auto startTimer = std::chrono::high_resolution_clock::now();

  std::ifstream inputFile;
  inputFile.open("../day_five/resources/input.txt");

  if (!inputFile.is_open())
  {
    std::cout << "FILE_FAILED_TO_OPEN\n";
    system("pause");
    return -1;
  }

  std::string inputLine;
  std::vector<std::pair<long long, long long>> ranges;
  std::vector<std::pair<long long, bool>> inputs;
  std::vector<long long> freshIngredients;
  bool checkingRanges{true};
  int rowCount{0};
  while (std::getline(inputFile, inputLine)) {
    try {
      /* code */
      if (inputLine.empty()) {
        std::cout << "GRABBING INPUT NOW, size: ";
        std::cout << ranges.size() << "\n";
        system("pause");
        checkingRanges = false;
        continue;
      }

      if (checkingRanges) {
        for (int i = 0; i < inputLine.length(); i++) {
          std::pair<long long, long long> rangePair;
          if (inputLine[i] == '-') {
            int startIndex = i + 1;
            rangePair.first = std::stoll(inputLine.substr(0, startIndex));
            rangePair.second = std::stoll(inputLine.substr(startIndex));
            ranges.push_back(rangePair);
          }
        }
      }
      else {
        std::pair<long long, bool> in;
        in.first = std::stoll(inputLine);
        in.second = false;
        inputs.push_back(in);
      }
    }
    catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
      throw  std::exception(e);
      
    }
    rowCount++;
  }
  std::cout << "MOVING NOW, count: " << rowCount << " input size: ";
  std::cout << inputs.size() << "\n";
  std::cout << "\n============INPUT============\n";
  for (auto input : inputs){
    std::cout << input.first << "\n";
  }
  system("pause");

  std::cout << "\n============RANGES============\n";
  for (auto range : ranges)
  {
    std::cout << "range(" << range.first << "," << range.second << ")\n";
    for (int i = 0; i < inputs.size(); i++)
    {
      if ((inputs[i].first >= range.first && inputs[i].first <= range.second) && !inputs[i].second)
      {
        std::cout << "input[" << inputs[i].first << "] in range(" << range.first << "," << range.second << ")\n";
        freshIngredients.push_back(inputs[i].first);
        inputs[i].second = true;
        //inputs.erase(inputs.begin() + i);
      }
    }
  }


  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;

  std::cout << "\n\n====EXECUTION INFORMATION=====\n ";
  std::cout << "ELAPSED TIME: " << elapsedTime.count() << "\n"
            << "RANGE SIZE: " << ranges.size() << "\n"
            << "INPUT SIZE: " << inputs.size() << "\n"
            << "TOTAL RESULT: " << freshIngredients.size() << "\n";
  std::cout << "\n================================\n ";
  system("pause");
  return 0;
}
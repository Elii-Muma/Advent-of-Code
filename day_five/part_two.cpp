#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<long long, long long>> sortArr(std::vector<std::pair<long long, long long>> arr)
{

  std::cout << "SORTING...\n";
  for (int i = 0; i < arr.size()-1; i++)
  {
    bool swapped = false;
    for (int j = 0; j < arr.size()-i-1; j++)
    {
      long long currFirst = arr[j].first;
      long long currSecond = arr[j].second;

      long long nextFirst = arr[j+1].first;
      long long nextSecond = arr[j+1].second;

      if (currSecond > nextSecond || (currSecond == nextSecond && currFirst > nextFirst)) {
        std::swap(arr[j], arr[j+1]);
        swapped = true;
      }
    }
    if(!swapped)
      break;
  }

  std::cout << "SORTED ARR\n";
  for(auto range : arr){
    std::cout << "RANGE (" << range.first << "," << range.second << ")" << "\n";
  }
  return arr;
}

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
  std::vector<long long> freshIngredients;
  bool checkingRanges{true};
  while (std::getline(inputFile, inputLine)) {
    try {
      /* code */
      if (inputLine.empty()) {
        checkingRanges = false;
        break;
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
    }
    catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
      throw  std::exception(e);
      
    }
  }

  //sort by upperbound
  ranges = sortArr(ranges);

  
  std::cout << "\n============MODIFYING RANGES============\n";
  long long int totalFreshIngredients{0};
  long long highestValue = ranges[ranges.size()-1].second;
  for (int i = 0; i < ranges.size(); i++)
  {
    bool lowerModified = false;
    bool upperModified = false;
    bool isRemoved = false;
    for (int j = i; j < ranges.size(); j++)
    {
      if(j == i){
        continue;
      }
      long long lowerBound = ranges[i].first;
      long long upperBound = ranges[i].second;
      long long newLowerBound = ranges[j].first;
      long long newUpperBound = ranges[j].second;
      std::cout << "for old range(" << lowerBound << "," << upperBound << ")\n";

      // if(lowerBound == upperBound && (lowerBound >= newLowerBound && lowerBound <= newUpperBound)){
      //   // unsigned long long values = (ranges[i].second - ranges[i].first) + 1;
      //   // totalFreshIngredients -= values;
      //   std::cout << "RANGE (" << ranges[i].first << "," << ranges[i].second << ") has been removed " << "\n\n";
      //   ranges.erase(ranges.begin()+i);
      //   isRemoved = true;
      //   i--;
      //   continue;
      // }
      if((upperBound >= newLowerBound && upperBound <= newUpperBound) && (lowerBound >= newLowerBound && lowerBound <= newUpperBound)){
        // unsigned long long values = (ranges[i].second - ranges[i].first) + 1;
        // totalFreshIngredients -= values;
        std::cout << "RANGE (" << ranges[i].first << "," << ranges[i].second << ") has been removed " << "\n\n";
        ranges.erase(ranges.begin()+i);
        isRemoved = true;
        i--;
        continue;
      }

      if((lowerBound >= newLowerBound && lowerBound <= newUpperBound) && !lowerModified){
        std::cout << "lower input: [" << lowerBound << "] found in RANGE:(" << newLowerBound << "," << newUpperBound << ")\n";
        lowerBound = newUpperBound + 1;
        std::cout << "changing to: " << lowerBound<< "\n";
        ranges[i].first = lowerBound;
        // lowerModified = true;
      }
      if((upperBound >= newLowerBound && upperBound <= newUpperBound) && !upperModified){
        std::cout << "upper input: [" << upperBound << "] found in RANGE:(" << newLowerBound << "," << newUpperBound <<")\n";
        upperBound = newLowerBound - 1; 
        std::cout << "changing to: " << upperBound << "\n";
        if(ranges[i].first > upperBound){
          ranges[i].second = ranges[i].first;
          std::cout << "upper lower so changing to: " << ranges[i].first << "\n";
        }else{
          ranges[i].second = upperBound;
        }
        // upperModified = true;
      }
    }

    if(isRemoved)
      continue;
    std::cout << "new range :(" << ranges[i].first << "," << ranges[i].second << ")\n";
    unsigned long long values = (ranges[i].second - ranges[i].first) + 1;
    std::cout << "values in RANGE:(" << ranges[i].first << "," << ranges[i].second << ") = " << values << "\n\n";
    totalFreshIngredients += values;

    // sort
    if(i-1 > 0){
      if(ranges[i-1].second > ranges[i].second){
        std::swap(ranges[i-1], ranges[i]);
      }
    }
  }

  std::cout << "\n============RANGES============\n";
  for(auto range : ranges){
    std::cout << "(" << range.first << "," << range.second << ") \n";
  }


  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;

  std::cout << "\n\n====EXECUTION INFORMATION=====\n ";
  std::cout << "ELAPSED TIME: " << elapsedTime.count() << "\n"
            << "RANGE SIZE: " << ranges.size() << "\n"
            << "TOTAL RESULT: " << totalFreshIngredients << "\n";
  std::cout << "\n================================\n ";
  system("pause");
  return 0;
}
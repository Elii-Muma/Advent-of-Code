#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::pair<long long, long long>> sortArr(std::vector<std::pair<long long, long long>> arr)
{
  std::vector<std::pair<long long, long long>> sortedArr = arr;

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

      std::cout << "checking for: " << currSecond << "\n";
      if (currSecond > nextSecond | (currSecond == nextSecond && currFirst > nextSecond)) {
        std::cout << "swapping(" << currSecond << " AND " << nextSecond << ")\n";
        std::swap(arr[j], arr[j+1]);
        swapped = true;
      }
    }
    if(!swapped)
      break;
  }
  sortedArr = arr;
  return sortedArr;
}

int main()
{

  std::ifstream inputFile;
  inputFile.open("../day_five/resources/test.txt");

  if (!inputFile.is_open())
  {
    std::cout << "FILE_FAILED_TO_OPEN\n";
    system("pause");
    return -1;
  }

  std::string inputLine;
  std::vector<std::pair<long long, long long>> ranges;
  bool checkingRanges{true};
  while (std::getline(inputFile, inputLine))
  {
    try
    {
      if (inputLine.empty())
      {
        checkingRanges = false;
        break;
      }

      if (checkingRanges)
      {
        for (int i = 0; i < inputLine.length(); i++)
        {
          std::pair<long long, long long> rangePair;
          if (inputLine[i] == '-')
          {
            int startIndex = i + 1;
            rangePair.first = std::stoll(inputLine.substr(0, startIndex));
            rangePair.second = std::stoll(inputLine.substr(startIndex));
            ranges.push_back(rangePair);
          }
        }
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      throw std::exception(e);
    }
  }

  // sort by upperbound
  std::cout << "\n====BEFORE SORT====\n\n";
  for (auto range : ranges)
  {
    std::cout << "for old range(" << range.first << "," << range.second << ")\n";
  }
  ranges = sortArr(ranges);
  std::cout << "\n\n====AFTER SORT====\n";

  for (auto range : ranges)
  {
    std::cout << "for old range(" << range.first << "," << range.second << ")\n";
  }

  system("pause");
  return 0;
}
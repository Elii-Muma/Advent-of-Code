#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <chrono>
#include <algorithm>

/**@todo the issue right now is that everythin has to be done from right to left not left to right
 * for addition the numbers are actually left aligned
 * for multiplication the numbers are right aligned
 * if its mulitplication just get the last digit
 */

bool handleDuplicate(std::vector<std::pair<std::pair<int, bool>, long long>> &arr, int value, long long nPaths)
{
  auto it = std::find_if(arr.begin(), arr.end(), [value](const std::pair<std::pair<int, bool>, long long> &p)
                         { return p.first.first == value; });

  if (it != arr.end())
  {
    int index = std::distance(arr.begin(), it);
    long long numPaths = arr[index].second + nPaths;
    arr[index] = std::pair(std::pair(value, true), numPaths);
    return true;
  }
  return false;
}

int main()
{
  auto startTimer = std::chrono::high_resolution_clock::now();

  std::ifstream inputFile;
  inputFile.open("../day_seven/resources/input.txt");

  if (!inputFile.is_open())
  {
    std::cout << "FILE_FAILED_TO_OPEN\n";
    system("pause");
    return -1;
  }

  std::string inputLine;
  std::vector<std::pair<std::pair<int, bool>, long long>> beams;
  int startPosition{-1};
  int rowNum{0};

  while (std::getline(inputFile, inputLine))
  {
    // get le starting position
    // if its the first line i guess..we nab the starting position
    if (rowNum == 0)
      for (int i = 0; i < inputLine.length() - 1; i++)
      {
        char c = inputLine[i];

        if (c == 'S')
        {
          std::cout << "start pos: " << i << "\n";
          startPosition = i;
          beams.push_back(std::pair(std::pair(startPosition, true), 1));
          break;
        }
      }

    try
    {
      // we have an array of beams and we're iterating through it
      // beams are added gradually, so the array grows
      for (long long j = 0; j < beams.size(); j++)
      {
        std::pair currBeam = beams[j];          // a beam position in the array...or where its supposed to be
        bool &isActive = currBeam.first.second; // get the position for checking
        if (!isActive)
          continue;
        int beamPos = currBeam.first.first;     // get the position for checking
        long long numPaths = currBeam.second;
        char new_c = inputLine[beamPos]; // get the character thats at the position

        if (new_c == '.')
        {
          inputLine[beamPos] = '|';
        }
        else if (new_c == '^')
        {

          int leftPos = beamPos - 1;
          int rightPos = beamPos + 1;

          if (!handleDuplicate(beams, leftPos, numPaths))
          {
            beams.push_back(std::pair(std::pair(leftPos, true), 1));
          }

          if (!handleDuplicate(beams, rightPos, numPaths))
          {
            beams.push_back(std::pair(std::pair(rightPos, true), 1));
          }

          beams[j] = std::pair(std::pair(beamPos, false), 0); // kill the current beam
          inputLine[leftPos] = '|';
          inputLine[rightPos] = '|';

        }
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cout << "LINE: " << inputLine << "[" << beams.size() << "]\n";

    rowNum++;
  }

  long long totalPaths{0};
  for (auto pair : beams)
    if(pair.first.second){
      std::cout << "num of duplicates: " << pair.second << " at "<< pair.first.first << "\n";
      totalPaths+=pair.second;
    }



  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;

  std::cout << "=============EXECUTION STATS================\n"
            << "TOTAL POSSIBLE PATHS: " << totalPaths<< "\n"
            << "EXECUTION TIME: " << elapsedTime.count() << "\n";

  system("pause");
  return 0;
}
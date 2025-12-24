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

bool checkExists(std::vector<std::pair<int, bool>> arr, int value){

  auto it = std::find(arr.begin(), arr.end(), std::pair(value, true));
  if(it != arr.end()){
    int index = std::distance(arr.begin(), it);
    //std::cout << "value found at: " << index << "\n";
    return true;
  }
  return false;
}

int main()
{

  auto startTimer = std::chrono::high_resolution_clock::now();

  std::ifstream inputFile;
  inputFile.open("../day_seven/resources/test.txt");

  if (!inputFile.is_open())
  {
    std::cout << "FILE_FAILED_TO_OPEN\n";
    system("pause");
    return -1;
  }

  std::string inputLine;
  std::vector<std::pair<int, bool>> beams;
  int startPosition{-1};
  int rowNum{0};
  int numSplits{0};

  while (std::getline(inputFile, inputLine))
  {

    //get le starting position
    if(rowNum == 0)
      for(int i=0; i<inputLine.length()-1; i++){
        char c = inputLine[i];

        if(c == 'S'){
          std::cout << "start pos: " << i << "\n";
          startPosition = i;
          beams.push_back(std::pair(startPosition, true));
          break;
        }
      }

    for(int j=0; j<beams.size(); j++){
      std::pair currBeam = beams[j];
      int beamPos = currBeam.first;
      bool isBeamAlive= currBeam.second;

      char new_c = inputLine[beamPos];
      if(!isBeamAlive)
        continue;
      if(new_c == '.'){
        inputLine[beamPos] = '|';
        beamPos++;
      }else if(new_c == '^'){
        beams[j] = std::pair(beamPos, false); //kill the current beam
        
        int leftPos = beamPos - 1;
        int rightPos = beamPos + 1;
        if(!checkExists(beams, leftPos)){
          beams.push_back(std::pair(leftPos, true)); //kill the current beam
          inputLine[leftPos] = '|';
        }

        if(!checkExists(beams, rightPos)){
          beams.push_back(std::pair(rightPos, true)); //kill the current beam
          inputLine[rightPos] = '|';
        }
        numSplits += 1;
      }
    }
    std::cout << "LINE: " << inputLine << "["<< numSplits << "]\n";

    rowNum++;
  }

  int activeBeams{0};
  for(auto pair : beams)
    if(pair.second)
      activeBeams++;

  std::cout << "num of active Beams" << activeBeams << "\n";

  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;

  std::cout << "=============EXECUTION STATS================\n"
            << "TOTAL BEAM SPLITS: " << numSplits << "\n"
            << "EXECUTION TIME: " << elapsedTime.count() << "\n";

  system("pause");
  return 0;
}
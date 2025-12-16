#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>

int main()
{

  auto startTimer = std::chrono::high_resolution_clock::now();

  std::ifstream inputFile;
  inputFile.open("../day_four/resources/input.txt");

  if (!inputFile.is_open())
  {
    std::cout << "FAILED_TO_OPEN_FILE\n";
    system("pause");
    return -1;
  }

  std::string inputLine;
  int rowNum{0};
  int rows{150};
  int cols{100};

  std::vector<std::vector<char>> grid;
  while (std::getline(inputFile, inputLine))
  {
    //traverse the 2d grid
    std::vector<char> row;

    for (int col=0; col<inputLine.length(); col++){
      //check the 8 adjacent sides forj
      row.push_back(inputLine[col]);
    }
    grid.push_back(row);
  }

  int moveableBoxes{0};
  int newMoveableBoxes{-1};
  int index{0};
  bool isFirstPass{true};
  std::vector<std::vector<char>> newGrid;

  newGrid = grid;
  while(moveableBoxes != newMoveableBoxes){
    newMoveableBoxes = moveableBoxes;
    moveableBoxes = 0;
    index++;

    for(int row = 0; row<grid.size(); row++){
      for(int col = 0; col<grid[row].size(); col++){
        if( grid[row][col] == '.'){
          continue;
        }
        int boxesFound{0}; 
        // std::cout << "at: (" << row << ", " << col << ")\n";
        //check left
        if(col > 0){
          if(grid[row][col-1] == '@'){
            // std::cout << "found[l]: (" << row << ", " << col-1 << ")\n";
            boxesFound++;
          }
        }
        //check right
        if(col < grid[row].size()-1){
          if(grid[row][col+1] == '@'){
            // std::cout << "found[r]: (" << row << ", " << col+1 << ")\n";
            boxesFound++;
          }
        }
        //check up
        if(row > 0){
          if(grid[row-1][col] == '@'){
            // std::cout << "found[u]: (" << row-1 << ", " << col << ")\n";
            boxesFound++;
          }
        }
        //check down
        if(row < grid.size()-1){
          if(grid[row+1][col] == '@'){
            // std::cout << "found[d]: (" << row+1 << ", " << col << ")\n";
            boxesFound++;
          }
        }

        //check left and up
        if(col > 0 && row > 0){
          if(grid[row-1][col-1] == '@'){
            // std::cout << "found[l&u]: (" << row-1 << ", " << col-1 << ")\n";
            boxesFound++;
          }
        }
        //check left and down 
        if(col > 0 && row < grid.size()-1){
          if(grid[row+1][col-1] == '@'){
            // std::cout << "found[l&d]: (" << row+1 << ", " << col-1 << ")\n";
            boxesFound++;
          }
        }
        //check right and up
        if(col < grid[row].size()-1 && row > 0){
          if(grid[row-1][col+1] == '@'){
            // std::cout << "found[r&u]: (" << row-1 << ", " << col+1 << ")\n";
            boxesFound++;
          }
        }
        //check right and down 
        if(col < grid[row].size()-1 && row < grid.size()-1){
          if(grid[row+1][col+1] == '@'){
            // std::cout << "found[r&d]: (" << row+1 << ", " << col+1 << ")\n";
            boxesFound++;
          }
        }

        //how many you find?
        if(boxesFound < 4){
          newGrid[row][col] = 'X';
          moveableBoxes++;
        }
        // std::cout << "found " << boxesFound << " boxes\n\n";
      }
    }
    std::cout << "moveable boxes on pass["<<index<<"]: " << moveableBoxes << " boxes\n\n";
    grid = newGrid;
  }

  //PRINT
  for(auto row : newGrid){
    for(char c : row){
      std::cout << c;
    }
    std::cout << "\n";
  }

  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;
  std::cout << "\n================EXECUTION STATS=================\n";
  std::cout << "ELAPSED TIME: " << elapsedTime.count() << "\n";
  std::cout << "TOTAL VALUE: " << moveableBoxes << "\n";
  std::cout << "\n================================================\n";

  system("pause");
  return 0;
}
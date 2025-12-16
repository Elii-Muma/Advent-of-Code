#include <iostream>
#include <string>
#include <fstream>

/**
 * @brief
 * todo:
 * -> read from input file
 * -> check direction
 * -> do arithmetic
 * -> check if result is 0
 * -> if zero append one to code
 * -> else keep moving
 * @return int
 */

int main()
{

  std::ifstream input_file;
  input_file.open("resources/input.txt");

  if (!input_file.is_open())
  {
    std::cerr << "file failed to open\n";
    return -1;
  }

  std::string line_str = "";
  int wrapped_value{0};
  int zeroCount{0};
  int startValue{50};
  int rotateValue{0};

  while (std::getline(input_file, line_str))
  {
    switch (line_str[0])
    {
    case 'R':
      rotateValue = std::stoi(line_str.substr(1));
      // std::cout << "going right, start value:: " << startValue << "\n";
      for (int i = 1; i <= rotateValue; i++)
      {
        startValue += 1;
        startValue = (startValue % 100 + 100) % 100;
        zeroCount += (startValue == 0) ? 1 : 0;
      }
      // std::cout << "start value loop:: " << startValue << "\n";
      // std::cout << "zeroCount:: " << zeroCount << "\n";
      break;
    case 'L':
      rotateValue = std::stoi(line_str.substr(1));
      // std::cout << "going left, start value:: " << startValue << "\n";
      for (int i = 1; i <= rotateValue; i++)
      {
        startValue -= 1;
        startValue = (startValue % 100 + 100) % 100;
        zeroCount += (startValue == 0) ? 1 : 0;
      }
      // std::cout << "start value loop:: " << startValue << "\n";
      // std::cout << "zeroCount:: " << zeroCount << "\n";
      break;
    default:
      std::cout << "idk whats cutting\n";
    }
  }
  std::cout << "passcode:: " << zeroCount << "\n";

  system("pause");
  return 0;
}
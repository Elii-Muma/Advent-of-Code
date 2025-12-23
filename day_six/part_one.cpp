#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

int main()
{

  std::ifstream inputFile;
  inputFile.open("../day_six/resources/input.txt");

  if (!inputFile.is_open())
  {
    std::cout << "FILE_FAILED_TO_OPEN\n";
    system("pause");
    return -1;
  }

  std::string inputLine;
  std::vector<std::vector<long>> numbers(1000);
  std::vector<char> operators(1000);
  int index{0};
  std::string num{""};
  int rowCount{0};

  try
  {
    while (std::getline(inputFile, inputLine))
    {
      int len = static_cast<int>(inputLine.length()) - 1;
      std::cout << inputLine << "\n";
      index = 0;
      for (char c : inputLine)
      {
        if (c == ' ')
        {
          if (num.empty())
          {
            num = "";
            continue;
          }
          std::cout << "at index:: " << index << "\n";
          numbers[index].push_back(std::stol(num));
          index++;
          num.clear(); 
          std::cout << "continue\n";
          continue;
        }
        if (std::isdigit(c))
        {
          num.push_back(c);
          std::cout << "num:: [" << num << "]\n";
        }
        else
        {
          std::cout << "operator:: " << c << "\n";
          operators[index] = (c);
          index++;
        }
      }
      if (!num.empty())
      {
        numbers[index].push_back(std::stol(num));
        std::cout << "num from op:: [" << num << "]\n";
        num.clear(); 
        index = 0;
        rowCount++;
      }
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  long long int finalResult{0};
  std::cout << "\n\n=====ARRAY BUCKETS======\n";
  for (int i = 0; i < operators.size(); i++)
  {
    std::cout << "operator:" << operators[i] << "\n";
    unsigned long long int result{0};
    switch (operators[i])
    {
    case '*':
      result = 1;
      for (long num : numbers[i]){
        std::cout << "index [" << i << "] num:" << num << "\n";
        result *= num;
      }
      std::cout << "index [" << i << "] result:" << result << "\n";
      finalResult += result;
      break;
    case '-':
      for (long num : numbers[i]){
        std::cout << "index [" << i << "] num:" << num << "\n";
        result -= num;
      }

      std::cout << "index [" << i << "] result:" << result << "\n";
      finalResult += result;
      break;
    case '+':
      for (long num : numbers[i]){
        std::cout << "index [" << i << "] num:" << num << "\n";
        result += num;
      }
      std::cout << "index [" << i << "] result:" << result << "\n";
      finalResult += result;
      break;
    default:
      break;
    }
  }

  std::cout << "final Result: " << finalResult << "\n";

  system("pause");
  return 0;
}
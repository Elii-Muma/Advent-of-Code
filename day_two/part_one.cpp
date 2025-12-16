#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <chrono>

struct rangePair
{
  std::string start;
  std::string end;
} m_pair;

std::vector<std::string> m_invalid_numbers;
bool isVerboseComments{false};

int checkDuplicate(long long value)
{

  std::string strValue = std::to_string(value);
  // int num = std::stoi(lePair.start);
  long long len = static_cast<long>(strValue.length());

  if (len % 2 == 0)
  {
    long long midpoint = len / 2;
    long long firstHalf = std::stoll(strValue.substr(0, midpoint));
    long long secondHalf = std::stoll(strValue.substr(midpoint));
    // std::cout << "firstHalf :: " << firstHalf << "\n";
    // std::cout << "secondHalf :: " << secondHalf<< "\n";
    if (firstHalf == secondHalf)
    {
      std::cout << "found duplicate sequence number:: " << strValue << "\n";
      m_invalid_numbers.push_back(strValue);
    }
  }
  return 0;
}

int checkLeadingZero(int value)
{

  std::string strValue = std::to_string(value);
  if (strValue[0] == '0')
  {
    std::cout << "found leading zero number:: " << strValue << "\n";
    m_invalid_numbers.push_back(strValue);
  }
  return 0;
}

int main()
{
  auto startTimer = std::chrono::high_resolution_clock::now();
  std::ifstream inputFile;
  inputFile.open("../day_two/resources/input.txt");
  if (!inputFile.is_open())
  {
    std::cout << "FAILED_TO_OPEN_FILE\n";
    return -1;
  }

  std::pair<std::string, std::string> yup;
  std::string lineStr;
  std::vector<rangePair> ranges;

  int startIndex{0}; //doesnt reset because its really just one line
  //EXTRACT THE RANGES FROM THE txt FILE
  while (std::getline(inputFile, lineStr))
  {
    std::cout << "string :: " << lineStr << "\n";
    startIndex = 0; //reset 
    for (int i = 0; i < lineStr.length(); i++)
    {
      if (lineStr[i] == '-')
      {
        m_pair.start = lineStr.substr(startIndex, i - startIndex);
        startIndex = i + 1;
      }
      if (lineStr[i] == ',')
      {
        m_pair.end = lineStr.substr(startIndex, i - startIndex);
        startIndex = i + 1;
        ranges.push_back(m_pair);
      }
    }
    m_pair.end = lineStr.substr(startIndex);
    ranges.push_back(m_pair);
    std::cout << "at end:: " << m_pair.end << "\n";
  }

  //CHECK FOR DUPLICATES IN EACH RANGE AND SUM THEM UP
  std::cout << "\n\n====PAIRS=====\n";
  for (auto pair : ranges)
  {
    std::cout << "(" << pair.start << ", " << pair.end << ")\n";
    try
    {
      long long lowerBound = std::stoll(pair.start);
      long long upperBound = std::stoll(pair.end);
      for (long long i = lowerBound; i <= upperBound; i++)
      {
        long long value = i;
        // std::cout<<"value :: " << value << "\n";
        checkDuplicate(value);
        checkLeadingZero(value);
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  std::cout << "\n====INVALID NUMBERS =====\n ";
  unsigned long long int sum{0}; 
  if (!m_invalid_numbers.empty())
  {
    for (std::string str : m_invalid_numbers)
    {
      std::cout << "le invalid number:: " << str << "\n";
      sum += std::stoll(str);
    }
  }

  std::cout << "\n====FINAL SUM=====\n ";
  std::cout << "final sum = "<<sum<<"\n ";

  auto endTimer = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = endTimer - startTimer;
  std::cout << "\n\n====EXECUTION INFORMATION=====\n ";
  std::cout << "ELAPSED TIME: " << elapsedTime.count() << "\n"
            << "NUMBER OF RANGES: " << ranges.size() << "\n"
            << "VERBOSE COMMENTS: " << (isVerboseComments) ? "ON" : "OFF";
  std::cout << "\n================================\n ";

  system("pause");
  return 0;
}
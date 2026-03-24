#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct vec3{
    long long x{0};
    long long y{0};
    long long z{0};
};

long double calculateDistance(vec3 a, vec3 b){
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;

    long long d = ((dx * dx) + (dy * dy) + (dz * dz));

    return std::sqrt(d);
}

int main()
{
  vec3 a = {2, 5, 0};
  vec3 b = {11, 1, 0};
  std::cout << "distance: " << calculateDistance(a, b) << "\n";

  system("pause");
  return 0;
}
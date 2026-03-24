#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// THIS WAS ACTUALLY THE WORST ONE - so confusing :(

struct vec3
{
    long long x{0};
    long long y{0};
    long long z{0};
};

typedef struct
{
    vec3 b1;
    vec3 b2;
    long long area;
} rec_points;
int allInCircuit = 0;

bool compareVectors(vec3 a, vec3 b)
{
    if (a.x == b.x && a.y == b.y && a.z == b.z)
        return true;

    return false;
}

void printArr(std::vector<rec_points> arr)
{
    int i{1};
    for (auto conn : arr)
    {
        std::cout << "box " << i << ": \t" << "[("
                  << conn.b1.x << ", " << conn.b1.y << ", " << conn.b1.z << "), " << "("
                  << conn.b2.x << ", " << conn.b2.y << ", " << conn.b2.z << ")] ="
                  << conn.area << "\n";
        i++;
    }
}
long long calculateArea(vec3 a, vec3 b)
{
    long long len = std::abs(a.y - b.y) + 1;
    long long wid = std::abs(a.x - b.x) + 1;
    // std::cout << "len: " << len << "\n";
    // std::cout << "wid: " << wid << "\n";

    return len * wid;
}

long double calculateDistance(vec3 a, vec3 b)
{
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;

    long long d = ((dx * dx) + (dy * dy) + (dz * dz));

    return std::ceil(std::sqrt(d));
}

bool checkExistsInside(vec3 point, std::vector<vec3> &points)
{
    int winding = 0;
    int n = points.size(); // use the original ordered polygon points

    for (int i = 0; i < n - 1; i++)
    {
        vec3 a = points[i]; // use original ordered points, not old_points
        vec3 b = points[i + 1];

        if (a.y <= point.y)
        {
            if (b.y > point.y)
            {
                // upward crossing
                // check if point is left of edge a->b
                long long cross = (b.x - a.x) * (point.y - a.y) - (point.x - a.x) * (b.y - a.y);
                if (cross > 0)
                    winding++;
            }
        }
        else
        {
            if (b.y <= point.y)
            {
                // downward crossing
                long long cross = (b.x - a.x) * (point.y - a.y) - (point.x - a.x) * (b.y - a.y);
                if (cross < 0)
                    winding--;
            }
        }
    }

    return winding != 0;
}

bool createAndCheckPoints(vec3 a, vec3 c, std::vector<vec3> &points)
{
    vec3 b = {c.x, a.y};
    vec3 d = {a.x, c.y};
    std::cout << "new b: (" << b.x << ", " << b.y << ")\n";
    std::cout << "new d: (" << d.x << ", " << d.y << ")\n";

    int found = 0;
    if (checkExistsInside(b, points) && checkExistsInside(d, points))
    {
        std::cout << "points found in or on polygon\n";
        return true;
    }
    else
    {
        std::cout << "points not found in or on the polygon\n";
    }

    return false;
}

int main()
{

    auto startTimer = std::chrono::high_resolution_clock::now();
    std::ifstream inputFile;
    inputFile.open("../day_nine/resources/test.txt");

    if (!inputFile.is_open())
    {
        std::cout << "FILE_FAILED_TO_OPEN\n";
        system("pause");
        return -1;
    }

    std::string inputLine;
    std::vector<vec3> boxes;

    // step 1. get and store the coordinates of the junction boxes
    while (std::getline(inputFile, inputLine))
    {
        std::string value;
        int index{0};
        vec3 currBox;
        for (auto c : inputLine)
        {
            if (std::isdigit(c))
            {
                value.push_back(c);
            }
            else
            {
                // std::cout << "value: " << c << "\n";
                if (index == 0)
                    currBox.x = std::stoi(value);
                value.clear();
            }
        }
        currBox.y = std::stoi(value);
        currBox.z = 0;
        boxes.push_back(currBox);
    }

    std::vector<rec_points> areas;
    for (int i = 0; i < boxes.size(); i++)
    {
        rec_points temp;
        temp.b1 = boxes[i];

        if (i + 1 > boxes.size())
            continue;
        for (int j = i + 1; j < boxes.size(); j++)
        {
            temp.b2 = boxes[j];
            if (createAndCheckPoints(temp.b2, temp.b1, boxes))
            temp.area = calculateArea(temp.b1, temp.b2);
            areas.push_back(temp);
        }
    }

    std::sort(areas.begin(), areas.end(), [](const rec_points &a, const rec_points &b)
              { return a.area > b.area; });
    printArr(areas);

    auto endTimer = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = endTimer - startTimer;
    std::cout << "=============EXECUTION STATS================\n"
              << "Largest Area: " << areas[0].area << "\n"
              << "EXECUTION TIME: " << elapsedTime.count() << "\n";

    system("pause");
    return 0;
}

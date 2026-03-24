#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>



struct vec3
{
    long long x{0};
    long long y{0};
    long long z{0};

    bool operator==(const vec3 &other) const
    {
        return (other.x == x && other.y == y && other.z == z);
    }
};

template <>
struct std::hash<vec3>
{
    std::size_t operator()(const vec3 &v) const
    {
        using std::hash;
        using std::size_t;
        using std::string;

        return ((hash<long long>()(v.x) ^ (hash<long long>()(v.y) << 1)) >> 1) ^ (hash<long long>()(v.z) << 1);
    }
};

typedef struct
{
    vec3 b1;
    vec3 b2;
    long long int area;
} rec_points;

enum dir
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

dir checkDirection(vec3 start, vec3 end);

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

long double calculateDistance(vec3 a, vec3 b)
{
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;

    long long d = ((dx * dx) + (dy * dy) + (dz * dz));

    return std::sqrt(d);
}

long long int calculateArea(vec3 a, vec3 b)
{
    long long int len = std::abs(a.y - b.y) + 1;
    long long int wid = std::abs(a.x - b.x) + 1;
    // std::cout << "len: " << len << "\n";
    // std::cout << "wid: " << wid << "\n";

    return len * wid;
}

int maxLeft, maxRight, maxUp, maxDown;
std::vector<vec3> points;
// = { {7, 1}, {9, 1}, {11, 1}, {11, 7}, {9, 7}, {9, 5}, {2, 5}, {2, 3}, {7, 3}, {7,1}};
std::unordered_set<vec3> corners;
std::vector<vec3> old_points;

bool moveRight(long long maxRight, vec3 &nextP)
{
    // increment the x coordinate by one and
    vec3 temp = nextP;
    bool found = false;
    std::vector<vec3> tempPoints;
    tempPoints.push_back(temp);
    while (true)
    {
        temp.x += 1;
        tempPoints.push_back(temp);
        if (temp.x <= maxRight)
        {
            auto it = std::find_if(points.begin(), points.end(), [temp](const vec3 &a)
                                   { return compareVectors(a, temp); });
            // if it does set our next point to be that one
            // we actually only want the furthest point to the right
            // so keep going until we reach end
            if (it != points.end())
            {
                int index = std::distance(points.begin(), it);
                nextP = points[index];
                for (auto p : tempPoints)
                    corners.insert(p);
                found = true;
                break;
            }
        }
    }
    return found;
}

bool moveLeft(long long maxLeft, vec3 &nextP)
{

    // increment the x coordinate by one and
    vec3 temp = nextP;
    bool found{false};
    std::vector<vec3> tempPoints;
    tempPoints.push_back(temp);
    while (true)
    {
        temp.x -= 1;
        tempPoints.push_back(temp);
        if (temp.x >= maxLeft)
        {
            auto it = std::find_if(points.begin(), points.end(), [temp](const vec3 &a)
                                   { return compareVectors(a, temp); });

            // if it does set our next point to be that one
            // we actually only want the furthest point to the right
            // so keep going until we reach end
            if (it != points.end())
            {
                int index = std::distance(points.begin(), it);
                nextP = points[index];
                for (auto p : tempPoints)
                    corners.insert(p);
                found = true;
                break;
            }
        }
    }
    return found;
}

bool moveUp(long long maxUp, vec3 &nextP)
{
    // increment the x coordinate by one and
    vec3 temp = nextP;
    bool found{false};
    std::vector<vec3> tempPoints;
    tempPoints.push_back(temp);
    while (true)
    {
        temp.y -= 1;
        tempPoints.push_back(temp);
        if (temp.y >= maxUp)
        {
            auto it = std::find_if(points.begin(), points.end(), [temp](const vec3 &a)
                                   { return compareVectors(a, temp); });

            // if it does set our next point to be that one
            // we actually only want the furthest point to the right
            // so keep going until we reach end
            if (it != points.end())
            {
                int index = std::distance(points.begin(), it);
                nextP = points[index];
                for (auto p : tempPoints)
                    corners.insert(p);
                found = true;
                break;
            }
        }
    }
    return found;
}

bool moveDown(long long maxDown, vec3 &nextP)
{
    // increment the x coordinate by one and
    vec3 temp = nextP;
    bool found = false;
    std::vector<vec3> tempPoints;
    tempPoints.push_back(temp);
    // for (int i = 0; i < points.size(); i++)
    while (true)
    {
        // std::cout << "checking: " << "(" << temp.x << ", " << temp.y << ", " << temp.z << ")\n";
        temp.y += 1;
        tempPoints.push_back(temp);

        if (temp.y <= maxDown)
        {
            auto it = std::find_if(points.begin(), points.end(), [temp](const vec3 &a)
                                   { return compareVectors(a, temp); });

            // if it does set our next point to be that one
            // we actually only want the furthest point to the right
            // so keep going until we reach end
            if (it != points.end())
            {
                // std::cout << "found: " << "(" << temp.x << ", " << temp.y << ", " << temp.z << ")\n";
                int index = std::distance(points.begin(), it);
                nextP = points[index];
                for (auto p : tempPoints)
                    corners.insert(p);
                found = true;
                break;
            }
        }
    }
    return found;
}

bool checkExists(std::unordered_set<vec3> &arr, vec3 point)
{
    // std::cout << "checking exists\n";
    auto it = arr.find(point);

    if (it != arr.end())
        return true;

    return false;
}

// bool checkExistsInside(vec3 point)
// // maybe shoot a ray in each direction and see if
// // need to optimize
// {
//     // std::cout << "point: (" << point.x << ", " << point.y << ")\n";
//     vec3 temp = point;
//     bool down{false}, up{false}, left{false}, right{false};
//     while(true)
//     {
//         temp.y += 1;
//         if (temp.y <= maxDown)
//         {

//             auto it = corners.find(temp);

//             if (it != corners.end())
//             {
//                 // std::cout << "found: (" << temp.x << ", " << temp.y << ")\n";
//                 down = true;
//                 break;
//             }
//         }else
//             break;
//     }

//     temp = point;
//     while(true)
//     {
//         temp.y -= 1;
//         if (temp.y >= maxUp)
//         {
//             auto it = corners.find(temp);

//             if (it != corners.end())
//             {
//                 // std::cout << "found: (" << temp.x << ", " << temp.y << ")\n";
//                 up = true;
//                 break;
//             }
//         }else
//             break;
//     }
//     temp = point;
//     while(true)
//     {
//         temp.x -= 1;
//         if (temp.x >= maxLeft)
//         {
//             auto it = corners.find(temp);

//             if (it != corners.end())
//             {
//                 // std::cout << "found: (" << temp.x << ", " << temp.y << ")\n";
//                 left = true;
//                 break;
//             }
//         }else
//             break;
//     }
//     temp = point;
//     while(true)
//     {
//         temp.x += 1;
//         if (temp.x <= maxRight)
//         {
//             auto it = corners.find(temp);

//             if (it != corners.end())
//             {
//                 // std::cout << "found: (" << temp.x << ", " << temp.y << ")\n";
//                 right = true;
//                 break;
//             }
//         }else
//             break;
//     }

//     if (down && up && left && right)
//     {
//         // std::cout << "found inside\n";
//         return true;
//     }

//     // std::cout << "not found inside\n";
//     return false;
// }

bool checkExistsInside(vec3 point)
// maybe shoot a ray in each direction and see if
// need to optimize
{
    // std::cout << "point: (" << point.x << ", " << point.y << ")\n";
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

bool checkValidLine(vec3 a, vec3 b)
{
    dir direction = checkDirection(a, b);
    if(direction == dir::NONE) {
        // std::cout << "weird dir\n";
        return false;
    }

    bool isFound = true;
    switch (direction) {
    case dir::LEFT: {
        // std::cout<< "moving left\n";
        vec3 start = a;
        vec3 end = b;
        while (start.x > end.x){
            start.x -= 1;
            // std::cout<< "checking:(" << start.x << ", " << start.y<< ")\n";
            auto it = corners.find(start);
            if (it == corners.end() && !checkExistsInside(start)){
                // std::cout << "line not valid\n";
                return false;
            }
        }
    } break;
    case dir::RIGHT: {
        // std::cout<< "moving right\n";
        vec3 start = a;
        vec3 end = b;
        while (start.x < end.x)
        {
            start.x += 1;
            // std::cout<< "checking:(" << start.x << ", " << start.y<< ")\n";
            auto it = corners.find(start);
            if (it == corners.end() && !checkExistsInside(start)){
                // std::cout << "line not valid\n";
                return false;
            }
        }
    } break;
    case dir::UP: {
        // std::cout<< "moving up\n";
        vec3 start = a;
        vec3 end = b;
        // std::cout<< "start:(" << start.x << ", " << start.y<< ")\n";
        // std::cout<< "end:(" << end.x << ", " << end.y<< ")\n";
        while (start.y > end.y)
        {
            start.y -= 1;
            // std::cout<< "checking:(" << start.x << ", " << start.y<< ")\n";
            auto it = corners.find(start);
            if (it == corners.end() && !checkExistsInside(start)){
                // std::cout << "line not valid\n";
                return false;
            }
            
        }
    }
    break;
    case dir::DOWN:
    {
        // std::cout<< "moving down\n";
        vec3 start = a;
        vec3 end = b;
        while (start.y < end.y)
        {
            start.y += 1;
            // std::cout<< "checking:(" << start.x << ", " << start.y<< ")\n";
            auto it = corners.find(start);
            if (it == corners.end() && !checkExistsInside(start)){
                // std::cout << "line not valid\n";
                return false;
            }
        }
    }
    break;
    default:
        break;
    }

    return true;
}

bool createAndCheckPoints(vec3 a, vec3 c)
{

    // std::cout << "point a: (" << a.x << ", " << a.y << ")\n";
    // std::cout << "point c: (" << c.x << ", " << c.y << ")\n";
    /// check [a, d] [a, b] & [c, b] [c, d]
    ///if a and c are in a straigt line dont check if line valid
    ///no, if a and c are in a straight line then just check if the line is valid
    bool found{false};
    if(c.x == a.x || a.y == c.y){
        // std::cout << "straight line\n";
        if(!checkValidLine(a, c)){
            // std::cout << "straight line not valid\n";
            return false;
        }
        // std::cout << "straight line valid\n";
        return true;
    }else{
        vec3 b = {c.x, a.y};
        vec3 d = {a.x, c.y};
        // std::cout << "new b: (" << b.x << ", " << b.y << ")\n";
        // std::cout << "new d: (" << d.x << ", " << d.y << ")\n";
        if (checkExists(corners, b) && (checkValidLine(a, b) && checkValidLine(c, b))) {
            // std::cout << "found d in corner\n";
        } else if (checkExistsInside(b) && (checkValidLine(a, b) && checkValidLine(c, b))) {
            // std::cout << "found d inside\n";
        } else {
            // std::cout << "lines a->b & c->b not valid or found\n";
            return false;
        } 

        if (checkExists(corners, d) && (checkValidLine(a, d) && checkValidLine(c, d))) {
            // std::cout << "found d in corner\n";
        } else if (checkExistsInside(d) && (checkValidLine(a, d) && checkValidLine(c, d))) {
            // std::cout << "found d inside\n";
        } else {
            // std::cout << "lines a->d & c->d not valid or found\n";
            return false;
        }
    }
    // std::cout << "area valid\n";
    return true;
}

dir checkDirection(vec3 start, vec3 end) {
    if (start.x == end.x)
    {
        // same x so we're moving either up or down
        if (start.y < end.y)
        {
            return dir::DOWN;
        }
        if (start.y > end.y)
        {
            return dir::UP;
        }
    }
    else if (start.y == end.y)
    {
        // same y so we're moving either left or right
        if (start.x < end.x)
        {
            return dir::RIGHT;
        }
        if (start.x > end.x)
        {
            return dir::LEFT;
        }
    }
    return dir::NONE;
}

int main()
{
    auto startTimer = std::chrono::high_resolution_clock::now();
    std::ifstream inputFile;
    inputFile.open("../day_nine/resources/input.txt");

    if (!inputFile.is_open())
    {
        std::cout << "FILE_FAILED_TO_OPEN\n";
        system("pause");
        return -1;
    }

    std::string inputLine;

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
        points.push_back(currBox);
    }

    old_points = points;
    std::cout << "points size: " << old_points.size() << "\n";

    // sort points in the y get maxup and maxdown
    std::sort(old_points.begin(), old_points.end(), [](const vec3 &a, const vec3 &b)
              { return a.y < b.y; });

    maxUp = old_points[0].y;
    maxDown = old_points[old_points.size() - 1].y;

    // sort points in the x get maxleft and maxright
    std::sort(old_points.begin(), old_points.end(), [](const vec3 &a, const vec3 &b)
              { return a.x < b.x; });

    maxLeft = old_points[0].x;
    maxRight = old_points[old_points.size() - 1].x;

    dir lastMove = dir::NONE;
    dir newMove = dir::NONE;
    vec3 start = points[0];

    std::cout << "start point: " << "(" << start.x << ", " << start.y << ", " << start.z << ")\n";
    std::cout << "creating bounds\n";
    try
    {
        for (int i = 1; i < points.size(); i++)
        {
            newMove = checkDirection(start, points[i]);
            // if(lastMove != newMove) corners.insert(start);
            switch (newMove)
            {
            case dir::RIGHT:
                moveRight(maxRight, start);
                lastMove = newMove;
                break;
            case dir::DOWN:
                moveDown(maxDown, start);
                lastMove = newMove;
                break;
            case dir::LEFT:
                moveLeft(maxLeft, start);
                lastMove = newMove;
                break;
            case dir::UP:
                moveUp(maxUp, start);
                lastMove = newMove;
                break;
            default:
                break;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "done creating bounds\n";

    std::cout << "corners found: " << corners.size() << "\n";
    // for (auto c : corners)
    // {
    //     std::cout << "(" << c.x << ", " << c.y << ", " << c.z << ")\n";
    // }

    std::vector<rec_points> areas;
    // points.pop_back();
    for (int i = 0; i < points.size(); i++)
    {
        rec_points temp;
        temp.b1 = points[i];
        std::cout << "\n--------conn. " << i << "--------\n";

        if (i + 1 > points.size())
            continue;
        for (int j = i + 1; j < points.size(); j++)
        {
            temp.b2 = points[j];
            if (compareVectors(temp.b2, temp.b1))
                continue;
            if (createAndCheckPoints(temp.b1, temp.b2))
            {
                // std::cout << "(" << temp.b1.x << ", " << temp.b1.y << ")" << "area in\n";
                // std::cout << "(" << temp.b2.x << ", " << temp.b2.y << ")" << "area in\n";
                // std::cout << "\tarea: " << calculateArea(temp.b1, temp.b2);
                temp.area = calculateArea(temp.b1, temp.b2);
                areas.push_back(temp);
            }
            else
            {
                // std::cout << "(" << temp.b1.x << ", " << temp.b1.y << ")" << "area not in\n";
                // std::cout << "(" << temp.b2.x << ", " << temp.b2.y << ")" << "area not in\n";
            }
        }
    }

    std::sort(areas.begin(), areas.end(), [](const rec_points &a, const rec_points &b)
              { return a.area > b.area; });
    // printArr(areas);


    // if(createAndCheckPoints({9,5}, {2,3})){
    //     std::cout << "line valid\n";
    // }else
    //     std::cout << "line not valid\n";

    auto endTimer = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = endTimer - startTimer;
    std::cout << "=============EXECUTION STATS================\n"
              << "Largest Area: " << areas[0].area << "\n"
              << "EXECUTION TIME: " << elapsedTime.count() << "\n";
    system("pause");
    return 0;
}
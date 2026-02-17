#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// THIS WAS ACTUALLY THE WORST ONE - so confusing :(

struct vec3{
    long long x{0};
    long long y{0};
    long long z{0};
};

struct box{
    vec3 c;
    bool inCircuit{false};
};

typedef struct {
    vec3 b1;
    vec3 b2;
    long double distance;
} box_connection;
int allInCircuit = 0;


void addConnToCircuit(std::vector<std::vector<vec3>> &circuits, box_connection connection) {
    std::vector<vec3> temp_vec;

    temp_vec.push_back(connection.b1);
    temp_vec.push_back(connection.b2);

    circuits.push_back(temp_vec);
}

bool compareVectors(vec3 a, vec3 b){
    if(a.x == b.x && a.y == b.y && a.z ==b.z) return true;
    
    return false;
}

void setIsInCircuit(std::vector<box> &arr, vec3 vec){
    for(auto b : arr){
        if(compareVectors( b.c, vec) && !b.inCircuit){
            b.inCircuit = true;
            allInCircuit++;
            return;
        }
    }
}

int checkExists(std::vector<std::vector<vec3>> &arr, vec3 vector){

    auto it = std::find_if(arr.begin(), arr.end(), [vector](const std::vector<vec3> &p){ 
                                return std::any_of(p.begin(), p.end(), [vector](const vec3 &c){
                                    return (compareVectors(c, vector));
                                });
                            });

    // if it(iterator) is equal to the end, meaning it reached 
    // the end and never found anything, then...yeah 
    if (it != arr.end()){
        int index = std::distance(arr.begin(), it);
        return index;
    }

    return -1;
}

void printArr(std::vector<box_connection> arr){
    int i{1};
    for(auto conn : arr){
        std::cout   << "box "<< i <<": \t"<< "[(" 
                    << conn.b1.x << ", " << conn.b1.y << ", " << conn.b1.z << "), " << "(" 
                    << conn.b2.x << ", " << conn.b2.y << ", " << conn.b2.z << ")] =" 
                    << conn.distance << "\n";
        i++;
    }
}
                              
long double calculateDistance(vec3 a, vec3 b){
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;

    long long d = ((dx * dx) + (dy * dy) + (dz * dz));

    return std::sqrt(d);
}

int main()
{

    auto startTimer = std::chrono::high_resolution_clock::now();
    std::ifstream inputFile;
    inputFile.open("../day_eight/resources/input.txt");

    if (!inputFile.is_open()){
        std::cout << "FILE_FAILED_TO_OPEN\n";
        system("pause");
        return -1;
    }

    std::string inputLine;
    std::vector<box> boxes;

    // step 1. get and store the coordinates of the junction boxes 
    while(std::getline(inputFile, inputLine)){
        std::string value;
        int index{0};
        box currBox;
        for(auto c : inputLine){
            if(std::isdigit(c)){
                value.push_back(c);
            }else{
                if(index == 0) currBox.c.x = std::stoi(value);
                else if(index == 1) currBox.c.y = std::stoi(value);
                index++;
                value.clear();
            }
        }
        currBox.c.z = std::stoi(value);
        boxes.push_back(currBox);
    }

    // step 2: create all possible connections between boxes
    // where order ab == ba
    std::vector<box_connection> connections;
    for(int i = 0; i < boxes.size(); i++){
        box_connection temp; 
        temp.b1 = boxes[i].c;

        if(i+1 > boxes.size()) continue;
        for(int j = i+1; j < boxes.size(); j++){
           temp.b2 = boxes[j].c;
           temp.distance = calculateDistance(temp.b1, temp.b2);
           connections.push_back(temp);
        }
    }

    // step 2.1: sort the connections made by distance -- closest to furthest  
    std::sort(connections.begin(), connections.end(), [](const box_connection &a, const box_connection &b){
        return a.distance < b.distance;
    });
    // printArr(connections);

    // step 3: create circuits
    // - merge circuits where box boxes in a connection belong to two different circuits.
    // - when only one box belongs to a circuit add the one that doesnt to the circuit.
    // - if none of them belong to a circuit, create a new circuit.
    std::vector<std::vector<vec3>> circuits; 

    int size = connections.size();
    int max_connections{size};
    int prev{0};
    long long int product{1};
    for(int j = 0; j<max_connections; j++){

        if(allInCircuit >= boxes.size()){
            std::cout   << "its this connection: "
                        << connections[j-1].b1.x << ", "
                        << connections[j-1].b2.x
                        << "\n";
            product = connections[j-1].b1.x * connections[j-1].b2.x;
            break;
        }

        vec3 jb1 = connections[j].b1;
        vec3 jb2 = connections[j].b2;

        int i1 = checkExists(circuits, jb1); //index 1
        int i2 = checkExists(circuits, jb2); //index 2

        if(i1 != -1 && i2 != -1){
            if(i1 == i2) continue;
            // merge
            circuits[i1].insert(circuits[i1].end(), circuits[i2].begin(), circuits[i2].end());
            circuits.erase(circuits.begin() + i2);
            continue;
        } if(i1 != -1){
            circuits[i1].push_back(jb2);
            setIsInCircuit(boxes, jb2);
            continue;
        }else if(i2 != -1){
            circuits[i2].push_back(jb1);
            setIsInCircuit(boxes, jb1);
            continue;
        } else {
            addConnToCircuit(circuits, connections[j]);
            setIsInCircuit(boxes, jb1);
            setIsInCircuit(boxes, jb2);
            continue;
        }
    }

    std::sort(circuits.begin(), circuits.end(), [](std::vector<vec3> &a, std::vector<vec3> &b){
        return a.size() > b.size();
    });

    int i{1};
    for(auto b : circuits){
        std::cout   << "circuit "<< i <<". j-boxes = " << b.size() << "\n"; 
        // if(i <= 3) product *= b.size();
        int j{1};
        for(auto c : b){
            std::cout << j << ". (" << c.x  << ", " << c.y << ", " << c.z <<")\n";
            j++;
        }
        std::cout << "\n";
        i++;
    }

    auto endTimer = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = endTimer - startTimer;
    std::cout << "=============EXECUTION STATS================\n"
                << "PRODUCT OF TOP 3: " << product << "\n"
                << "EXECUTION TIME: " << elapsedTime.count() << "\n";

    system("pause");
    return 0;
}

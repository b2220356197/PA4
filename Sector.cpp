#include "Sector.h"
#include <math.h>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
    distance_from_earth = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    int distance_floored = floor(distance_from_earth);
    sector_code += std::to_string(distance_floored);
    sector_code += (x == 0) ? 'S' : (x > 0) ? 'R' : 'L';
    sector_code += (y == 0) ? 'S' : (y > 0) ? 'U' : 'D';
    sector_code += (z == 0) ? 'S' : (z > 0) ? 'F' : 'B';

}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}
bool Sector::operator<(const Sector& other) const {
    if (x < other.x) return true;
    if (x > other.x) return false;
    if (y < other.y) return true;
    if (y > other.y) return false;
    return z < other.z;
}

bool Sector::operator>(const Sector& other) const {
    return other < *this;
}

bool Sector::operator<=(const Sector& other) const {
    return !(other < *this);
}

bool Sector::operator>=(const Sector& other) const {
    return !(*this < other);
}
Sector& Sector::operator=(const Sector& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        distance_from_earth = other.distance_from_earth;
        sector_code = other.sector_code;
        left = other.left;
        right = other.right;
        parent = other.parent;
        color = other.color;
    }
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return x == other.x && y == other.y && z == other.z &&
           distance_from_earth == other.distance_from_earth &&
           sector_code == other.sector_code;
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}
//Sector& Sector::operator=(const Sector& other) {
//    // TODO: Overload the assignment operator
//    return *this;
//}
//
//bool Sector::operator==(const Sector& other) const {
//    return (x == other.x && y == other.y && z == other.z);
//}
//
//bool Sector::operator!=(const Sector& other) const {
//    return !(*this == other);
//}
#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H
#include <map>

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include "vector"

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    Sector* rotateLeft(Sector* root);
    Sector* rotateRight(Sector* root);
    void alterNodeColors(Sector *currentNode);
    bool nodeIsRed(Sector *currentNode);
    void recursivelyDelete(Sector *currentNode);
    Sector* insertRec(Sector* root, Sector* to_insert, Sector* parent);
    void fixInsertion(Sector*& node);
    bool is_bigger(Sector* node, Sector* other);
    void dispINorder(Sector* node);
private:
    std::map<std::string, Sector*> __ctr_PROTOCOL_API__;
std::vector<Sector*>& findRec(std::vector<Sector*>&, Sector* node);
    std::vector<Sector*> __merge_paths(std::vector<Sector*>& pathA, std::vector<Sector*>& pathB);
    std::vector<Sector*> __findPathToRoot(Sector* node);
    std::vector<Sector*> __findCommonPath(std::vector<Sector*>& pathA, std::vector<Sector*>& pathB);
    void displayINO(Sector* node);
    void displayPRE(Sector* node);
    void displayPOST(Sector* node);
    void delete_tree(Sector* node);
};

#endif // SPACESECTORLLRBT_H

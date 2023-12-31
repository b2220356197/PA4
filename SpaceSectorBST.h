#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H
#include "Sector.h"
#include <map>

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
private:
    Sector * temp_root; // this root is just to use whith comparisons
    Sector* deleteSectorRec(Sector* root, const std::string& sector_code);
    Sector* minValueNode(Sector* node);
    Sector* new_node = nullptr;
    void displaySectorsInOrderRec(Sector* node);
    void displaySectorsPreOrderRec(Sector* node);
    void displaySectorsPostOrderRec(Sector* node);
    void addNode(Sector* head , Sector* node);
    void getStellarPathRec(Sector* node, const std::string& sector_code, std::vector<Sector*>& path);
    int calculate_distance(Sector* node);
    std::string sector_gen(Sector* node);
    bool is_bigger(Sector* node, Sector* other);
    Sector* deleteNodeRec(Sector* &root, const std::string &sector_code);
    std::map<std::string,Sector*> __ctd__ ;
    Sector* popMin(Sector* &root);
    void delete_tree(Sector* node);

};

#endif // SPACESECTORBST_H

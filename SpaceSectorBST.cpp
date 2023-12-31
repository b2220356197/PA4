#include "SpaceSectorBST.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <math.h>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {

}

void SpaceSectorBST::delete_tree(Sector* node) {
    if (node == nullptr) {
        return;
    }

    // Recursively delete left and right subtrees
    delete_tree(node->left);
    delete_tree(node->right);

    // Delete the current node after deleting its children
    delete node;
}

SpaceSectorBST::~SpaceSectorBST() {
    delete_tree(root);
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison critera based on the sector coordinates.
    // with skipping the first line
    try {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            getline(file, line);
            while (getline(file, line)) {
                stringstream ss(line);
                string token;
                int x, y, z;
                getline(ss, token, ',');
                x = stoi(token);
                getline(ss, token, ',');
                y = stoi(token);

                getline(ss, token, ',');
                z = stoi(token);
                //cout << "Inserting sector: " << x << "," << y << "," << z << endl;
                insertSectorByCoordinates(x, y, z);

            }}} catch (exception& e) {
        cout << "Error on read sectors: " << e.what() << endl;
    }
}

bool SpaceSectorBST::is_bigger(Sector* node, Sector* other) {
    if (node->x > other->x) {
        return true;
    } else if (node->x == other->x) {
        if (node->y > other->y) {
            return true;
        } else if (node->y == other->y) {
            if (node->z > other->z) {
                return true;
            }
        }
    }
    return false;
}



void SpaceSectorBST::addNode(Sector* head, Sector* node){
    // Check if the current node has the same sector code as the new node
    if (head->sector_code == node->sector_code) {
        // If the sector codes are the same, do not insert the node
        return;
    }

    if (is_bigger(head, node)) {
        if (head->left == nullptr) {
            head->left = node;
            node->parent = head;
        } else {
            addNode(head->left, node);
        }
    } else {
        if (head->right == nullptr) {
            head->right = node;
            node->parent = head;
        } else {
            addNode(head->right, node);
        }
    }
}


void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    Sector* new_sector = new Sector(x, y, z);

    if (root == nullptr) {
        root = new_sector;
        root->sector_code = "0SSS";
        root->distance_from_earth = 0;
    } else {
        //new_sector->distance_from_earth = calculate_distance(new_sector);
        //new_sector->sector_code = sector_gen(new_sector);
        addNode(root, new_sector);
    }
    __ctd__[new_sector->sector_code] = new_sector;
}


std::string SpaceSectorBST::sector_gen(Sector* node) {
    std::string sector_code = "";
    int distance_floored = floor(node->distance_from_earth);
    sector_code += std::to_string(distance_floored);

    int x = node->x;
    int y = node->y;
    int z = node->z;

    sector_code += (x == 0) ? 'S' : (x > 0) ? 'R' : 'L';
    sector_code += (y == 0) ? 'S' : (y > 0) ? 'U' : 'D';
    sector_code += (z == 0) ? 'S' : (z > 0) ? 'F' : 'B';

    return sector_code;
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    if (!(__ctd__.count(sector_code) > 0)) {
        return;
    }
    root = deleteNodeRec(root, sector_code);
}

// delete the minimum node in the bst
Sector* SpaceSectorBST::popMin(Sector *&root) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->left == nullptr) {
        Sector* temp = root->right;
        delete root;
        return temp;
    }
    root->left = popMin(root->left);
    return root;
}

Sector* SpaceSectorBST::deleteNodeRec(Sector *&node, const std::string &sector_code) {
    if (node == nullptr) {
        return nullptr;
    }

    if (is_bigger(__ctd__[sector_code], node)) {
        node->right = deleteNodeRec(node->right, sector_code);
    } else if (is_bigger(node, __ctd__[sector_code])) {
        node->left = deleteNodeRec(node->left, sector_code);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            Sector *temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        } else {
            Sector *successor = minValueNode(node->right);
            node->x = successor->x;
            node->y = successor->y;
            node->z = successor->z;
            node->distance_from_earth = successor->distance_from_earth;
            node->sector_code = successor->sector_code;
            __ctd__[node->sector_code] = node; // Update __ctd__ map
            node->right = deleteNodeRec(node->right, successor->sector_code);
        }
    }
    return node;
}


Sector* SpaceSectorBST::minValueNode(Sector* node) {
    if (node == nullptr) {
        return nullptr;
    }
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void SpaceSectorBST::displaySectorsInOrder() {
    cout << "Space sectors inorder traversal:" << endl;
    displaySectorsInOrderRec(root);
    std::cout << std::endl;
}

// Given a binary tree, print its nodes in inorder
void SpaceSectorBST::displaySectorsInOrderRec(Sector* node){
    if (node != nullptr) {
        displaySectorsInOrderRec(node->left); // Visit left child
        std::cout << node->sector_code << std::endl; // Process current node
        displaySectorsInOrderRec(node->right); // Visit right child
    }
}

void SpaceSectorBST::displaySectorsPreOrder() {
    cout << "Space sectors preorder traversal:" << endl;
    displaySectorsPreOrderRec(root);
    std::cout << std::endl;
}

void SpaceSectorBST::displaySectorsPreOrderRec(Sector* node) {
    if (node != nullptr) {
        std::cout << sector_gen(node) << endl;
        displaySectorsPreOrderRec(node->left);
        displaySectorsPreOrderRec(node->right);
    }
}

void SpaceSectorBST::displaySectorsPostOrder() {
    cout << "Space sectors postorder traversal:" << endl;
    displaySectorsPostOrderRec(root);
    std::cout << std::endl;
}

void SpaceSectorBST::displaySectorsPostOrderRec(Sector* node) {
    if (node != nullptr) {
        displaySectorsPostOrderRec(node->left);
        displaySectorsPostOrderRec(node->right);
        std::cout << node->sector_code << endl;
    }
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    if(!(__ctd__.count(sector_code) > 0)){
        Sector* notfound = new Sector(-1,-1,-1);
        std::vector<Sector*> _notfound_ = {notfound};
        return _notfound_;
    }
    std::vector<Sector*> path;

    if (sector_code == root->sector_code) {
        return path;
    }

    getStellarPathRec(root, sector_code, path);
    return path;
}

void SpaceSectorBST::getStellarPathRec(Sector* node, const std::string& sector_code, std::vector<Sector*>& path) {
    // there is a hashmap called __ctd__ where the key is the sector code and the value is a pointer to the sector node

    if (node == nullptr) {
        return;
    }



    path.push_back(node);

    if (sector_code == node->sector_code) {
        return;
    }

    if (!is_bigger(__ctd__[sector_code],node)) {
        getStellarPathRec(node->left, sector_code, path);
    } else if (is_bigger(__ctd__[sector_code],node)) {
        getStellarPathRec(node->right, sector_code, path);
    }
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    // Check if the vector is empty
    if (path.empty()) {
        cout << "A path to Dr. Elara could not be found." << endl;
        return;
    }

    // Check for a specific condition on the first element if it's not null
    if (path.front() && path.front()->x == -1) {
        cout << "A path to Dr. Elara could not be found." << endl;
        return;
    }

    // Print the stellar path
    cout << "The stellar path to Dr. Elara: ";
    for (size_t i = 0; i < path.size(); i++) {
        // Safely handle potential null pointers
        if (path[i]) {
            cout << path[i]->sector_code;
            if (i != path.size() - 1) {
                cout << "->";
            }
        } else {
            cout << "[Invalid Sector]";
        }
    }
    cout << endl;
}

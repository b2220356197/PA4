#include "SpaceSectorLLRBT.h"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);  // Skip the first line
    while (getline(file, line)) {
        stringstream ss(line);
        int x, y, z;
        ss >> x;
        ss.ignore();
        ss >> y;
        ss.ignore();
        ss >> z;

        insertSectorByCoordinates(x, y, z);
    }

    file.close();
}

void SpaceSectorLLRBT::delete_tree(Sector* node) {
    if (node == nullptr) {
        return;
    }

    // Recursively delete left and right subtrees
    delete_tree(node->left);
    delete_tree(node->right);

    // Delete the current node after deleting its children
    delete node;
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    delete_tree(root);
}


Sector *SpaceSectorLLRBT::rotateLeft(Sector *root) {
    Sector *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    temp->color = root->color;
    root->color = true;

    // Update parent pointers
    temp->parent = root->parent;
    root->parent = temp;
    if (root->right != nullptr) {
        root->right->parent = root;
    }

    return temp;
}


Sector* SpaceSectorLLRBT::rotateRight(Sector* root) {
    Sector *temporaryNode = root->left;
    root->left = temporaryNode->right;
    temporaryNode->right = root;
    temporaryNode->color = root->color;
    root->color = true;

// Update parent pointers
    temporaryNode->parent = root->parent;
    root->parent = temporaryNode;

    if (root->left != nullptr) {
        root->left->parent = root;
    }

    return temporaryNode;

}

void SpaceSectorLLRBT::alterNodeColors(Sector *currentNode) {
    currentNode->color = true;  // Set current node color to red
    if (currentNode->left != nullptr) {
        currentNode->left->color = false;  // Set left child color to black
    }
    if (currentNode->right != nullptr) {
        currentNode->right->color = false;  // Set right child color to black
    }
}

bool SpaceSectorLLRBT::nodeIsRed(Sector *currentNode) {
    return currentNode != nullptr && currentNode->color;
}

void SpaceSectorLLRBT::recursivelyDelete(Sector *currentNode) {
    if (!currentNode) {
        return;
    }
    recursivelyDelete(currentNode->left);  // Delete left subtree
    recursivelyDelete(currentNode->right);  // Delete right subtree
    delete currentNode;  // Delete the current node
}



bool SpaceSectorLLRBT::is_bigger(Sector* node, Sector* other) {
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
void SpaceSectorLLRBT::insertSectorByCoordinates(int coordX, int coordY, int coordZ) {
    Sector* newSector = new Sector(coordX, coordY, coordZ);
    __ctr_PROTOCOL_API__[newSector->sector_code] = newSector;

    if (!root) {
        root = newSector;
    } else {
        root = insertRec(root, newSector, nullptr);
    }
    root->color = false;
}


Sector* SpaceSectorLLRBT::insertRec(Sector* root, Sector* to_insert, Sector* parent) {
    if (root == nullptr) {
        to_insert->parent = parent;
        return to_insert;
    }

    if (is_bigger(to_insert, root)) {
        root->right = insertRec(root->right, to_insert, root);
    } else if (!is_bigger(to_insert, root)) {
        root->left = insertRec(root->left, to_insert, root);
    } else {
        delete to_insert;
        return root;
    }

    //balance every node
    if (nodeIsRed(root->right) && !nodeIsRed(root->left)) {
        root = rotateLeft(root);
    }
    if (nodeIsRed(root->left) && nodeIsRed(root->left->left)) {
        root = rotateRight(root);
    }
    if (nodeIsRed(root->left) && nodeIsRed(root->right)) {
        alterNodeColors(root);
    }

    return root;
}



/*
 * Space sectors inorder traversal:
BLACK sector: 25LDS
RED sector: 37LDB
BLACK sector: 37LDF
BLACK sector: 18LDF
BLACK sector: 18LUF
BLACK sector: 0SSS
RED sector: 50SUB
BLACK sector: 18RUB
RED sector: 37RUF
RED sector: 45RDF
BLACK sector: 43RDF
BLACK sector: 25RUS
BLACK sector: 70RUF

Space sectors preorder traversal:
BLACK sector: 0SSS
BLACK sector: 18LDF
RED sector: 37LDB
BLACK sector: 25LDS
BLACK sector: 37LDF
BLACK sector: 18LUF
BLACK sector: 25RUS
RED sector: 37RUF
BLACK sector: 18RUB
RED sector: 50SUB
BLACK sector: 43RDF
RED sector: 45RDF
BLACK sector: 70RUF

Space sectors postorder traversal:
BLACK sector: 25LDS
BLACK sector: 37LDF
RED sector: 37LDB
BLACK sector: 18LUF
BLACK sector: 18LDF
RED sector: 50SUB
BLACK sector: 18RUB
RED sector: 45RDF
BLACK sector: 43RDF
RED sector: 37RUF
BLACK sector: 70RUF
BLACK sector: 25RUS
BLACK sector: 0SSS
 * */

void SpaceSectorLLRBT::displaySectorsInOrder() {
    cout << "Space sectors inorder traversal:" << endl;
    displayINO(root);
    cout << endl;
}
void SpaceSectorLLRBT::displayINO(Sector *node) {
    if (node == nullptr) {
        return;
    }
    displayINO(node->left);
    cout << (node->color ? "RED" : "BLACK") << " sector: " << node->sector_code << endl;
    displayINO(node->right);

}

void SpaceSectorLLRBT::displayPOST(Sector *node) {
    if (node == nullptr) {
        return;
    }
    displayPOST(node->left);
    displayPOST(node->right);
    cout << (node->color ? "RED" : "BLACK") << " sector: " << node->sector_code << endl;
}
void SpaceSectorLLRBT::displayPRE(Sector *node) {
    if (node == nullptr) {
        return;
    }
    cout << (node->color ? "RED" : "BLACK") << " sector: " << node->sector_code << endl;
    displayPRE(node->left);
    displayPRE(node->right);
}
void SpaceSectorLLRBT::displaySectorsPreOrder() {

    cout << "Space sectors preorder traversal:" << endl;
    displayPRE(root);
    cout << endl;
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors postorder traversal:" << endl;
    displayPOST(root);
    cout << endl;
}

std::vector<Sector*>& SpaceSectorLLRBT::findRec(std::vector<Sector*>& path, Sector* node) {
    if (node) {
        path.push_back(node);
        if (node->parent) findRec(path, node->parent);
    }
    return path;
}



std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path_to_goal, path_to_start, final_path;
    Sector* start_node = __ctr_PROTOCOL_API__["0SSS"]; // Assuming "0SSS" is the start node
    Sector* goal_node = __ctr_PROTOCOL_API__[sector_code];

    // If either start or goal is null, return empty path
    if (!goal_node || !start_node) return {};

    // Find paths to root from both start and goal
    path_to_start = findRec(path_to_start, start_node);
    path_to_goal = findRec(path_to_goal, goal_node);

    Sector* common_node = nullptr;
    for (auto& node_start : path_to_start) {
        for (auto& node_goal : path_to_goal) {
            if (node_start == node_goal) {
                common_node = node_start;
                break;
            }
        }
        if (common_node) break;
    }

    for (auto& node : path_to_start) {
        final_path.push_back(node);
        if (node == common_node) break;
    }
    for (auto it = path_to_goal.rbegin(); it != path_to_goal.rend(); ++it) {
        if (*it == common_node) continue; // Avoid duplicate common node
        final_path.push_back(*it);
    }

    return final_path;
}
void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
    //The stellar path to Dr. Elara: 0SSS->25RUS->37RUF->43RDF->45RDF
    //A path to Dr. Elara could not be found.
    if (path.empty()) {
        cout << "A path to Dr. Elara could not be found." << endl;
        return;
    }
    cout << "The stellar path to Dr. Elara: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->sector_code;
        if (i != path.size() - 1) {
            cout << "->";
        }
    }
}
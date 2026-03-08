#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

static const int MAX_SPACES = 40;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    MonopolySpace() : propertyName(""), propertyColor(""), value(0), rent(0) {}

    MonopolySpace(string propertyName, string propertyColor, int value, int rent)
    : propertyName(propertyName),
      propertyColor(propertyColor),
      value(value),
      rent(rent)
    {
    }

    bool isEqual(MonopolySpace other) {
        return propertyName == other.propertyName;
    }

    void print() {
        cout << this->propertyName << endl << this->propertyColor << endl << this->value << endl << this->rent << endl;
    }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
    T data;
    Node<T>* nextNode;
    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
    Node<T>* headNode;
    Node<T>* tailNode;

    // player cursor for traversal-based gameplay
    Node<T>* playerNode;
    //For Search
    Node<T>* current;
    Node<T>* previous;

    int nodeCount;
    int passGoCount;

public:
    CircularLinkedList() {
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }


    // -------------------------------
    // Board Construction Policy (Reminder)
    // -------------------------------
    // Spaces are added during board construction BEFORE gameplay.
    // You choose how to construct the board:
    // - hardcode spaces, read from file, or generate programmatically
    // The only non-negotiable requirement:
    // - enforce MAX_SPACES
    // - maintain circular integrity
    // -------------------------------

    // -------------------------------
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
    bool addSpace(T value) {
        if (nodeCount == MAX_SPACES) {
            cout << "No capacity for spaces" << endl;
            return false;
        }
        Node<T>* newNode = new Node<T>(value);

        if (headNode == nullptr) {
            // first node
            headNode = newNode;
            tailNode = newNode;
            playerNode = newNode;
            newNode->nextNode = headNode;
        } else {
            tailNode->nextNode = newNode;
            tailNode = newNode;
            tailNode->nextNode = headNode;
        }
        nodeCount++;
        return true;
    }

    // -------------------------------
    // Core B: Add Multiple Spaces at Once
    // -------------------------------
    int addMany(const vector<T>& values) {

        int added = 0;

        for (T val : values) {
            if (nodeCount != MAX_SPACES) {
                if (addSpace(val)) {
                    added++;
                }
            }
            else {
                break;
            }
        }
        return added;
    }

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    void movePlayer(int steps) {
        // TODO:
        // - Move playerNode forward 'steps' times, node-by-node
        // - Wrap naturally because list is circular
        // - Detect and track passing GO:
        //   increment passGoCount when a move crosses from tail back to head
        // - Must handle empty list safely

        if (playerNode == nullptr) { // if Player Node unassigned
            playerNode = headNode;
        } else {
            for (int i = 0; i = steps; i++) {
                playerNode = playerNode->nextNode;
            }
        }
        if (playerNode == headNode) {
            passGoCount++;
        }
        if (playerNode == tailNode) {
            headNode = playerNode->nextNode;
        }
        if (nodeCount == 0) {
            return;
        }

    }

    int getPassGoCount() {
        return passGoCount;
    }

    // -------------------------------
    // Core D: Controlled Board Display
    // -------------------------------
    void printFromPlayer(int count) {
        // TODO:
        // - Print exactly 'count' nodes starting from playerNode
        // - Must not infinite loop
        // - Must handle empty list
        // - Output must be deterministic and readable

        if (playerNode == nullptr) {
            cout << "No spaces found";
            return;
        }
        for (int i = 0; i < count; i++) {
            playerNode->data.print();
        }

    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    bool removeByName(string name) {
        // TODO:
        // - Delete FIRST matching node
        // - Must handle:
        //   - deleting head
        //   - deleting tail
        //   - deleting the only-node list
        // - Maintain circular link tail->next=head
        // - If playerNode points to deleted node, move playerNode to a safe node
        // - nodeCount--

        current = headNode;
        previous = tailNode;

        if (headNode->propertyName == name) {
            headNode = current->nextNode;
            current->nextNode = headNode;
            nodeCount--;
        }
        while (current->propertyName != name) {
            current = current->nextNode;
            previous = previous->nextNode;
        }
        if (current->propertyName == name) {
            previous->nextNode = current->NextNode;
            delete current;
            nodeCount--;
        }
        return true;
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(string color) {
        // TODO:
        // - Traverse ring exactly once
        // - Collect matching names in vector<string>
        // - Return matches

        vector<string> matches;
        current = headNode;
        current = current->nextNode;

        while (current != headNode) {
            if (current->propertyColor != color) {
                current = current->nextNode;
            }
            if (current->propertyColor == color) {
                matches.push_back(current->propertyName);
            }
        }

        return matches;
    }

    // -------------------------------
    // Edge-case helper: countSpaces O(n)
    // -------------------------------
    int countSpaces() {
        // TODO:
        // - Must be O(n), traverse exactly once with correct stop condition
        // - Do NOT rely on nodeCount for this method

        int count = 0;
        current = headNode;
        current = current->nextNode;
        while (current != headNode) {
            count++;
            current = current->nextNode;
        }
        return count;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        // TODO:
        // - Safely delete all nodes
        // - Tip: if tailNode exists, break the cycle first: tailNode->nextNode = nullptr
        // - Then delete like a normal singly linked list

        tailNode->nextNode = nullptr;
        current = headNode;
        int count = countSpaces();
        for (int i = 0; i = count; i++) {
            delete current;
            current = current->nextNode;
        }
    }
};

// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    CircularLinkedList<MonopolySpace> board;

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    // You decide how to build the board:
    // - hardcode spaces, load from file, or generate spaces programmatically
    // The only requirement: never exceed MAX_SPACES and keep the list circular.
    //
    // Example (hardcoded) usage:
    // vector<MonopolySpace> spaces;
    // spaces.push_back(MonopolySpace("GO","None",0,0));
    // ...
    // board.addMany(spaces);
    //
    // NOTE: This starter calls addSpace once to show the intended API,
    // but your final submission should build a meaningful board.
    board.addSpace(MonopolySpace("GO", "None", 0, 0));

    vector<MonopolySpace> spaces;

    ifstream filein("C:\\Users\\kailo\\CLionProjects\\CS210Project1\\monopoly_spaces.txt");
    if (filein.is_open()) {

        string line;

        while (getline(filein, line)) {
            string name;
            string color;
            int value;
            int rent;

            stringstream ss(line);

            getline(ss, name, ',');
            getline(ss, color, ',');

            string valueStr;
            string rentStr;

            getline(ss, valueStr, ',');
            getline(ss, rentStr, ',');

            value = stoi(valueStr);
            rent = stoi(rentStr);

            MonopolySpace space(name, color, value, rent);
            spaces.push_back(space);
        }
        filein.close();

        board.addMany(spaces);
    } else {
        cout << "Unable to open file" << endl;
    }


    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }

    // -------------------------------
    // Advanced Feature Demos (students choose path)
    // -------------------------------
    // Option A examples:
    // board.removeByName("Baltic Avenue");
    // vector<string> brownProps = board.findByColor("Brown");
    //
    // Option B example:
    // board.mirrorBoard();

    board.removeByName("Reading Railroad");
    vector<string> brownProps = board.findByColor("Brown");
    cout << brownProps[0] << endl;

    return 0;




}

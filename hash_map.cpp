//
//  main.cpp
//  HW4
//
//  Created by Jacob Sturges on 11/18/20.
//

#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int);

int nextPrime(int);

bool isPrime(int x) {
    if (x == 2 || x == 3) {
        return true;
    }
    if (x == 1 || x % 2 == 0) {
        return false;
    }
    for (int i = 3; i*i <= x; i+=2) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int nextPrime(int x) {
    if (x <= 1) {
        return 2;
    }
    
    bool found = false;
    
    while(!found) {
        x++;
        
        if(isPrime(x)) {
            found = true;
        }
    }
    return x;
}

class Node {
public:
    int key = NULL;
    char data = NULL;
    Node* next = nullptr;
    
    Node() {}
    
    Node(int k, char d) {
        key = k;
        data = d;
        Node* next = nullptr;
    }
    
    int getKey() {
        return key;
    }
    
    char getSatellite() {
        return data;
    }
};

int main() {
    
    int key, input, mod, searchKeys;
    char satellite;
    vector<int> vect;
    vector<char> vect2;
    vector<int> vect3;
    
    //freopen("enter directory here", "r", stdin);
    
    while (cin >> key) {
        if (key != -1) {
            vect.push_back(key);
        }
        else break;
    }
    
    while (cin >> satellite) {
        if (satellite != '*') {
            vect2.push_back(satellite);
        }
        else break;
    }
        
    cin >> input >> mod;
    
    while (cin >> searchKeys) {
        if (searchKeys != -1) {
            vect3.push_back(searchKeys);
        }
        else break;
    }
    
    switch(input) {
        case 0: {
            int max = *max_element(vect.begin(), vect.end());
            vector<char> data(max);
            for (int i = 0; i < data.size(); i++) {
                data[i] = '*';
            }
            for (int i = 0; i < vect.size(); i++) {
                data[vect[i]] = vect2[i];
            }
            for (int i = 0; i < vect3.size(); i++) {
                cout << data[vect3[i]] << " ";
            }
            break;
        }
        case 1: {
            
            int size = mod;
            
            // vect = all keys, vect2 = satellite, vect3 = search keys
            
            Node *data[size];
            for (int i = 0; i < size; i++) {
                data[i] = NULL;
                
            }
            for (int i = 0; i < vect.size(); i++) {
                Node* newNode = new Node(vect.at(i), vect2.at(i));
                int newKey = vect.at(i) % size;
                
                if (data[newKey] == NULL) {
                    data[newKey] = newNode;
                }
                else {
                    Node* temp = data[newKey];
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
            }
            
            // This is where you find each search key
            // You take any search key in vect3 and mod it with the given modulo in the file
            // Iterate through linked list to find a key
            
            for (int i = 0; i < vect3.size(); i++) {
                
                Node* temp1 = data[vect3.at(i) % size];
                bool isFound = false;
                while (temp1 != NULL) {
                    
                    if (temp1->key == vect3.at(i)) {
                        cout << temp1->data << " ";
                        isFound = true;
                        break;
                    }
                    else {
                        temp1 = temp1->next;
                    }
                }
                if (isFound == false) {
                    cout << "*" << " ";
                }
                else continue;
            }
            break;
        }
        case 2: {
            
            if (!isPrime(mod)) {
                mod = nextPrime(mod);
            }
            
            vector<char> data(vect.size()+1);
            for (int i = 0; i < data.size(); i++) {
                data[i] = '*';
            }
            
            for (int i = 0; i < vect.size(); i++) {
                int hashKey = vect.at(i) % mod;
                if (data[hashKey] == '*') {
                        data[hashKey] = vect2.at(i);
                }
                else {
                        //bool slotFound = false;
                    for (int j = 0; j < mod; j++) {
                        int t = ((hashKey + j * j) % mod);
                        if (data[t] == '*') {
                            data[t] = vect2.at(i);
                            break;
                        }
                    }
                }
            }
            for (int i = 0; i < vect3.size(); i++) {

                int currentKey = vect3[i];
                    
                    for (int j = 0; j < vect.size(); j++) {
                        if (currentKey == vect[j]) {
                            cout << vect2[j] << " ";
                            break;
                        }
                        else if (currentKey != vect[j] && j == vect.size() - 1) {
                            cout << "*" << " ";
                        }
                    }
            }
            break;
        }
}
}

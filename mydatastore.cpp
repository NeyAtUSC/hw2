#include "mydatastore.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <set>

using namespace std;

MyDataStore::MyDataStore() : products_(), users_() {  }

MyDataStore::~MyDataStore() {
    for (auto p : products_) {
        delete p;
    }
    for (auto u : users_) {
        delete u;
    }
}

void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);

    set<string> keywords = p->keywords();
    for (const string& keyword : keywords) {
        keywordMap_[keyword].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users_.push_back(u);
	userMap_[u->getName()] = u;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    set<Product*> resultSet;

    if (terms.empty()) return vector<Product*>();

    if (keywordMap_.find(terms[0]) != keywordMap_.end()) {
        resultSet = keywordMap_[terms[0]];
    }

    for (size_t i = 1; i < terms.size(); ++i) {
        if (keywordMap_.find(terms[i]) != keywordMap_.end()) {
            if (type == 0) {
                set<Product*> temp;
                set_intersection(resultSet.begin(), resultSet.end(),
                                 keywordMap_[terms[i]].begin(), keywordMap_[terms[i]].end(),
                                 inserter(temp, temp.begin()));
                resultSet = temp;
            } else {
                set_union(resultSet.begin(), resultSet.end(),
                          keywordMap_[terms[i]].begin(), keywordMap_[terms[i]].end(),
                          inserter(resultSet, resultSet.begin()));
            }
        }
    }

    return vector<Product*>(resultSet.begin(), resultSet.end());
}

void MyDataStore::dump(ostream& ofile) {
    ofile << "products" << endl;
    for (auto product : products_) {
        product->dump(ofile);
    }

    ofile << "users" << endl;
    for (auto user : users_) {
        user->dump(ofile);
    }
}

void MyDataStore::addToCart(User* user, Product* p) {
    userCart_[user].insert(p);
}

void MyDataStore::viewCart(User* user) {
    if (userCart_.find(user) != userCart_.end()) {
        cout << "Cart contents for user " << user->getName() << ":" << endl;
        for (auto product : userCart_[user]) {
            cout << product->displayString() << endl;
        }
    } else {
        cout << "Cart is empty!" << endl;
    }
}

void MyDataStore::checkout(User* user) {
    if (userCart_.find(user) != userCart_.end()) {
        for (auto product : userCart_[user]) {
            product->subtractQty(1);
        }
        userCart_[user].clear();
        cout << "Thank you for your purchase!" << endl;
    } else {
        cout << "Cart is empty!" << endl;
    }
}

User* MyDataStore::getUserByUsername(const std::string& username) {
    // Iterate through the vector of users to find the matching user
    auto it = std::find_if(users_.begin(), users_.end(), 
                           [&username](User* user) {
                               return user->getName() == username;  // Assuming User has a getUsername() method
                           });

    // If the user was found, return the User*, otherwise return nullptr
    if (it != users_.end()) {
        return *it;
    }
    return nullptr;  // User not found
}
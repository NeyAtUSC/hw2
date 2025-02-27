#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>

#include "product.h"
#include "user.h"

#include "datastore.h"

class MyDataStore : public DataStore {
	public:
		MyDataStore();
		virtual ~MyDataStore();

		void addProduct(Product* p);
		void addUser(User* u);

		void addToCart(User* user, Product* p);
		void viewCart(User* user);
		void checkout(User* user);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);

		void dump(std::ostream& ofile);

		User* getUserByUsername(const std::string& username);
	private:
		std::vector<Product*> products_;
		std::vector<User*> users_;
		std::map<std::string, std::set<Product*>> keywordMap_;
		std::map<User*, std::set<Product*>> userCart_;
		std::map<std::string, User*> userMap_;
};

#endif
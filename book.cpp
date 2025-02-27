#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author) : Product(category, name, price, qty) {
	ISBN_ = ISBN;
	author_ = author;
}

string Book::displayString() const {
	std::stringstream out;
	out << name_ << ' ' << author_ << ' ' << ISBN_ << ' ' << price_ << ' ' << qty_;
	return out.str();
}

std::set<std::string> Book::keywords() const {
	std::set<string> out;

	std::set<string> nameKeys = parseStringToWords(name_);
	out.insert(nameKeys.begin(), nameKeys.end());

	std::set<string> authorKeys = parseStringToWords(author_);
	out.insert(authorKeys.begin(), authorKeys.end());

	out.insert(ISBN_);
	
	return out;
}

void Book::dump(ostream& os) const {
	Product::dump(os);
	os << author_ << "\n" << ISBN_ << endl; 
}

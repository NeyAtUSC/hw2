#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : Product(category, name, price, qty) {
	size_ = size;
	brand_ = brand;
}

string Clothing::displayString() const {
	stringstream out;
	out << name_ << ' ' << size_ << ' ' << brand_ << ' ' << price_ << ' ' << qty_;
	return out.str();
}

std::set<std::string> Clothing::keywords() const {
	std::set<string> out;

	std::set<string> nameKeys = parseStringToWords(name_);
	out.insert(nameKeys.begin(), nameKeys.end());

	std::set<string> sizeKeys = parseStringToWords(size_);
	out.insert(sizeKeys.begin(), sizeKeys.end());

	out.insert(brand_);
	return out;
}

void Clothing::dump(ostream& os) const {
	Product::dump(os);
	os << size_ << "\n" << brand_ << endl; 
}

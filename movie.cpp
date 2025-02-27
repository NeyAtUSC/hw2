#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product(category, name, price, qty) {
	genre_ = genre;
	rating_ = rating;
}

string Movie::displayString() const {
	stringstream out;
	out << name_ << ' ' << genre_ << ' ' << rating_ << ' ' << price_ << ' ' << qty_;
	return out.str();
}

std::set<std::string> Movie::keywords() const {
	std::set<string> out;

	std::set<string> nameKeys = parseStringToWords(name_);
	out.insert(nameKeys.begin(), nameKeys.end());

	std::set<string> genreKeys = parseStringToWords(genre_);
	out.insert(genreKeys.begin(), genreKeys.end());

	out.insert(rating_);

	return out;
}

void Movie::dump(ostream& os) const {
	Product::dump(os);
	os << genre_ << "\n" << rating_ << endl; 
}

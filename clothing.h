#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "product.h"

class Clothing : public Product {
	public:
		Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
	protected:
		std::string brand_;
		std::string size_;
};

#endif
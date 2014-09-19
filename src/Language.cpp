
#include "Language.hpp"

using namespace mksrc;

void Language::addSuffix(int index, const std::string &suffix) {
	this->suffix[index].push_back(suffix);
}

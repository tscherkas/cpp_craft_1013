#include "VectorIntMinMax.h"

VectorIntMinMax::VectorIntMinMax():
min_(-1),
max_(1) {

}

VectorIntMinMax::VectorIntMinMax(const std::vector<int>& data):
	min_(-1),
	max_(1),
	data_(data){

}

VectorIntMinMax::~VectorIntMinMax() {
	min_ = data_[0];
	max_ = data_[0];

	for(std::vector<int>::const_iterator it = data_.begin() + 1; it < data_.end(); ++it){
		min_ = std::min(min_, *it);
		max_ = std::max(max_, *it);
	}

	std::cout << "vectorMinMax:\tmin" << getMin() << " max" << getMax() << std::endl;
}

void VectorIntMinMax::process() {
}

void VectorIntMinMax::setData(const std::vector<int>& data){
	data_ = data;
}

int VectorIntMinMax::getMin() {
	return min_;
}

int VectorIntMinMax::getMax() {
	return max_;
}

#include "solution.h"

void task4_5::solution::render(){
	for(size_t i = 0; i < data_.size(); i++){
		for(size_t j = 0; j < data_[i].size(); j++){
			std::cout << data_[i][j] << " ";
		}
		std::cout << std::endl;
	}
	//std::copy(data[i].begin(), data[i].end(), iostream)
}

task4_5::solution::solution( const data_type& data ):
	data_(data)
{

}

int task4_5::solution::get_min() const
{
	return 0;
}
int task4_5::solution::get_max() const
{
	return 0;
}

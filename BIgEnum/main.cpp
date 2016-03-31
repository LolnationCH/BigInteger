#include "b_int.h"
#include <time.h>


int main(){
	B_int c(58788787);
	B_int temp(58788787);
	std::cout << c.SchonhageStrassen(c, temp) << std::endl;
	std::cout << c * temp;

	std::cin.get();
	return 0;
}
#include "b_int.h"
#include <time.h>


int main(){
	B_int c(123);
	B_int temp(456);
	c.SchonhageStrassen(c, temp);

	std::cin.get();
	return 0;
}
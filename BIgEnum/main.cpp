#include "b_int.h"
#include <time.h>


int main(){
	B_int c("160000000000");
	B_int temp("19999999999999999999999999999999999999999999999999");
	/*clock_t t;
	t = clock();
	std::cout << c.SchonhageStrassen(c, temp) << std::endl;
	t = clock() - t;
	std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl;
	t = clock();
	std::cout << c * temp << std::endl;
	t = clock() - t;
	std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl;
	*/
	std::cout << c.isPrime();
	std::cin.get();
	return 0;
}
#include "b_int.h"
#include <time.h>


int main(){
	B_int c("587887875878878788888888888888888888888888888888888888888888587887875878878788888888888888888888888888888888888888888888");
	B_int temp("587887875878878788888888888888888888888888888888888888888888587887875878878788888888888888888888888888888888888888888888");
	clock_t t;
	t = clock();
	std::cout << c.SchonhageStrassen(c, temp) << std::endl;
	t = clock() - t;
	std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl;
	t = clock();
	std::cout << c * temp << std::endl;
	t = clock() - t;
	std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl;

	std::cin.get();
	return 0;
}
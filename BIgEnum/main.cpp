#include "b_int.h"
#include <time.h>


int main(){
	B_int c("88");
	B_int temp("88");
	clock_t t;
	t = clock();
	std::cout << c.SchonhageStrassen(c, temp) << std::endl;
	t = clock() - t;
	std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl;
	t = clock();
	std::cout << c * temp << std::endl;
	t = clock() - t;
	std::cout << ((float)t) / CLOCKS_PER_SEC << std::endl;
	
	//Je dois reverifier tous les opérateurs arithmétique de base
	std::cin.get();
	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#define INPUT_FROM_FILE (0) 
#if INPUT_FROM_FILE
#include <fstream>
#endif
int main(){
	long a, b;
#if INPUT_FROM_FILE
	std::ifstream ifs("test.txt");
#endif
#if INPUT_FROM_FILE
	ifs >> a >> b;
#else
	std::cin >> a >> b;
#endif
	std::cout << std::bitset<32>(a & b) << std::endl;
	std::cout << std::bitset<32>(a | b) << std::endl;
	std::cout << std::bitset<32>(a ^ b) << std::endl;
#if INPUT_FROM_FILE
#endif
	return 0;
}

/***
*      b_int.h - define the b_int class
*
*      Author : Clovis Hall�
*
*Purpose:
*       Allows programmers to manipulate
*		large integer numbers just like
*		with a int, long, unint64_t, size_t, etc...
*
*		Version 1.0
*
*       [Open Source]
*
Implemented:
	- Constructor with std::string, standard integer type, integer and size_t
	- Flux operator(<<,>>) for std::cin and std::cout
	- Fonction that gives a std::string of the number
	- Every arithemetic operators (+,-,*,/,%)
	- Increments (++,--)
	- The math function pow and sqrt has been added
	- Pseudo-Random generated number
	- Prime test of Miller-Rabin (probabilist if the number is bigger then 18�446�744�073�709�551�616)

To be implemented:
	-logic operator with every integer
****/


#include <iostream>
#include <deque>
#include <sstream>
#include <stdint.h>
#include <time.h>

#ifndef b_int_h
#define b_int_h

class B_int{
private:
	std::deque<uint8_t> digits;
	bool negatif;

	//Delete non-significant zero
	void retirerZero(){
		std::string temp = to_string();
		if (temp.size() == 1){
			return;
		}
		if (temp.at(0) == '-'){
			temp = temp.substr(1, temp.size());
			while (temp.at(0) == '0'){
				temp = temp.substr(1, temp.size());
			}
			temp = '-' + temp;
		}
		else{
			while (temp.at(0) == '0' && temp.size() != 1){
				temp = temp.substr(1, temp.size());
			}
		}
		*this = B_int(temp);
	}
	B_int powTen(size_t t){
		B_int c(10);
		if (t == 0)
			return B_int(1);
		for (size_t i = 0; i < t - 1; i++){
			c.digits.push_front(0);
		}
		return c;
	}
	static B_int sub(B_int a, B_int b){
		uint8_t take = 0;
		B_int c;
		c.digits.pop_back();
		if (b.size() < a.size()){
			b.digits.push_back(0);
		}
		for (size_t i = 0; i < b.size(); i++){
			uint8_t temp = (a.digits.at(i) - take) - b.digits.at(i);
			if (temp >= 10){
				take = 1;
				temp = 10 - (256 - temp);
			}
			else if (take == 1){
				take = 0;
			}
			c.digits.push_back(temp);
		}
		for (size_t i = b.size(); i < a.size(); i++){
			c.digits.push_back(a.digits.at(i));
		}
		c.retirerZero();
		return c;
	}
public:
	//Constructeur
	B_int(){ 
		digits.push_back(0);
		negatif = false; 
	}
	B_int(std::string temp){
		if (temp.at(0) == '-'){
			negatif = true;
			for (size_t i = 1; i < temp.size(); i++){
				digits.push_front(temp.at(i) - '0');
			}
		}
		else{
			negatif = false;
			for (size_t i = 0; i < temp.size(); i++){
				digits.push_front(temp.at(i) - '0');
			}
		}
	}
	B_int(long long val){
		std::string temp = std::to_string(val);
		if (temp.at(0) == '-'){
			negatif = true;
			for (size_t i = 1; i < temp.size(); i++){
				digits.push_front(temp.at(i) - '0');
			}
		}
		else{
			negatif = false;
			for (size_t i = 0; i < temp.size(); i++){
				digits.push_front(temp.at(i) - '0');
			}
		}
	}
	B_int(const B_int& copy){
		digits = copy.digits;
		negatif = copy.negatif;
	}

	//Function
	std::string to_string(){
		std::string Stream = "";
		if (negatif){
			Stream += '-';
		}
		for (size_t i = digits.size(); i >= 1; i--){
			Stream += std::to_string(digits.at(i - 1));
		}
		return Stream;
	}
	size_t size(){ 
		return digits.size();
	}
	void timesTen(size_t t){
		for (size_t i = 0; i < t; i++){
			digits.push_front(0);
		}
	}
	uint8_t first(){
		return digits.at(digits.size() - 1);
	}
	B_int last(){
		B_int c = *this;
		c.digits.pop_back();
		return c;
	}

	/*Flux Operator*/
	friend std::ostream& operator<<(std::ostream& Stream, B_int& Obj){
		Stream << Obj.to_string();
		return Stream;
	}
	friend std::istream& operator>>(std::istream& Stream, B_int& Obj){
		std::string temp;
		Stream >> temp;
		Obj = temp;
		Stream.ignore();
		return Stream;
	}

	/*Increments*/
	B_int operator++(){
		B_int temp = (*this + B_int(1));
		negatif = temp.negatif;
		digits = temp.digits;
		return temp;
	} //i++
	B_int operator--(){
		B_int temp = (*this - B_int(1));
		negatif = temp.negatif;
		digits = temp.digits;
		return temp;
	} //i--
	B_int operator++(int){
		B_int temp = *this;
		operator++();
		return temp;
	}//++i
	B_int operator--(int){
		B_int temp = *this;
		operator--();
		return temp;
	}//--i

	/*Affectator*/
	void operator=(B_int& a){
		digits = a.digits;
		negatif = negatif;
	}
	void operator=(std::string temp){
		B_int a(temp);
		digits = a.digits;
		negatif = negatif;
	}
	void operator=(long long temp){
		B_int a(temp);
		digits = a.digits;
		negatif = negatif;
	}

	/*Arithmetic operator*/
	friend B_int operator+(B_int a, B_int b){
		a.retirerZero(); b.retirerZero();
		if (a.negatif){
			return (b - a);
		}
		else if (b.negatif){
			return (a - b);
		}
		else if (a.digits.size() < b.digits.size()){
			return b + a;
		}
		else{
			B_int c;
			c.digits.pop_back();
			c.negatif = a.negatif;
			int sup = 0;
			//a + b
			for (size_t i = 0; i < b.digits.size(); i++){
				uint8_t temp = a.digits.at(i) + b.digits.at(i) + sup;
				if (temp > 9){
					temp -= 10;
					sup = 1;
				}
				else
					sup = 0;
				c.digits.push_back(temp);
			}
			//a
			for (size_t i = b.digits.size(); i < a.digits.size(); i++){
				uint8_t temp = a.digits.at(i) + sup;
				if (temp > 9){
					temp -= 10;
					sup = 1;
				}
				else
					sup = 0;
				c.digits.push_back(temp);
			}
			c.digits.push_back(sup);
			c.retirerZero();
			return c;
		}
	}
	friend B_int operator-(B_int a, B_int b){
		a.retirerZero(); b.retirerZero();
		if (b.negatif){
			B_int c(b);
			c.negatif = false;
			return (a + c);
		}
		if (a.negatif){
			B_int c(a);
			c.negatif = false;
			c = c + b;
			c.negatif = true;
			return c;
		}
		B_int c;
		if (a < b){
			c = sub(b, a);
			c.negatif = true;
			return c;
		}
		return sub(a, b);
	}
	friend B_int operator*(B_int a, B_int b){
		B_int c;
		for (size_t j = 0; j < a.digits.size(); j++){
			B_int temp;
			for (size_t i = 0; i < a.digits.at(j); i++){
				temp += b;
			}
			for (size_t i = 0; i < j; i++){
				temp.digits.push_front(0);
			}
			c += temp;
		}
		c.negatif = !(a.negatif == b.negatif);
		return c;
	}
	friend B_int operator/(B_int a, B_int b){
		if (b.digits.size() > a.digits.size()){
			return B_int(0);
		}

		B_int temp2(b);
		B_int push((a.digits.size() - b.digits.size()));
		for (size_t i = 0; B_int(i) < push; i++){
			temp2.digits.push_front(0);
		}
		B_int temp(a);
		B_int c;
		for (size_t i = 0; B_int(i) < push + B_int(1); i++){
			B_int r;
			while (temp >= temp2){
				temp = temp - temp2;
				r = r + B_int(1);
			}
			c.digits.push_front(r.digits.at(0));
			temp2.digits.pop_front();
		}
		c.negatif = !(a.negatif == b.negatif);
		c.retirerZero();
		return c;
	}
	friend B_int operator%(B_int a, B_int b){
		if (b > a){
			return b - a;
		}
		B_int temp2(b);
		B_int push((a.digits.size() - b.digits.size()));
		for (size_t i = 0; B_int(i) < push; i++){
			temp2.digits.push_front(0);
		}
		B_int temp(a);
		B_int c;
		for (size_t i = 0; B_int(i) < push + B_int(1); i++){
			B_int r;
			while (temp >= temp2){
				temp = temp - temp2;
				r = r + B_int(1);
			}
			temp2.digits.pop_front();
		}
		return temp;
	}

	B_int SchonhageStrassen(B_int& a, B_int& b){
		B_int c;
		std::deque<B_int> convulution = std::deque<B_int>(a.size() + b.size() - 1, { 0 });
		for (size_t i = 0; i < a.size(); i++){
			for (size_t j = 0; j < b.size(); j++){
				convulution[i + j] += a.digits.at(i) * b.digits.at(j);
			}
		}
		B_int carry;
		c.digits.pop_back();
		for (size_t i = 0; i < convulution.size(); i++){
			carry += convulution.at(i).digits.at(0);
			c.digits.push_back(carry.digits.at(0));
			carry.digits.pop_front();
			if (carry.size() == 0)
				carry.digits.push_back(0);
			for (size_t j = 1; j < convulution.at(i).digits.size(); j++){
				carry += powTen(j-1) * convulution.at(i).digits.at(j);
			}
		}
		for (size_t i = 0; i < carry.size(); i++){
			c.digits.push_back(carry.digits.at(i));
		}
		c.negatif = !(a.negatif == b.negatif);
		c.retirerZero();
		return c;
	}

	/*Arithmetic operator=*/
	B_int& operator+=(B_int b){
		B_int temp = (*this + b);
		negatif = temp.negatif;
		digits = temp.digits;
		return *this;
	}
	B_int& operator-=(B_int b){
		B_int temp = (*this - b);
		negatif = temp.negatif;
		digits = temp.digits;
		return *this;
	}
	B_int& operator*=(B_int b){
		B_int temp = (*this * b);
		negatif = temp.negatif;
		digits = temp.digits;
		return *this;
	}
	B_int& operator/=(B_int b){
		B_int temp = (*this / b);
		negatif = temp.negatif;
		digits = temp.digits;
		return *this;
	}

	/*Logic operator*/
	friend bool operator==(B_int& a, B_int& b){
		if (a.negatif != b.negatif)
			return false;
		if (a.digits.size() != b.digits.size())
			return false;
		else{
			for (size_t i = 0; i < a.digits.size(); i++){
				if (a.digits.at(i) != b.digits.at(i))
					return false;
			}
		}
		return true;
	}
	friend bool operator!=(B_int& a, B_int& b){
		return !(a == b);
	}
	friend bool operator>(B_int& a, B_int& b){
		if (a.digits.size() > b.digits.size())
			return true;
		else if (a.digits.size() < b.digits.size())
			return false;
		else{
			for (size_t i = 1; i < a.digits.size() + 1; i++){
				if (a.digits.at(a.digits.size() - i) > b.digits.at(a.digits.size() - i))
					return true;
				if (a.digits.at(a.digits.size() - i) < b.digits.at(a.digits.size() - i))
					return false;
			}
		}
		return false;
	}
	friend bool operator>=(B_int& a, B_int& b){
		if (a.digits.size() > b.digits.size())
			return true;
		else if (a.digits.size() < b.digits.size())
			return false;
		else{
			for (size_t i = 1; i < a.digits.size() + 1; i++){
				if (a.digits.at(a.digits.size() - i) > b.digits.at(a.digits.size() - i))
					return true;
				if (a.digits.at(a.digits.size() - i) < b.digits.at(a.digits.size() - i))
					return false;
			}
		}
		return true;
	}
	friend bool operator<=(B_int& b, B_int& a){
		if (a.digits.size() > b.digits.size())
			return true;
		else if (a.digits.size() < b.digits.size())
			return false;
		else{
			for (size_t i = 1; i < a.digits.size() + 1; i++){
				if (a.digits.at(a.digits.size() - i) > b.digits.at(a.digits.size() - i))
					return true;
				else if (a.digits.at(a.digits.size() - i) < b.digits.at(a.digits.size() - i))
					return false;
			}
		}
		return true;
	}
	friend bool operator<(B_int& b, B_int& a){
		if (a.digits.size() > b.digits.size())
			return true;
		else if (a.digits.size() < b.digits.size())
			return false;
		else{
			for (size_t i = 1; i < a.digits.size() + 1; i++){
				if (a.digits.at(a.digits.size() - i) > b.digits.at(a.digits.size() - i))
					return true;
				else if (a.digits.at(a.digits.size() - i) < b.digits.at(a.digits.size() - i))
					return false;
			}
		}
		return false;
	}

	/*Math Fontion*/
	B_int sqrt(){
		B_int c = *this;

		if (c.size() % 2 != 0){ //Need a even number of digits
			c.digits.push_back(0);
		}

		B_int p;
		B_int d;
		B_int res;
		uint8_t x = 0;
		size_t limit = c.size() / 2;

		for (size_t i = 0; i < limit; i++){
			d = res.to_string() + //Get first two digits
				std::to_string(c.digits.at(c.size() - ((2 * i) + 1))) + std::to_string(c.digits.at(c.size() - ((2 * i) + 2))); 
			d.retirerZero(); //Just in case

			while ((B_int(20) * p * B_int(x)) + B_int((x * x)) <= d && x <= 10){
				x++;
			}
			x--;
			B_int temp = x;

			for (size_t j = 0; j < i; j++){
				temp = temp * B_int(10);
			}
			res = d - ((B_int(20) * p * B_int(x)) + B_int((x * x)));
			p = p + temp;
		}
		return p;
	}

	B_int pow(size_t t){
		B_int temp2 = *this;
		for (size_t i = 0; i < t - 1; i++){
			temp2 *= temp2;
		}
		return temp2;
	}

	/*
		If you want the Miller-Rabin with a pseudo-random generated number, send in parameter true
	*/
	bool isPrime(bool cond = false){
		size_t i = 1;
		if (cond){
			B_int a;
			bool test = true;
			while (test && i < 10 + 1)
			{
				a = random(2, *this - 2);
				test = Rabin(a);
				std::cout << ++i << " ";
			}
			return test;
		}
		std::deque <uint8_t> list = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
		for (int i = 0; i < list.size(); i++){
			if (!(Rabin(list.at(i))))
				return false;
		}
		return true;
	}
	
	bool Rabin(B_int a){
		if (*this == B_int(2))
			return true;
		B_int p, e, m, i, k;

		e = *this - 1;
		m = e;
		B_int temp = e % 2;
		for (k = 0; e % 2 == B_int(0); k++)
			e = e / 2;

		for (p = 1; e > B_int(0); e = e / 2) {
			if (e % 2 != B_int(0))
				p = (p * a) % *this;
			a = (a * a) % *this;
		}
		if (p == B_int(1)) return true;

		for (i = 0; i < k; i++) {
			if (p == m) return true;
			if (p == B_int(1)) return false;
			p = (p * p) % *this;
		}
		return false;
	}

	B_int random(B_int start, B_int end){
		clock_t time = clock();
		B_int c = ((((B_int)start) * (int)time) + 1);
		c =  (c % (end - 1));
		return c;
	}

	//From this point, there nothing really special about the code
	//There is no point in reading further
	//Why are you still reading?

	/*Constructeur Other*/
	B_int(long val){
		B_int temp((long long)val);
		digits = temp.digits;
		negatif = temp.negatif;
	}
	B_int(uint8_t val){
		B_int temp((long long)val);
		digits = temp.digits;
		negatif = temp.negatif;
	}
	B_int(int8_t val){
		B_int temp((long long)val);
		digits = temp.digits;
		negatif = temp.negatif;
	}
	B_int(uint16_t val){
		B_int temp((long long)val);
		digits = temp.digits;
		negatif = temp.negatif;
	}
	B_int(int16_t val){
		B_int temp((long long)val);
		digits = temp.digits;
		negatif = temp.negatif;
	}
	B_int(int32_t val){
		B_int temp((long long)val);
		digits = temp.digits;
		negatif = temp.negatif;
	}
	B_int(uint64_t val){
		B_int temp((long long)val);
		digits = temp.digits;
		negatif = temp.negatif;
	}
	B_int(size_t val){
		std::string temp = std::to_string(val);
		negatif = false;
		for (size_t i = 0; i < temp.size(); i++){
			digits.push_front(temp.at(i) - '0');
		}
	}
	
	/*Arithmetic operator*/ 
	friend B_int operator+(B_int a, long b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, long b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, long b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, long b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, long b){
		return a % B_int(b);
	}

	friend B_int operator+(B_int a, long long b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, long long b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, long long b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, long long b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, long long b){
		return a % B_int(b);
	}

	friend B_int operator+(B_int a, uint8_t b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, uint8_t b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, uint8_t b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, uint8_t b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, uint8_t b){
		return a % B_int(b);
	}

	friend B_int operator+(B_int a, int8_t b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, int8_t b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, int8_t b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, int8_t b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, int8_t b){
		return a % B_int(b);
	}

	friend B_int operator+(B_int a, uint16_t b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, uint16_t b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, uint16_t b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, uint16_t b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, uint16_t b){
		return a % B_int(b);
	}

	friend B_int operator+(B_int a, int16_t b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, int16_t b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, int16_t b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, int16_t b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, int16_t b){
		return a % B_int(b);
	}

	friend B_int operator+(B_int a, int32_t b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, int32_t b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, int32_t b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, int32_t b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, int32_t b){
		return a % B_int(b);
	}

	friend B_int operator+(B_int a, uint64_t b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, uint64_t b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, uint64_t b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, uint64_t b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, uint64_t b){
		return a % B_int(b);
	}

	friend B_int operator+(B_int a, size_t b){
		return a + B_int(b);
	}
	friend B_int operator-(B_int a, size_t b){
		return a - B_int(b);
	}
	friend B_int operator*(B_int a, size_t b){
		return a * B_int(b);
	}
	friend B_int operator/(B_int a, size_t b){
		return a / B_int(b);
	}
	friend B_int operator%(B_int a, size_t b){
		return a % B_int(b);
	}
};

#endif
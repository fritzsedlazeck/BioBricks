/*
 * structs.h
 *
 *  Created on: Nov 27, 2018
 *      Author: sedlazec
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <string.h>
#include <vector>
using namespace std;


struct chromosome_str{
	std::string name;
	std::string sequence;
};

struct regions_str{
	std::string chr;
	bool p1; //false = p2
	int start;
	int stop;
};


#endif /* STRUCTS_H_ */

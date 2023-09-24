#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <filesystem>

#ifndef FILESDEB_H
#define FILESDEB_H

typedef struct MyStructure {
private:
	std::string directory = "";
public:
	MyStructure(std::string ste);
	std::vector<std::string> getNm();
	void dister();
} MyStructure;

#endif // FILESDEB_H

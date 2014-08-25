#include "material.hpp"
#include "color.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

int main()
{
	std::vector<Material> mats;
	std::ifstream file("readMat.txt");
	int i=0;
	std::string input[100];
	while(file.is_open())
	{
		std::string temp;
		std::getline(file,temp,' ');
		if ((temp!="define")&&(temp!="material"))
		{
			input[i]=temp;
			std::cout<<input[i];
			++i;
		}
	}
	

	
}
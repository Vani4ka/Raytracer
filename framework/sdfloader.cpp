#include "sdfloader.hpp"

std::vector<Material> sdfloader::mats() const
{
	return mats_;
}

std::vector<Sphere> sdfloader::sphs()
{
	return sphs_;
}

std::vector<Box> sdfloader::bx()
{
	return bx_;
}

std::vector<Light> sdfloader::li()
{
	return li_;
}

template<typename T>
std::vector<T> sdfloader::vectorsort(std::vector<T> vec)
{
	if (vec.begin() != vec.end())
	{
		int j=0;
		while (j != vec.size()+1)
		{

			for (int i=0 ; i != vec.size()-1 ; ++i)
			{
				std::cout<<"Vector sort"<<std::endl;

				auto z1= vec[i].center().z;
				auto z2= vec[i+1].center().z;

				auto r1=vec[i].radius();
				auto r2=vec[i+1].radius(); 

				if ((z1+r1) > (z2+r2))
				{
					std::cout<<"Vector swap: "<< (z1+r1) <<", "<< (z2+r2) << std::endl;
					auto temp=vec[i];
					vec[i]=vec[i+1];
					vec[i+1]=temp;
				}
			}
			++j;
		}
	}
	else 
	{
		std::cout<<"empty Vector"<<std::endl;
	}	
	return vec;
}

void sdfloader::load()
{
	std::string filename("readMat.txt");
	std::ifstream file(filename);
	std::string temp;
	
	while(file.is_open())
	{	
		std::cout << "reading line of file " << filename << std::endl;
		getline(file, temp);
		
		if (temp.find("define material")!=std::string::npos) //Material
		{
			std::string input[13];
			size_t pos=0;
			int i=0;
			while((pos=temp.find(' ')) != std::string::npos)
			{
				input[i]=temp.substr(0, pos);
				temp.erase(0, pos + 1);
				++i;
			}
			std::cout << "reading material: " << input[2] << std::endl;
			
			Material mater={input[2],
				            {std::stof(input[3]), std::stof(input[4]), std::stof(input[5])}, 
				        	{std::stof(input[6]), std::stof(input[7]), std::stof(input[8])},
				            {std::stof(input[9]), std::stof(input[10]), std::stof(input[11])},
				        	std::stof(input[12])};
			
			sdfloader::mats_.push_back(mater);
		}

		if (temp.find("define light")!=std::string::npos)
		{
			std::string input[12];
			size_t pos=0;
			int i=0;
			while((pos=temp.find(' ')) != std::string::npos)
			{
				input[i]=temp.substr(0, pos);
				temp.erase(0, pos + 1);
				++i;
			}

			std::cout << "reading light: " << input[2] << std::endl;
			Light light={input[2],
				        {std::stof(input[3]), std::stof(input[4]), std::stof(input[5])}, 
				        {std::stof(input[6]), std::stof(input[7]), std::stof(input[8])},
				        {std::stof(input[9]), std::stof(input[10]), std::stof(input[11])}};
			
			sdfloader::li_.push_back(light); 
		}



		if (temp.find("define shape")!=std::string::npos)
		{
			if (temp.find("sphere")!=std::string::npos)
			{
				std::string input[9];
				size_t pos=0;
				int i=0;
				while((pos=temp.find(' ')) != std::string::npos)
				{
					input[i]=temp.substr(0,pos);
					temp.erase(0, pos + 1);
					++i;
				}

			    std::cout << "reading sphere: " << input[3] << std::endl;
			
			Sphere sp={ input[3],
						{std::stof(input[4]), std::stof(input[5]), std::stof(input[6])},
						std::stof(input[7]),
						input[8]};

			sdfloader::sphs_.push_back(sp);
			}

			if (temp.find("box")!=std::string::npos)
			{
				std::string input[11];
				size_t pos=0;
				int i=0;
				while((pos=temp.find(' ')) != std::string::npos)
				{
					input[i]=temp.substr(0,pos);
					temp.erase(0, pos + 1);
					++i;
				}

				std::cout << "reading box: " << std::endl;

			
			Box b={ input[3],
				   {std::stof(input[4]), std::stof(input[5]), std::stof(input[6])},
				   {std::stof(input[7]), std::stof(input[8]), std::stof(input[9])},
					input[10]};

			sdfloader::bx_.push_back(b);
			}

		}

		/*if (temp.find("transform")!= std::string::npos)
		{
			if (temp.find("translate")!=std::string::npos)
			{
				std::string input[6];
				size_t pos=0;
				int i=0;
				while((pos=temp.find(' ')) != std::string::npos)
				{
					input[i]=temp.substr(0,pos);
					temp.erase(0, pos + 1);
					++i;
				}

				std::cout << "reading transformation: " << input[2] << " of " << input[1] << std::endl;

				/*for (i=0; i < sphs_.size(); ++i)
				{
					if (sphs_[i].name()==input[1])
					{
						glm::vec3 tVector ={std::stof(input[3]), std::stof(input[4]), std::stof(input[5])};
						sphs_[i].translate(tVector);
					}
				}
			}

		}*/
		
		if (temp.find("end")!=std::string::npos)
		{
			std::cout << "finished reading file " << filename << std::endl;
			file.close();
		}
		
	}

	sphs_=vectorsort(sphs_);
}



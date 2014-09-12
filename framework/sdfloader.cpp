#include "sdfloader.hpp"

//Getter

std::vector<Material> const& sdfloader::materials() const
{
	return materials_;
}

std::vector<Light> const& sdfloader::lights() const
{
	return lights_;
}

std::vector<std::shared_ptr<Shape>> const& sdfloader::shapes() const
{
	return shapes_;
}

void sdfloader::load()
{
	std::string filename("scene.sdf");
	std::ifstream file(filename);
	std::string temp;
	while(file.is_open())
	{	
		getline(file, temp); //Lese Zeile vom File
		std::cout << "reading line of file " << filename << std::endl;
		
		if (temp.find("#")==std::string::npos) //Kommentarfunktion
		{

			if (temp.find("define material")!=std::string::npos) //Material
			{
				std::string input[13];
				size_t pos=0;
				int i=0;
				while((pos=temp.find(' ')) != std::string::npos) //Zerteiln des Strings 
				{
					input[i]=temp.substr(0, pos); //Speichern der Stücke im Array
					temp.erase(0, pos + 1);		  //Löschen des gespeicherten Teils + Leerzeile
					++i;
				}
				std::cout << "reading material: " << input[2] << std::endl;
				
				Material mater={input[2],
					            {std::stof(input[3]), std::stof(input[4]), std::stof(input[5])}, 
					        	{std::stof(input[6]), std::stof(input[7]), std::stof(input[8])},
					            {std::stof(input[9]), std::stof(input[10]), std::stof(input[11])},
					        	std::stof(input[12])};
				
				materials_.push_back(mater);
				std::cout<<"Vector-Size Material: "<<materials_.size()<<std::endl;

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
				
				lights_.push_back(light); 

				std::cout<<"Vector-Size Light: "<<lights_.size()<<std::endl;
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
				
				Sphere sphere={ input[3], 														//Name
							   input[8], 														//Materialname 
							   {std::stof(input[4]), std::stof(input[5]), std::stof(input[6])}, //Center
							    std::stof(input[7])};											//Radius

				
				shapes_.push_back(std::make_shared<Sphere>(sphere));

				std::cout<<"Vector-Size Shapes: "<<shapes_.size()<<std::endl;
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

				
				Box box={ input[3],																//Name
						  input[10],															//Materialname
					   		{std::stof(input[4]), std::stof(input[5]), std::stof(input[6])},	//Punkt 1
					   		{std::stof(input[7]), std::stof(input[8]), std::stof(input[9])}};	//Punkt 2

				shapes_.push_back(std::make_shared<Box>(box));
				std::cout<<"Vector-Size Shapes: "<<shapes_.size()<<std::endl;
				}

				if (temp.find("cylinder")!=std::string::npos)
				{
					std::string input[10];
					size_t pos=0;
					int i=0;
					while((pos=temp.find(' ')) != std::string::npos)
					{
						input[i]=temp.substr(0,pos);
						temp.erase(0, pos + 1);
						++i;
					}

					std::cout << "reading cylinder: " << std::endl;

				
				Cylinder cylinder={ input[3],															//Name
						  			input[9],															//Materialname
					   				{std::stof(input[4]), std::stof(input[5]), std::stof(input[6])},	//Center
					   				std::stof(input[7]),												//Höhe
					   				std::stof(input[8])};												//Radius

				shapes_.push_back(std::make_shared<Cylinder>(cylinder));
				std::cout<<"Vector-Size Shapes: "<<shapes_.size()<<std::endl;
				}

			}

			if (temp.find("transform")!= std::string::npos)
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

					for (auto const& i : shapes_)
					{
						if ( i-> name() == input[1]  )
						{
							i->setTransformed();	//Objekt i ist transformiert
								
								i->translate({std::stof(input[3]),
											  std::stof(input[4]),
											  std::stof(input[5])});
							

						}
					}


				}

				if (temp.find("scale")!=std::string::npos)
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


					for (auto const& i : shapes_)
					{
						if ( i-> name() == input[1]  )
						{
							i->setTransformed();
								
								i->scale({std::stof(input[3]),
										  std::stof(input[4]),
									      std::stof(input[5])});
							

						}
						std::cout<< i-> name() <<" | " << i -> isTransformed() << std::endl;
					}
				}

				if (temp.find("rotate")!=std::string::npos)
				{
					std::string input[7];
					size_t pos=0;
					int i=0;
					while((pos=temp.find(' ')) != std::string::npos)
					{
						input[i]=temp.substr(0,pos);
						temp.erase(0, pos + 1);
						++i;
					}

					std::cout << "reading transformation: " << input[2] << " of " << input[1] << std::endl;


					for (auto const& i : shapes_)
					{
						if ( i-> name() == input[1]  )
						{
							i->setTransformed();
								
								i->rotate(std::stof(input[3]),
										 {std::stof(input[4]),
										  std::stof(input[5]),
									      std::stof(input[6])});
							

						}
						std::cout<< i-> name() <<" | " << i -> isTransformed() << std::endl;
					}
				}

			}
			
			if (temp.find("end")!=std::string::npos)
			{
				std::cout << "finished reading file " << filename << std::endl;
				file.close();
			}
		}
		
	}
}



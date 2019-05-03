#pragma once


#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "../OBJ.h"
#include "../Mesh.h"

class MeshReader {
private:

	std::vector<std::string> split(const std::string& s, char delimiter){
		std::vector<std::string> tokens;

		std::stringstream ss_token(s);
		std::string token;
		while (std::getline(ss_token, token, delimiter)){
			tokens.push_back(token);
		}
		return tokens;
	}

public:
	MeshReader(){}

	Mesh* read(std::string filepath) {
		try {
			Mesh* mesh = new Mesh();

			std::ifstream file(filepath);
			file.exceptions(std::ifstream::badbit);

			unsigned int countGroup = 0;
			while (!file.eof()){
				std::string line;
				std::getline(file, line);

				std::stringstream ss_line(line);

				std::string command;
				ss_line >> command;
				
				if (command == "v") {
					float x, y, z;
					ss_line >> x >> y >> z;

					mesh->addVertice(x, y, z);
				}
				else if (command == "vt") {
					float x, y;
					ss_line >> x >> y;

					mesh->addTexture(x, y);
				}
				else if (command == "vn") {
					float x, y, z;
					ss_line >> x >> y >> z;

					mesh->addNormal(x, y, z);
				}
				else if (command == "g") {
					if (countGroup < 1) {
						std::string filepathTexture;
						ss_line >> filepathTexture;

						mesh->getGroup()->setPathFileTexture(filepathTexture);

						countGroup++;
					}
				}
				else if (command == "f") {
					std::string content;
					std::getline(ss_line, content);
					std::vector<std::string> vec_content = split(content, ' ');
					if (vec_content.size() == 5) { //faces quadradas
						std::string vertice1, vertice2, vertice3, vertice4;
						vertice1 = vec_content.at(1);
						vertice2 = vec_content.at(2);
						vertice3 = vec_content.at(3);
						vertice4 = vec_content.at(4);

						std::vector<std::string> vec_vertice1 = split(vertice1, '/');
						if (vec_vertice1.size() == 1) { // v

						}
						else if (vec_vertice1.size() == 2) { // v/t
							Group* group = mesh->getGroup();

							Face* face1 = new Face();
							face1->addIndexPosition(std::stoi(vec_vertice1.at(0)) - 1);
							face1->addIndexTexture(std::stoi(vec_vertice1.at(1)) - 1);

							std::vector<std::string> vec_vertice2 = split(vertice2, '/');
							face1->addIndexPosition(std::stoi(vec_vertice2.at(0)) - 1);
							face1->addIndexTexture(std::stoi(vec_vertice2.at(1)) - 1);

							std::vector<std::string> vec_vertice3 = split(vertice3, '/');
							face1->addIndexPosition(std::stoi(vec_vertice3.at(0)) - 1);
							face1->addIndexTexture(std::stoi(vec_vertice3.at(1)) - 1);

							group->addFace(face1);

							Face* face2 = new Face();
							face2->addIndexPosition(std::stoi(vec_vertice1.at(0)) - 1);
							face2->addIndexTexture(std::stoi(vec_vertice1.at(1)) - 1);

							face2->addIndexPosition(std::stoi(vec_vertice3.at(0)) - 1);
							face2->addIndexTexture(std::stoi(vec_vertice3.at(1)) - 1);

							std::vector<std::string> vec_vertice4 = split(vertice4, '/');
							face2->addIndexPosition(std::stoi(vec_vertice4.at(0)) - 1);
							face2->addIndexTexture(std::stoi(vec_vertice4.at(1)) - 1);

							group->addFace(face2);
						}
						else if (vec_vertice1.size() == 3) { // v//n ou v/t/n
							if (vec_vertice1.at(1) == "") { // v//n

							}
							else { //v/t/n
								Group* group = mesh->getGroup();

								Face* face1 = new Face();
								face1->addIndexPosition(std::stoi(vec_vertice1.at(0)) - 1);
								face1->addIndexTexture(std::stoi(vec_vertice1.at(1)) - 1);
								face1->addIndexNormal(std::stoi(vec_vertice1.at(2)) - 1);

								std::vector<std::string> vec_vertice2 = split(vertice2, '/');
								face1->addIndexPosition(std::stoi(vec_vertice2.at(0)) - 1);
								face1->addIndexTexture(std::stoi(vec_vertice2.at(1)) - 1);
								face1->addIndexNormal(std::stoi(vec_vertice2.at(2)) - 1);

								std::vector<std::string> vec_vertice3 = split(vertice3, '/');
								face1->addIndexPosition(std::stoi(vec_vertice3.at(0)) - 1);
								face1->addIndexTexture(std::stoi(vec_vertice3.at(1)) - 1);
								face1->addIndexNormal(std::stoi(vec_vertice3.at(2)) - 1);

								group->addFace(face1);

								Face* face2 = new Face();
								face2->addIndexPosition(std::stoi(vec_vertice1.at(0)) - 1);
								face2->addIndexTexture(std::stoi(vec_vertice1.at(1)) - 1);
								face2->addIndexNormal(std::stoi(vec_vertice1.at(2)) - 1);

								face2->addIndexPosition(std::stoi(vec_vertice3.at(0)) - 1);
								face2->addIndexTexture(std::stoi(vec_vertice3.at(1)) - 1);
								face2->addIndexNormal(std::stoi(vec_vertice3.at(2)) - 1);

								std::vector<std::string> vec_vertice4 = split(vertice4, '/');
								face2->addIndexPosition(std::stoi(vec_vertice4.at(0)) - 1);
								face2->addIndexTexture(std::stoi(vec_vertice4.at(1)) - 1);
								face2->addIndexNormal(std::stoi(vec_vertice4.at(2)) - 1);

								group->addFace(face2);
							}
						}
					}
					else if (vec_content.size() == 4) { // faces triangulares
						std::string vertice1, vertice2, vertice3;
						vertice1 = vec_content.at(1);
						vertice2 = vec_content.at(2);
						vertice3 = vec_content.at(3);

						std::vector<std::string> vec_vertice1 = split(vertice1, '/');

						if (vec_vertice1.size() == 1) { // v

						}
						else if (vec_vertice1.size() == 2) { // v/t
							Group* group = mesh->getGroup();

							Face* face = new Face();
							face->addIndexPosition(std::stoi(vec_vertice1.at(0)) - 1); 
							face->addIndexTexture(std::stoi(vec_vertice1.at(1)) - 1);

							std::vector<std::string> vec_vertice2 = split(vertice2, '/');
							face->addIndexPosition(std::stoi(vec_vertice2.at(0)) - 1);
							face->addIndexTexture(std::stoi(vec_vertice2.at(1)) - 1);

							std::vector<std::string> vec_vertice3 = split(vertice3, '/');
							face->addIndexPosition(std::stoi(vec_vertice3.at(0)) - 1);
							face->addIndexTexture(std::stoi(vec_vertice3.at(1)) - 1);

							group->addFace(face);
						}
						else if (vec_vertice1.size() == 3) { // v//n ou v/t/n
							if (vec_vertice1.at(1) == "") { // v//n
								Group* group = mesh->getGroup();

								Face* face = new Face();
								face->addIndexPosition(std::stoi(vec_vertice1.at(0)) - 1);
								face->addIndexNormal(std::stoi(vec_vertice1.at(2)) - 1);

								std::vector<std::string> vec_vertice2 = split(vertice2, '/');
								face->addIndexPosition(std::stoi(vec_vertice2.at(0)) - 1);
								face->addIndexNormal(std::stoi(vec_vertice2.at(2)) - 1);

								std::vector<std::string> vec_vertice3 = split(vertice3, '/');
								face->addIndexPosition(std::stoi(vec_vertice3.at(0)) - 1);
								face->addIndexNormal(std::stoi(vec_vertice3.at(2)) - 1);

								group->addFace(face);
							}
							else { // v/t/n
								Group* group = mesh->getGroup();

								Face* face = new Face();
								face->addIndexPosition(std::stoi(vec_vertice1.at(0)) - 1);
								face->addIndexTexture(std::stoi(vec_vertice1.at(1)) - 1);
								face->addIndexNormal(std::stoi(vec_vertice1.at(2)) - 1);

								std::vector<std::string> vec_vertice2 = split(vertice2, '/');
								face->addIndexPosition(std::stoi(vec_vertice2.at(0)) - 1);
								face->addIndexTexture(std::stoi(vec_vertice2.at(1)) - 1);
								face->addIndexNormal(std::stoi(vec_vertice2.at(2)) - 1);

								std::vector<std::string> vec_vertice3 = split(vertice3, '/');
								face->addIndexPosition(std::stoi(vec_vertice3.at(0)) - 1);
								face->addIndexTexture(std::stoi(vec_vertice3.at(1)) - 1);
								face->addIndexNormal(std::stoi(vec_vertice3.at(2)) - 1);

								group->addFace(face);
							}
						}
					}
					
				}
			}
			mesh->getGroup()->createVAOandTexture();
			
			file.close();

			return mesh;
		}
		catch (std::exception e) {
			std::cerr << "[ERRO] - " << filepath << ": " << e.what() << std::endl;
			return nullptr;
		}
	}
};

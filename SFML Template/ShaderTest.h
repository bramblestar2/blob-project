#pragma once
#include <SFML/Graphics.hpp>

class ShaderTest
{
public:
	ShaderTest();
	~ShaderTest();

	void drawShader(sf::RenderWindow* window);
	void loadVertex(std::string file);
	void loadFragment(std::string file);
	void loadBoth(std::string vertexFile, std::string fragmentFile);

	sf::Shader* getShader();
private:
	sf::Shader* shader;
};


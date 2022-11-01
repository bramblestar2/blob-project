#include "ShaderTest.h"

ShaderTest::ShaderTest()
{
	shader = nullptr;
	//shader->setUniform("position", 1.f);
}

ShaderTest::~ShaderTest()
{
	if (shader != nullptr)
		delete shader;
}

void ShaderTest::drawShader(sf::RenderWindow* window)
{
	if (window != nullptr && shader != nullptr)
	{
		sf::Texture t;
		t.create(600, 600);
		t.update(*window);

		sf::Sprite a;

		//a.setSize(sf::Vector2f(600,600));
		a.setTexture(t);
		
		shader->setUniform("txr", sf::Shader::CurrentTexture);
		shader->setUniform("xs", (float)window->getSize().x);
		shader->setUniform("ys", (float)window->getSize().y);
		shader->setUniform("r", 20.f);

		sf::RenderTexture b;
		b.create(600, 600);
		b.draw(a);

		a.setTexture(b.getTexture());
		//a.setFillColor(sf::Color(255,255,255,100));
		a.setColor(sf::Color(255, 255, 255, 50));
		a.setScale(1, -1);

		window->draw(a, shader);
	}
}

void ShaderTest::loadVertex(std::string file)
{
	shader->loadFromFile(file, sf::Shader::Vertex);
}

void ShaderTest::loadFragment(std::string file)
{
	shader->loadFromFile(file, sf::Shader::Fragment);
}

void ShaderTest::loadBoth(std::string vertexFile, std::string fragmentFile)
{
	if (shader != nullptr)
		delete shader;

	shader = new sf::Shader();

	shader->loadFromFile(vertexFile, fragmentFile);

	shader->setUniform("txr", sf::Shader::CurrentTexture);
	shader->setUniform("xs", 600.f);
	shader->setUniform("ys", 600.f);
	shader->setUniform("r", 50.f);
}

sf::Shader* ShaderTest::getShader()
{
	return shader;
}

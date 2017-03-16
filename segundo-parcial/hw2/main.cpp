
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <signal.h>


int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  sf::CircleShape shape(50);
  sf::Texture texture;
  if (!texture.loadFromFile("jaco.png")){
    printf("No se cargó la imagen");
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setPosition(sf::Vector2f(400, 400));
  int i = 0; 
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}

      window.clear();
      window.draw(sprite);
      window.display();

	//sprite.rotate(i);
      sprite.setPosition(sf::Vector2f(i, i*2));
      if(i > 400){
        i = 0;    
      }
      i++;
   }

  return 0;
}

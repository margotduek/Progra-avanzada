
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <signal.h>

void direction(int x);
void stop(int y);
void continue_(int y);

bool dir = true;
bool status = true;

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

  //Call handlers
  signal(SIGINT, stop);
  signal(SIGTSTP, continue_);
  signal(SIGALRM, direction);
  alarm(5);

  //Ignore Signals
  signal(SIGABRT,SIG_IGN);
  signal(SIGFPE,SIG_IGN);
  signal(SIGILL,SIG_IGN);
  signal(SIGSEGV,SIG_IGN);

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
      if(status){
        if(i > 400){
          i = 0;    
        }
        if(i < -400){
          i = 400;
        }
        if(dir){ 
          i++;
        }
        else if(!dir){
          i--;
        }
      }
    }
  
  return 0;
}



void direction(int x){
  alarm(5);
  signal(SIGALRM, direction);
  if(dir == true){
    dir = false;
  }else{
    dir = true;
  }
}
void stop(int y){
  status = false;
}
void continue_(int y){
  status = true;
}


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
  //Rendering a 800 * 800 window
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  //creating a circle to put a texture to put jacos' image
  sf::CircleShape shape(50);
  sf::Texture texture;
  if (!texture.loadFromFile("jaco.png")){
    printf("No se cargó la imagen");
  }
  //puting the jacos texture into a sprite
  sf::Sprite sprite;
  sprite.setTexture(texture);
  //Center jaco in the middle of the window
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
      //clear the window each time of the while
      window.clear();
      // draw the sprite again 
      window.draw(sprite);
      // display jacos' sprite again 
      window.display();

     
      sprite.setPosition(sf::Vector2f(i, i*2));
      // if status is false, then the program is in pause, check function stop and continue_
      if(status){
	//if the image goes out of the window start again 
        if(i > 400){
          i = 0;    
        }
        if(i < -400){
          i = 400;
        }
	// change direction, check function direction()
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


//direction handler
void direction(int x){
  alarm(5);
  signal(SIGALRM, direction);
  if(dir == true){
    dir = false;
  }else{
    dir = true;
  }
}
//pause handler
void stop(int y){
  status = false;
}
//continue handler 
void continue_(int y){
  status = true;
}

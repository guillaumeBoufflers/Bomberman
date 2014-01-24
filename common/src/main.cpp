#include 		"main.hh"

int 			main(int argc, char **argv)
{
  try {
    gtk_init(&argc, &argv);
    
    Bomberman	game;
    game.run();
  } catch (...) {
    std::cerr << "[Exception] : An unknown error occured" << std::endl;
  }
  return (0);
}

#include	"Render.hh"

Render::Render(int *size, int *players, int *rate, int *isActive)
{
  this->_size = size;
  this->_players = players;
  this->_rate = rate;
  this->_currentType = EMPTY;
  this->_isActive = isActive;
  int		iter = 4;
  while (iter <= 23)
    {
      this->_image[iter] = new sf::Image();
      iter++;
    }
  this->_image[4]->LoadFromFile("sprites/destructible_wall_text.png");
  this->_image[5]->LoadFromFile("sprites/wall_text.png");
  this->_image[6]->LoadFromFile("sprites/ground_text.png");
  this->_image[7]->LoadFromFile("sprites/random_text.png");
  this->_image[8]->LoadFromFile("sprites/bonus_speed_text.png");
  this->_image[9]->LoadFromFile("sprites/bonus_stock_text.png");
  this->_image[10]->LoadFromFile("sprites/flamme_text.png");
  this->_image[11]->LoadFromFile("sprites/mine_text.png");
  this->_image[12]->LoadFromFile("sprites/missile_text.png");
  this->_image[13]->LoadFromFile("sprites/radioactive_text.png");
  this->_image[14]->LoadFromFile("sprites/biological_text.png");
  this->_image[15]->LoadFromFile("sprites/piquante_text.png");
  this->_image[16]->LoadFromFile("sprites/remote_bomb.png");
  this->_image[17]->LoadFromFile("sprites/life_text.png");
  this->_image[18]->LoadFromFile("sprites/invincible_text.png");
  this->_image[19]->LoadFromFile("sprites/ghost_text.png");
  this->_image[20]->LoadFromFile("sprites/croix_rouge_text.png");
  this->_image[21]->LoadFromFile("sprites/random_text.png");
  this->_image[22]->LoadFromFile("sprites/player_text.png");
}

Render::~Render()
{
  int		iter = 4;
  while (iter <= 23)
    {
      delete (this->_image[iter]);
      iter++;
    }
}

int		Render::getActivity() const
{
  return (*this->_isActive);
}

void		Render::setCurrentType(ObjectType type)
{
  this->_currentType = type;
}

void		Render::setList(std::map<int, Object *> list)
{
  this->_list = list;
}

std::map<int, Object *>	Render::getList() const
{
  return (this->_list);
}

void		Render::setImg()
{
  sf::Sprite	*sprite;

  for (std::map<int, Object *>::iterator it = this->_list.begin(); it != this->_list.end(); ++it)
    {
      sprite = new sf::Sprite();
      sprite->SetImage(*(this->_image[(*it).second->getType()]));
      sprite->SetPosition((*it).second->getX(), (*it).second->getY());
      sprite->Resize(WINDOWSIZE / (*this->_size), WINDOWSIZE / (*this->_size));
      (*it).second->setSprite(sprite);
    }
}

void		Render::putNewObj(int x, int y, ObjectType type)
{
  int		xtmp;
  int		ytmp;

  for (std::map<int, Object *>::iterator it = this->_list.begin(); it != this->_list.end(); ++it)
    {
      xtmp = (*it).second->getX() + (WINDOWSIZE / (*this->_size));
      ytmp = (*it).second->getY() + (WINDOWSIZE / (*this->_size));
      if ((x > (*it).second->getX() && x < xtmp) && (y > (*it).second->getY() && y < ytmp))
	{
	  if ((*it).second->getBorder() == false && (*it).second->getType() != PLAYER)
	    {
	      (*it).second->getSprite()->SetImage(*(this->_image[type]));
	      (*it).second->getSprite()->Resize(WINDOWSIZE / (*this->_size), WINDOWSIZE / (*this->_size));
	      (*it).second->setType(type);
	    }
	}
    }
}

sf::RenderWindow	*Render::getWindow() const
{
  return (this->_app);
}

void		Render::sfmlLaunch()
{
  sf::RenderWindow app(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "mapGenerator");


  this->_app = &app;
  if ((*this->_isActive) == 0)
    {
      (*this->_isActive) = 1;
      while (app.IsOpened())
	{
	  sf::Event event;
	  while (app.GetEvent(event))
	    {
	      const sf::Input &input = app.GetInput();
	      if(event.Type == sf::Event::MouseButtonPressed)
		{
		  sf::Mouse::Button button = event.MouseButton.Button;
		  if (button == sf::Mouse::Left)
		    this->putNewObj(input.GetMouseX(), input.GetMouseY(), this->_currentType);
		  if (button == sf::Mouse::Right)
		    this->putNewObj(input.GetMouseX(), input.GetMouseY(), EMPTY);
		}
	      if (event.Type == sf::Event::Closed)
		{
		  (*this->_isActive) = 0;
		  app.Close();
		}
	    }
	  app.Clear();
	  for (std::map<int, Object *>::iterator it = this->_list.begin(); it != this->_list.end(); ++it)
	    app.Draw(*((*it).second->getSprite()));
	  app.Display();
	}
    }
}

void		*Render::run(void *data)
{
  Render	*render = (Render*) data;

  (void)data;
  render->setImg();
  render->sfmlLaunch();
  return (NULL);
}

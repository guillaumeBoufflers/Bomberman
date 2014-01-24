#include	"Gui.hh"

Gui		*gui;
Render		*render;

Gui::Gui()
{
  gui = this;
  this->_way[0] = 0;
  this->_way[1] = 1;
  this->_isActive = 0;
  this->_build = new Build(&this->_size, &this->_nbPlayers, &this->_occupancyRate, &this->_subRateWall, &this->_subRateUWall, &this->_subRateBonus);
  this->_render = new Render(&this->_size, &this->_nbPlayers, &this->_occupancyRate, &this->_isActive);
  render = this->_render;
  this->p_model = NULL;
  this->p_cell = NULL;
  this->_randMod = false;
}

Gui::~Gui()
{

}

std::string	Gui::getName() const
{
  return (this->_name);
}

int		Gui::getSize() const
{
  return (this->_size);
}

int		Gui::getNbPlayers() const
{
  return (this->_nbPlayers);
}

int		Gui::getOccupancyRate() const
{
  return (this->_occupancyRate);
}

void		Gui::saveLaunch()
{
  Save		*save;


  this->_name = gtk_entry_get_text(GTK_ENTRY(this->_entry[0]));
  if (this->_randMod == true)
    save = new Save(render->getList(), gui->getName(), gui->getSize(), gui->getNbPlayers(), gui->getOccupancyRate());
  else
    save = new Save(gui->getList(), gui->getName(), gui->getSize(), gui->getNbPlayers(), gui->getOccupancyRate());
  save = new Save(gui->getList(), gui->getName(), gui->getSize(), gui->getNbPlayers(), gui->getOccupancyRate());
  save->run();
}

void		Gui::save()
{
  gui->saveLaunch();
}

int		Gui::getActivity() const
{
  return (this->_isActive);
}

void		Gui::run(int ac, char **av)
{
  gtk_init(&ac, &av);
  this->createWindow();
  this->setWindowParam("mapGenerator", 300, 300, 300, 200);
  this->fillWindow();
  g_signal_connect(this->_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(this->_button[0], "clicked", G_CALLBACK(bridge), NULL);
  g_signal_connect(this->_button[1], "clicked", G_CALLBACK(map), NULL);
  g_signal_connect(this->_button[2], "clicked", G_CALLBACK(save), NULL);
  g_signal_connect(this->_button[3], "clicked", G_CALLBACK(reset), NULL);
  gtk_widget_show_all(this->_window);
  gtk_main();
}

GtkWidget	*Gui::getWindow() const
{
  return (this->_window);
}

void		Gui::testQuiting()
{
  sf::RenderWindow	  *app(gui->getRender()->getWindow());

  (*app).Close();
}

void		Gui::unsetSense(bool val)
{
  if ((this->_randMod == true && this->_size <= 100) || this->_randMod == false)
    gtk_widget_set_sensitive(this->p_combo, TRUE);
  else
    gtk_widget_set_sensitive(this->p_combo, FALSE);
  gtk_widget_set_sensitive(this->p_comboRate, val);
  gtk_widget_set_sensitive(this->p_comboWall, val);
  gtk_widget_set_sensitive(this->p_comboUWall, val);
  gtk_widget_set_sensitive(this->p_comboBonus, val);
  gtk_widget_set_sensitive(this->_label[0], val);
  gtk_widget_set_sensitive(this->_label[1], val);
  gtk_widget_set_sensitive(this->_label[2], val);
  gtk_widget_set_sensitive(this->_label[3], val);
  gtk_widget_set_sensitive(this->_label[4], val);
  this->_randMod = val;
}

void		Gui::reset()
{
  gui->unsetSense(false);
}

void		Gui::bridge()
{
  if (gui->getActivity() == 0)
    gui->unsetSense(true);
}

Render		*Gui::getRender() const
{
  return (this->_render);
}

GtkWidget	*Gui::getEntry(int id)
{
  return (this->_entry[id]);
}

bool		Gui::checkValidity(std::string s1) const
{
  unsigned int i = 0;

  while (i < s1.size())
    {
      if (!(s1[i] <= '9' && s1[i] >= '0'))
	return (false);
      i++;
    }
  return (true);
}

int		Gui::getWall() const
{
  return (this->_subRateWall);
}

int		Gui::getUWall() const
{
  return (this->_subRateUWall);
}

int		Gui::getBonus() const
{
  return (this->_subRateBonus);
}

bool		Gui::checkEntryValidity()
{
  if (this->_name.size() == 0)
    {
      errorWindow("You have to set a name for the map's file", "error");
      return (false);
    }
  else if (isNum(gtk_entry_get_text(GTK_ENTRY(this->_entry[1]))) == false ||
	   atoi(gtk_entry_get_text(GTK_ENTRY(this->_entry[1]))) < 10)
    {
      errorWindow("Size entry has to be a number higher than 10", "error");
      return (false);
    }
  else if (isNum(gtk_entry_get_text(GTK_ENTRY(this->_entry[2]))) == false)
    {
      errorWindow("NbPlayers entry has to be a number", "error");
      return (false);
    }
  else if (gui->getNbPlayers() > (gui->getSize() / 2))
    {
      errorWindow("you can not set more players than half the map's size", "error");
      return (false);
    }
  return (true);
}

bool		Gui::getRandMod() const
{
  return (this->_randMod);
}

GtkWidget	*Gui::getPCombo() const
{
  return (this->p_combo);
}

void		Gui::map(GtkButton  *button, int *way)
{
  pthread_t	thread;

  (void)button;
  (void)way;
  if (gui->getActivity() == 0)
    {
      gui->extractData();
      if (gui->checkEntryValidity() == true)
	{
	  if (gui->getRandMod() == true)
	    {
	      if ((gui->getWall()  * 10 + gui->getUWall() * 10 + gui->getBonus() * 10) != 100)
		{
		  errorWindow("the rate's sum has to be equal to 100", "error");
		  return ;
		}
	      else if (gui->getRandMod() == true && gui->getSize() > 1000)
		{
		  errorWindow("Size can not be higher than 1000 on Random Mode", "error");
		  return ;
		}
	      else  if (gui->getRandMod() == false && gui->getSize() > 100)
		{
		  errorWindow("Size can not be higher than 100 on Custom Mode", "error");
		  return ;
		}
	    }
	  if (gui->getNbPlayers() < 2)
	    {
	      errorWindow("At least 2 players have to be on the map", "error");
	      return ;
	    }
	  gui->setSensitive();
	  gui->getBuild()->init();
	  gui->getBuild()->setPlayer();
	  if (gui->getRandMod() == true)
	    gui->getBuild()->random();
	  gui->setList(gui->getBuild()->getList());
	  gui->getRender()->setList(gui->getList());
	  if (gui->getSize() > 100)
	    errorWindow("Graphical render is not available", "error");
	  else
	    pthread_create(&thread, NULL, Render::run, render);
	}
    }
}

std::map<int, Object *>	Gui::getList()
{
  return (this->_list);
}

void		Gui::setList(std::map<int, Object *> list)
{
  this->_list = list;
}

Build		*Gui::getBuild() const
{
  return (this->_build);
}

void		Gui::extractData()
{
  this->_name = gtk_entry_get_text(GTK_ENTRY(this->_entry[0]));
  this->_size = atoi(gtk_entry_get_text(GTK_ENTRY(this->_entry[1])));
  this->_nbPlayers = atoi(gtk_entry_get_text(GTK_ENTRY(this->_entry[2])));
  this->_occupancyRate = getActiveData(GTK_COMBO_BOX(this->p_comboRate)) * 10 + 20;
  this->_subRateWall = getActiveData(GTK_COMBO_BOX(this->p_comboWall));
  this->_subRateUWall = getActiveData(GTK_COMBO_BOX(this->p_comboUWall));
  this->_subRateBonus = getActiveData(GTK_COMBO_BOX(this->p_comboBonus));
}

void		Gui::createWindow()
{
  this->_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
}

void		Gui::setWindowParam(std::string name, int posX, int posY, int width, int height)
{
  gtk_window_move(GTK_WINDOW(this->_window), posX, posY);
  gtk_window_set_title(GTK_WINDOW(this->_window), name.c_str());
  gtk_window_set_default_size(GTK_WINDOW(this->_window), width, height);
}

void		Gui::initEntry()
{
  this->_entry[0] = gtk_entry_new();
  this->_entry[1] = gtk_entry_new();
  this->_entry[2] = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(this->_entry[0]), "Name");
  gtk_entry_set_text(GTK_ENTRY(this->_entry[1]), "Size");
  gtk_entry_set_text(GTK_ENTRY(this->_entry[2]), "Nb Players");
}

void		Gui::setSensitive()
{
  pthread_create(&thread, NULL, myThreadFunc, GTK_COMBO_BOX(p_combo));
}

int		Gui::getActiveData(GtkComboBox *p_combo)
{
  GtkTreeModel  *p_model = NULL;
  GtkTreeIter   iter;
  gint		index = 0;
  gchar 	*p_text;

  p_model = gtk_combo_box_get_model(p_combo);
  if (gtk_combo_box_get_active_iter(p_combo, &iter))
    gtk_tree_model_get(p_model, &iter, 0, &index, 1, &p_text, -1);
  return (index);
}

void		Gui::setObject(int obj)
{
  ObjectType		tmp;

  tmp = (ObjectType)obj;
  render->setCurrentType(tmp);
}

void            *Gui::myThreadFunc(void *data)
{
  GtkComboBox   *p_combo = (GtkComboBox*)data;

  (void)data;
  while (1)
    {
      gui->setObject(gui->getActiveData(p_combo));
      sleep(1);
    }
  return (NULL);
}

void		Gui::packIt(GtkWidget *widg, GtkWidget *obj, gboolean f, gboolean s)
{
  gtk_box_pack_start(GTK_BOX(widg), obj, f, s, 0);
}

void		Gui::addObjectInList(GtkListStore *model, GtkTreeIter iter, int id, const std::string name)
{
  gtk_list_store_append(model, &iter);
  gtk_list_store_set(model, &iter, 0, id, 1, name.data(), -1);
}

void		Gui::renderCell(GtkCellRenderer *cell, GtkWidget *combo, int id)
{
  cell = gtk_cell_renderer_text_new();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(combo), cell, FALSE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT(combo), cell, "text", id, NULL);
}

void		Gui::listOccupancyRate()
{
  this->p_modelRate = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
  this->p_comboRate = gtk_combo_box_new_with_model(GTK_TREE_MODEL(p_modelRate));
  this->renderCell(this->p_cellRate, this->p_comboRate, 1);
  this->addObjectInList(this->p_modelRate, this->iterRate, 1, "30%");
  this->addObjectInList(this->p_modelRate, this->iterRate, 2, "40%");
  this->addObjectInList(this->p_modelRate, this->iterRate, 3, "50%");
  this->addObjectInList(this->p_modelRate, this->iterRate, 4, "60%");
  this->addObjectInList(this->p_modelRate, this->iterRate, 5, "70%");
  this->addObjectInList(this->p_modelRate, this->iterRate, 6, "80%");
  this->addObjectInList(this->p_modelRate, this->iterRate, 7, "90%");
  gtk_combo_box_set_active(GTK_COMBO_BOX(this->p_comboRate), 0);
}

void		Gui::listFocusObj()
{
  this->p_model = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
  this->p_combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(p_model));
  this->renderCell(this->p_cell, this->p_combo, 1);
  this->addObjectInList(this->p_model, this->iter, 4, "Wall");
  this->addObjectInList(this->p_model, this->iter, 5, "Undestructible Wall");
  this->addObjectInList(this->p_model, this->iter, 6, "Floor");
  this->addObjectInList(this->p_model, this->iter, 8, "Bonus Speed");
  this->addObjectInList(this->p_model, this->iter, 9, "Bonus Stock");
  this->addObjectInList(this->p_model, this->iter, 10, "Bonus Range");
  this->addObjectInList(this->p_model, this->iter, 11, "Bonus Mine");
  this->addObjectInList(this->p_model, this->iter, 12, "Bonus Rocket");
  this->addObjectInList(this->p_model, this->iter, 13, "Bonus Nuclear Bomb");
  this->addObjectInList(this->p_model, this->iter, 14, "Bonus Biological Bomb");
  this->addObjectInList(this->p_model, this->iter, 15, "Bonus Spike Bomb");
  this->addObjectInList(this->p_model, this->iter, 16, "Bonus Remote Bomb");
  this->addObjectInList(this->p_model, this->iter, 17, "Bonus Life");
  this->addObjectInList(this->p_model, this->iter, 18, "Bonus Shield");
  this->addObjectInList(this->p_model, this->iter, 19, "Bonus Ghost");
  this->addObjectInList(this->p_model, this->iter, 20, "Bonus Health");
  this->addObjectInList(this->p_model, this->iter, 21, "Bonus Mystery");
  gtk_combo_box_set_active(GTK_COMBO_BOX(this->p_combo), 0);
}

void		Gui::subRateWall()
{
  this->p_modelWall = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
  this->p_comboWall = gtk_combo_box_new_with_model(GTK_TREE_MODEL(p_modelWall));
  this->renderCell(this->p_cellWall, this->p_comboWall, 1);
  this->addObjectInList(this->p_modelWall, this->iterWall, 0, "00%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 1, "10%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 2, "20%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 3, "30%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 4, "40%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 5, "50%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 6, "60%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 7, "70%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 8, "80%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 9, "90%");
  this->addObjectInList(this->p_modelWall, this->iterWall, 10, "100");
  gtk_combo_box_set_active(GTK_COMBO_BOX(this->p_comboWall), 2);
}

void		Gui::subRateUWall()
{
  this->p_modelUWall = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
  this->p_comboUWall = gtk_combo_box_new_with_model(GTK_TREE_MODEL(p_modelUWall));
  this->renderCell(this->p_cellUWall, this->p_comboUWall, 1);
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 0, "00%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 1, "10%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 2, "20%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 3, "30%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 4, "40%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 5, "50%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 6, "60%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 7, "70%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 8, "80%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 9, "90%");
  this->addObjectInList(this->p_modelUWall, this->iterUWall, 10, "100%");
  gtk_combo_box_set_active(GTK_COMBO_BOX(this->p_comboUWall), 6);
}

void		Gui::subRateBonus()
{
  this->p_modelBonus = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
  this->p_comboBonus = gtk_combo_box_new_with_model(GTK_TREE_MODEL(p_modelBonus));
  this->renderCell(this->p_cellBonus, this->p_comboBonus, 1);
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 0, "00%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 1, "10%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 2, "20%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 3, "30%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 4, "40%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 5, "50%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 6, "60%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 7, "70%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 8, "80%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 9, "90%");
  this->addObjectInList(this->p_modelBonus, this->iterBonus, 10, "100%");
  gtk_combo_box_set_active(GTK_COMBO_BOX(this->p_comboBonus), 2);
}

void		Gui::putIn()
{
  this->packIt(this->_vBox, this->_entry[0], TRUE, FALSE);
  this->packIt(this->_vBox, this->_entry[1], TRUE, FALSE);
  this->packIt(this->_vBox, this->_entry[2], TRUE, FALSE);
  this->packIt(this->_vBox, this->_hBox[0], TRUE, TRUE);
  this->_button[0] = gtk_button_new_with_label("Random");
  this->_button[1] = gtk_button_new_with_label("Launch");
  this->_button[2] = gtk_button_new_with_label("Save");
  this->_button[3] = gtk_button_new_with_label("Custom");
  this->packIt(this->_hBox[0], this->_button[0],TRUE, TRUE);
  this->packIt(this->_hBox[0], this->_button[3],TRUE, TRUE);
  this->packIt(this->_hBox[0], this->_button[1],TRUE, TRUE);
  this->packIt(this->_hBox[0], this->_button[2],TRUE, TRUE);
  this->listOccupancyRate();
  this->subRateWall();
  this->subRateUWall();
  this->subRateBonus();
  this->packIt(this->_vBox, this->_label[0], TRUE, FALSE);
  this->packIt(this->_vBox, this->p_comboRate, TRUE, FALSE);
  this->packIt(this->_vBox, this->_label[1], TRUE, FALSE);
  this->packIt(this->_vBox, this->p_comboWall, TRUE, FALSE);
  this->packIt(this->_vBox, this->_label[2], TRUE, FALSE);
  this->packIt(this->_vBox, this->p_comboUWall, TRUE, FALSE);
  this->packIt(this->_vBox, this->_label[3], TRUE, FALSE);
  this->packIt(this->_vBox, this->p_comboBonus, TRUE, FALSE);
  this->listFocusObj();
  this->packIt(this->_vBox, this->_label[4], TRUE, FALSE);
  this->packIt(this->_hBox[1], this->p_combo, TRUE, TRUE);
  gtk_box_pack_start(GTK_BOX(this->_vBox), this->_hBox[1], TRUE, TRUE, 0);
}

void		Gui::fillWindow()
{
  this->_vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(this->_window), this->_vBox);
  this->_hBox[0] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  this->_hBox[1] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  this->initEntry();
  this->_label[0] = gtk_label_new("Occupancy Rate :");
  this->_label[1] = gtk_label_new("Rate Wall :");
  this->_label[2] = gtk_label_new("Rate Undestructible Wall :");
  this->_label[3] = gtk_label_new("Rate Bonus :");
  this->_label[4] = gtk_label_new("Bonus List :");
  this->putIn();
  gtk_widget_set_sensitive(this->p_combo, FALSE);
  gtk_widget_set_sensitive(this->p_comboRate, FALSE);
  gtk_widget_set_sensitive(this->p_comboWall, FALSE);
  gtk_widget_set_sensitive(this->p_comboUWall, FALSE);
  gtk_widget_set_sensitive(this->p_comboBonus, FALSE);
  gtk_widget_set_sensitive(this->_label[0], FALSE);
  gtk_widget_set_sensitive(this->_label[1], FALSE);
  gtk_widget_set_sensitive(this->_label[2], FALSE);
  gtk_widget_set_sensitive(this->_label[3], FALSE);
  gtk_widget_set_sensitive(this->_label[4], FALSE);
}

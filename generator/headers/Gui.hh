#ifndef		__GUI_H__
#define		__GUI_H__

#include	<iostream>
#include	<vector>
#include	<string>
#include	<cstdlib>
#include	<pthread.h>
#include	<gtk/gtk.h>
#include	"Build.hh"
#include	"Render.hh"
#include	"../../common/headers/enum.hh"
#include	"Object.hh"
#include	"Save.hh"
#include	"errorWindow.hh"

bool		isNum(std::string str);

class		Render;

class		Gui
{
private:
  std::map<int, Object *>	_list;
  GtkWidget		*_window;
  GtkWidget		*_vBox;
  GtkWidget		*_hBox[2];
  GtkWidget		*_entry[4];
  GtkWidget		*_button[4];
  int			_way[2];
  Build			*_build;
  Render		*_render;
  std::string		_name;
  int			_size;
  int			_nbPlayers;
  int			_occupancyRate;
  GtkWidget		*_label[5];
  bool			_randMod;
  // focus Object
  GtkListStore		*p_model;
  GtkCellRenderer	*p_cell;
  GtkTreeIter		iter;
  GtkWidget		*p_combo;
  pthread_t		thread;
  // list occupancy rate
  GtkListStore		*p_modelRate;
  GtkCellRenderer	*p_cellRate;
  GtkTreeIter		iterRate;
  GtkWidget		*p_comboRate;
  //
  // list occupancy rate Destructible Wall
  GtkListStore		*p_modelWall;
  GtkCellRenderer	*p_cellWall;
  GtkTreeIter		iterWall;
  GtkWidget		*p_comboWall;
  //
  // list occupancy rate InDestructible Wall
  GtkListStore		*p_modelUWall;
  GtkCellRenderer	*p_cellUWall;
  GtkTreeIter		iterUWall;
  GtkWidget		*p_comboUWall;
  //
  // list occupancy rate Bonus
  GtkListStore		*p_modelBonus;
  GtkCellRenderer	*p_cellBonus;
  GtkTreeIter		iterBonus;
  GtkWidget		*p_comboBonus;
  //
  int			_subRateWall;
  int			_subRateUWall;
  int			_subRateBonus;
  int			_isActive;
  //
  int		getActiveData(GtkComboBox *p_combo);
  std::string	getName() const;
  int		getSize() const;
  int		getNbPlayers() const;
  int		getOccupancyRate() const;
  Render	*getRender() const;
  GtkWidget	*getEntry(int id);
  Build		*getBuild() const;
  int		getWall() const;
  int		getUWall() const;
  int		getBonus() const;
  int		getActivity() const;
  //
  void		setList(std::map<int, Object *> list);
  void		setObject(int obj);
  void		unsetSensitive();
  void		setSensitive();

  //
  void		addObjectInList(GtkListStore *model, GtkTreeIter iter, int id, const std::string name);
  void		saveLaunch();
  std::map<int, Object *>	getList();
  bool		checkValidity(std::string s1) const;
  void		extractData();
  void		createWindow();
  void	        setWindowParam(std::string name, int posX, int posY, int width, int height);
  void		putIn();
  void		initEntry();
  void		fillWindow();
  void		setTextIntoEntry();
  void		packIt(GtkWidget *widg, GtkWidget *obj, gboolean f, gboolean s);
  void		renderCell(GtkCellRenderer *cell, GtkWidget *combo, int id);
  void		listSize();
  void		listOccupancyRate();
  void		listFocusObj();
  void		subRateBonus();
  void		subRateUWall();
  void		subRateWall();
  bool		checkEntryValidity();
  void		unsetSense(bool val);
  bool		getRandMod() const;
  static void	reset();
  GtkWidget	*getPCombo() const;
  static void	testQuiting();
  GtkWidget	*getWindow() const;
public:
  Gui();
  ~Gui();
  /****/
  static void	bridge();
  static void   *myThreadFunc(void *data);
  static void	save();
  void		run(int ac, char **av);
  static void	map(GtkButton  *button, int *way);
  void		isClicAble(bool clic);
};

#endif

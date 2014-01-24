#include	"APhysicalObject.hh"
#include	"GameScene.hh"

APhysicalObject::APhysicalObject(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, ObjectType globalType) : _x(x * CASE_SIZE), _y(y * CASE_SIZE), _scale(scale), _angle(angle), _mesh(mesh),  _type(type), _globalType(globalType), _status(ALIVE)
{
  if (mesh != "")
    this->_model = gdl::Model::load(mesh);
}

APhysicalObject::APhysicalObject(TiXmlAttribute **attrib)
{
  this->_type = static_cast<ObjectType>((*attrib)->IntValue());
  (*attrib) = (*attrib)->Next();
  this->_x = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_y = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_scale = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  (*attrib)->QueryIntValue(&this->_angle);
  (*attrib) = (*attrib)->Next();
  this->_mesh = (*attrib)->Value();
  (*attrib) = (*attrib)->Next();
  this->_globalType = static_cast<ObjectType>((*attrib)->IntValue());
  (*attrib) = (*attrib)->Next();
  this->_status = (ObjectStatus)(*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  if (this->_mesh != "")
    this->_model = gdl::Model::load(this->_mesh);
}

APhysicalObject::~APhysicalObject()
{

}

void		APhysicalObject::setPosition(float x, float y)
{
  this->_x = x;
  this->_y = y;
}

float		APhysicalObject::getPosX() const
{
  return (this->_x);
}

float		APhysicalObject::getPosY() const
{
  return (this->_y);
}

void		APhysicalObject::setPositionCase(int x, int y)
{
  this->_x = x * CASE_SIZE;
  this->_y = y * CASE_SIZE;
}

int		APhysicalObject::getPosCaseX() const
{
  return ((this->_x + (CASE_SIZE / 2)) / CASE_SIZE);
}

int		APhysicalObject::getPosCaseY() const
{
  return ((this->_y + (CASE_SIZE / 2)) / CASE_SIZE);
}

void		APhysicalObject::setRotation(int angle)
{
  this->_angle = angle;
}

int		APhysicalObject::getRotation() const
{
  return (this->_angle);
}

void		APhysicalObject::setScale(int scale)
{
  this->_scale = scale;
}

int		APhysicalObject::getScale() const
{
  return (this->_scale);
}

void		APhysicalObject::setMesh(std::string &mesh)
{
  this->_mesh = mesh;
}
std::string	APhysicalObject::getMesh() const
{
  return (this->_mesh);
}

void		APhysicalObject::setType(ObjectType type)
{
  this->_type = type;
}

ObjectType	APhysicalObject::getType() const
{
  return (this->_type);
}

void		APhysicalObject::setGlobalType(ObjectType type)
{
  this->_globalType = type;
}

ObjectType	APhysicalObject::getGlobalType() const
{
  return (this->_globalType);
}


ObjectStatus	APhysicalObject::getStatus() const
{
  return (this->_status);
}

void		APhysicalObject::setStatus(ObjectStatus status)
{
  this->_status = status;
}

bool		APhysicalObject::canWalk(float x, float y)
{
  int ix = (x + (CASE_SIZE / 2)) / CASE_SIZE;
  int iy = (y + (CASE_SIZE / 2)) / CASE_SIZE;

  if (ix < 0 || iy < 0 || iy >= (int)GameScene::_map.size() || ix >= (int)GameScene::_map[0].size())
    return (false);
  if (GameScene::_map[iy][ix].front())
    {
      std::list<IPhysicalObject *>	tmp(GameScene::_map[iy][ix]);

      for (std::list<IPhysicalObject *>::iterator it = tmp.begin(); it != tmp.end(); ++it)
    	{
	       if (!(*it)->isReachable())
	         return (false);
      }
      return (true);
    }
  return (false);
}

bool    APhysicalObject::canWalkOutTo(float x, float y, int xA, int yA)
{
  int ix = (x + (CASE_SIZE / 2)) / CASE_SIZE;
  int iy = (y + (CASE_SIZE / 2)) / CASE_SIZE;

  if (xA == ix && yA == iy)
    return (true);
  if (ix < 0 || iy < 0 || iy >= (int)GameScene::_map.size() || ix >= (int)GameScene::_map[0].size())
    return (false);
  if (GameScene::_map[iy][ix].front())
    {
      std::list<IPhysicalObject *>  tmp(GameScene::_map[iy][ix]);

      for (std::list<IPhysicalObject *>::iterator it = tmp.begin(); it != tmp.end(); ++it)
      {
        if (!(*it)->isReachable())
          return (false);
      }
      return (true);
    }
  return (false);
}

TiXmlElement	*APhysicalObject::serialize()
{
  TiXmlElement	*ret = new TiXmlElement((this->_type - PLAYER < 0)?("OBJ"):((this->_type - BOMB < 0)?("PLAYER"):("BOMB")));
  ret->SetAttribute("type", this->_type);
  ret->SetAttribute("x", this->_x);
  ret->SetAttribute("y", this->_y);
  ret->SetAttribute("scale", this->_scale);
  ret->SetAttribute("angle", this->_angle);
  ret->SetAttribute("mesh", this->_mesh.c_str());
  ret->SetAttribute("globalType", this->_globalType);
  ret->SetAttribute("status", this->_status);
  return (ret);
}

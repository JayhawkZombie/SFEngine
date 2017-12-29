#ifndef TILE_H
#define TILE_H

#include <string>
class Tile
{
public:
	//constructor-destructor
	Tile();
	~Tile();

	//getters/setters
	std::string getSpriteBackground() const;
	std::string getSpriteForeground() const;
	bool getCanTravel() const;
	char getShow() const;

	void setSpriteBackground(std::string spriteBackground);
	void setSpriteForeground(std::string spriteForeground);
	void setCanTravel(bool canTravel);
	void setShow(char show);

	static int num;
private:
	std::string m_spriteBackground;
	std::string m_spriteForeground;
	bool m_canTravel;
	char m_show;
};

#endif

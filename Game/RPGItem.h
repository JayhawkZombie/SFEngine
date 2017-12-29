#ifndef RPG_ITEM_H
#define RPG_ITEM_H
#include <map>
#include <string>
class RPGItem
{
public:
	//constructor-destructor
	RPGItem();
	~RPGItem();

	//Getters-Setters
	std::string getName() const;
	std::string getDescription() const;
    std::string getTexture() const;
	int getValue() const;
	int getId() const;

	void setName(std::string name);
	void setDescription(std::string description);
    void setTexture(std::string texture);
	void setValue(int value);
	void setId(int id);

	//Other Methods
	static std::map<int, std::map<int, std::string>> TierNames();
	static std::map<int, int> tierValues();
	static std::map<int, int> tierBaseLevel();
	
	//	void InitializeRPGItem();
//	static int HowMany();//returns the number of items
//	static RPGItem* get();//returns a pointer to the
	//base of the array of length Num() that holds 
	//All of the RPGItem objects
private:
//	RPGItem* arrayBase;
//	static int num;
	std::string m_name;
	std::string m_description;
  std::string m_texture;
	int m_value;
	int m_id;
};
#endif

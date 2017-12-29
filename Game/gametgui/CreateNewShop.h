#ifndef CREATE_SHOP_H
#define CREATE_SHOP_H

#include <TGUI\TGUI.hpp>
#include "../Shop.h"

#include "Engine/Engine.h"
//need to optimize and debug
//need to read in textures
//add armor and weapons
//namespace Engine {
  class NewShopCreator
  {
  public:
    NewShopCreator() = default;
    ~NewShopCreator() = default;

    void CreateShopNode(Inventory pinv, Inventory sinv);

    void OpenTheme();
    void Close();

  protected:
    void Buy();
    void Sell();

    void TotalSellAmount(int index, int delta);
    void TotalBuyAmount(int index, int delta);

    void updateGold(); //update all the shop and player's expected golds
    void updateInventories(); //update the totals of the inventories;

    tgui::Theme::Ptr Theme;
    tgui::ChildWindow::Ptr ShopWindow;
    tgui::ChildWindow::Ptr PlayerWindow;

    tgui::Button::Ptr incOne;
    tgui::Button::Ptr decOne;
    tgui::Button::Ptr decAll;
    tgui::Button::Ptr incAll;
    tgui::Button::Ptr buttonBuy;
    tgui::Button::Ptr buttonSell;
    tgui::Button::Ptr buttonCancel;
    tgui::Button::Ptr buttonBack; //go back the shopkeep dialogue
    tgui::Picture::Ptr itemTexture;
    tgui::TextBox::Ptr shopDescription;
    tgui::ChatBox::Ptr shopName;
    tgui::ChatBox::Ptr shopAmt;
    tgui::TextBox::Ptr playerDescription;
    tgui::ChatBox::Ptr playerName;
    tgui::ChatBox::Ptr playerAmt;
    tgui::ChatBox::Ptr AmtSelling;
    tgui::ChatBox::Ptr AmtBuying;

    tgui::ChatBox::Ptr shopCost;
    tgui::ChatBox::Ptr playerCost;
    tgui::ChatBox::Ptr playerGold;
    tgui::ChatBox::Ptr shopGold;


    int textSize;
    int buttonPos;
    int m_numChoices;
    std::string m_contentText;
    std::string m_buttonText;
    std::string m_id;


    int* amtSell;
    int* amtBuy;

    std::vector<std::string> shopinv;
    std::vector<std::string> playerinv;
    std::vector<tgui::Button::Ptr> incdec;
    Useable** use_arr = NULL;
    Armor** armor_arr = NULL;
    Weapon** weapon_arr = NULL;

    int totalUseables = 0;
    int totalArmor = 0;
    int totalWeapons = 0;

    Inventory* pinven = NULL;
    Inventory* sinven = NULL;

    int sellMultiplier = 1;
    int buyMultiplier = 1;
    int totalBuyCost = 0;
    int totalSellCost = 0;
    std::vector<std::shared_ptr<std::string>> nodeIDs;

    sf::Vector2u WindowSize;
    std::shared_ptr<tgui::Gui> GUI;


  };

//}

#endif

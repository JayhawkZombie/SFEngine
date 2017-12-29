
#include "CreateNewShop.h"
#include <filesystem>

//namespace Engine {

  void NewShopCreator::CreateShopNode(Inventory pinv, Inventory sinv)
  {
    Theme = std::make_shared<tgui::Theme>("././SFEngine/Source/CoreFiles/UIThemes/UIDark.txt");
    GUI = GUI;
    OpenTheme();

    std::unique_ptr<ListReader> reader;
    reader = std::make_unique<ListReader>();
   
    use_arr = reader->readUseables("Game/ContentFiles/useable.txt");

    /*
    currently armor and weapon read-in don't work, not sure what their end product is supposed to look like
    armor_arr = reader.readArmor("Game/ContentFiles/armor.txt");
    weapon_arr = reader.readWeapons("Game/ContentFiles/weapon.txt");
    */
    totalUseables = reader->getNumUseables() - 1;
    //totalArmor = reader->getNumArmor();
    //totalWeapons = reader->getNumWeapons();

    //pinven = pinv;
    //sinven = sinv;

    pinven = new Inventory;
    sinven = new Inventory;
    amtSell = new int[totalUseables];
    amtBuy = new int[totalUseables];
    for (int i = 0; i < totalUseables; i++)
    {
      pinven->updateUseables(i, 1 + i);
      sinven->updateUseables(i, 2 + i);
      amtSell[i] = 0;
      amtBuy[i] = 0;
    }
    pinven->setGold(100);
    sinven->setGold(110);
    



    playerGold->addLine(std::to_string(pinven->getGold()));
    playerGold->addLine("0");
    playerGold->addLine(std::to_string(pinven->getGold()));
    shopGold->addLine(std::to_string(sinven->getGold()));
    shopGold->addLine("0");
    shopGold->addLine(std::to_string(sinven->getGold()));
    playerGold->setSize({ 60,70 });
    shopGold->setSize({ 60,70 });
    shopGold->setPosition({ 630,280 });
    playerGold->setPosition({ 280,280 });
    ShopWindow->add(playerGold);
    ShopWindow->add(shopGold);

    for (int i = 0; i < totalUseables; i++)
    {
      if (0 >= pinven->getUseables()[i])
      {
      }
      else
      {
        incOne = Theme->load("Button");
        decOne = Theme->load("Button");
        incOne->setText("+");
        decOne->setText("-");
        incOne->setSize({ 10,10 });
        decOne->setSize({ 10,10 });
        incOne->connect("clicked", [this, _i = i]() { this->TotalSellAmount(_i, 1); });
        decOne->connect("clicked", [this, _i = i]() { this->TotalSellAmount(_i, -1); });
        //incOne->connect("clicked", &NewShopCreator::TotalSellAmount, this, i, 1);
        //decOne->connect("clicked", &NewShopCreator::TotalSellAmount, this, i, -1);
        incOne->setPosition({ 10,(35 + i * 21) });
        decOne->setPosition({ 20,(35 + i * 21) });
        ShopWindow->add(incOne);
        ShopWindow->add(decOne);

        AmtSelling->addLine("0");
        playerName->addLine(use_arr[i]->getName());
        playerCost->addLine("0");
        playerAmt->addLine((std::to_string(pinven->getUseables()[i])));
        incdec.push_back(incOne);
        incdec.push_back(decOne);

      }
      if (0 >= sinven->getUseables()[i])
      {
      }
      else
      {
        incOne = Theme->load("Button");
        decOne = Theme->load("Button");
        incOne->setText("+");
        decOne->setText("-");
        incOne->setSize({ 10,10 });
        decOne->setSize({ 10,10 });
        incOne->connect("clicked", [this, _i = i]() { this->TotalBuyAmount(_i, 1); });
        decOne->connect("clicked", [this, _i = i]() { this->TotalBuyAmount(_i, -1); });
        //incOne->connect("clicked", &NewShopCreator::TotalBuyAmount, this, i, 1);
        //decOne->connect("clicked", &NewShopCreator::TotalBuyAmount, this, i, -1);
        incOne->setPosition({ 360,(35 + i * 21) });
        decOne->setPosition({ 370,(35 + i * 21) });
        ShopWindow->add(incOne);
        ShopWindow->add(decOne);
        AmtBuying->addLine("0");
        shopName->addLine(use_arr[i]->getName());
        shopCost->addLine("0");
        shopAmt->addLine((std::to_string(sinven->getUseables()[i])));
        incdec.push_back(incOne);
        incdec.push_back(decOne);
      }
    }

    buttonBuy->setText("Buy");
    buttonBuy->setSize({ 50, 20 });
    buttonBuy->setPosition({ 580, 370 });
    buttonBuy->connect("clicked", [this]() {this->Buy(); });

    buttonSell->setText("Sell");
    buttonSell->setSize({ 50, 20 });
    buttonSell->setPosition({ 640, 370 });
    buttonSell->connect("clicked", [this]() {this->Sell(); });

    AmtSelling->setSize({ 20,250 });
    AmtSelling->setPosition({ 40,30 });

    playerName->setSize({ 190, 250 });
    playerName->setPosition({ 90, 30 });

    playerAmt->setSize({ 20,250 });
    playerAmt->setPosition({ 70,30 });

    shopName->setSize({ 190, 250 });
    shopName->setPosition({ 440, 30 });

    shopAmt->setSize({ 20,250 });
    shopAmt->setPosition({ 420,30 });

    AmtBuying->setSize({ 20,250 });
    AmtBuying->setPosition({ 390,30 });

    playerCost->setSize({ 60,250 });
    playerCost->setPosition({ 280,30 });

    shopCost->setSize({ 60,250 });
    shopCost->setPosition({ 630,30 });

    ShopWindow->add(playerAmt);
    ShopWindow->add(playerName);
    ShopWindow->add(shopAmt);
    ShopWindow->add(shopName);
    ShopWindow->add(buttonBuy);
    ShopWindow->add(buttonSell);
    ShopWindow->add(AmtSelling);
    ShopWindow->add(AmtBuying);
    ShopWindow->add(playerCost);
    ShopWindow->add(shopCost);

  }

  //update the golds' displays
  void NewShopCreator::updateGold()
  {
    //clear all the current gold displys
    playerCost->removeAllLines();
    shopCost->removeAllLines();
    playerGold->removeAllLines();
    shopGold->removeAllLines();

    //display for shop's gold (for buying)
    int amtB = AmtBuying->getLineAmount();
    //display for player's gold (for selling)
    int amtS = AmtSelling->getLineAmount();

    std::vector<std::string> str_vec;
    int total;
    std::string totals;
    int amtIndex = 0;
    int amtIndex2 = 0;
    int itemCost;
    int totalGold;
    totalSellCost = 0;
    totalBuyCost = 0;

    //place the current player and shop's gold
    playerGold->addLine(std::to_string(pinven->getGold()));
    shopGold->addLine(std::to_string(sinven->getGold()));

    //map the total items to the original display
    for (int i = 0; i < totalUseables; i++)
    {
      //if the item exists in the player's inventory
      if (pinven->getUseables()[i] > 0)
      {
        totals = AmtSelling->getLine(amtIndex);
        total = std::stoi(totals);

        itemCost = total*use_arr[i]->getValue()*sellMultiplier;
        playerCost->addLine(std::to_string(itemCost));

        totalSellCost += itemCost;
        amtIndex++;
      }
      //if the item exists in the shop's inventory
      if (sinven->getUseables()[i] > 0)
      {
        totals = AmtBuying->getLine(amtIndex2);
        total = std::stoi(totals);

        itemCost = total*use_arr[i]->getValue()*buyMultiplier;
        shopCost->addLine(std::to_string(itemCost));

        totalBuyCost += itemCost;
        amtIndex2++;
      }
    }
    //total cost
    shopGold->addLine(std::to_string(totalSellCost));
    playerGold->addLine(std::to_string(totalBuyCost));
    //leftover gold if bought/sold
    shopGold->addLine(std::to_string(sinven->getGold() - totalSellCost));
    playerGold->addLine(std::to_string(pinven->getGold() - totalBuyCost));

  }

  //update the player and shop's displays to their current inventories
  void NewShopCreator::updateInventories()
  {
    //amount of unique items in the player's inventory
    int pamt = playerName->getLineAmount();
    //amount of unique items in the shop's inventory
    int samt = shopName->getLineAmount();
    //used for placement for the +/- buttons
    int buttonIndex = 0;
    int buttonIndex2 = 0;

    //clear all the current buttons
    for (int i = (pamt + samt) * 2 - 1; i >= 0; i--)
    {
      ShopWindow->remove(incdec[i]);
      incdec.pop_back();
    }

    //remove the current display
    AmtBuying->removeAllLines();
    AmtSelling->removeAllLines();
    playerName->removeAllLines();
    playerAmt->removeAllLines();
    shopName->removeAllLines();
    shopAmt->removeAllLines();
    playerCost->removeAllLines();
    shopCost->removeAllLines();
    playerGold->removeAllLines();
    shopGold->removeAllLines();

    //set player's golds to its defaults
    playerGold->addLine(std::to_string(pinven->getGold()));
    playerGold->addLine("0");
    playerGold->addLine(std::to_string(pinven->getGold()));
    shopGold->addLine(std::to_string(sinven->getGold()));
    shopGold->addLine("0");
    shopGold->addLine(std::to_string(sinven->getGold()));

    //map the items to the default inventory
    for (int i = 0; i < totalUseables; i++)
    {
      //player inventory
      if (0 >= pinven->getUseables()[i])
      {
        //only if there should be 0 displays for items
        //playerAmt->addLine("0");
      }
      else
      {
        //TO ADD: texture
        //place in the inc/dec buttons
        incOne = Theme->load("Button");
        decOne = Theme->load("Button");
        incOne->setText("+");
        decOne->setText("-");
        incOne->setSize({ 10,10 });
        decOne->setSize({ 10,10 });
        incOne->connect("clicked", [this, _i = i]() { this->TotalSellAmount(_i, 1); });
        decOne->connect("clicked", [this, _i = i]() { this->TotalSellAmount(_i, -1); });
        //incOne->connect("clicked", &NewShopCreator::TotalSellAmount, this, i, 1);
        //decOne->connect("clicked", &NewShopCreator::TotalSellAmount, this, i, -1);
        incOne->setPosition({ 10,(35 + buttonIndex * 21) });
        decOne->setPosition({ 20,(35 + buttonIndex * 21) });
        ShopWindow->add(incOne);
        ShopWindow->add(decOne);

        //set all the player's defaults to 0
        //set item name and amount of items it contains
        AmtSelling->addLine("0");
        playerGold->addLine("0");
        playerName->addLine(use_arr[i]->getName());
        playerAmt->addLine((std::to_string(pinven->getUseables()[i])));
        //place the buttons into a vector to clear them later
        incdec.push_back(incOne);
        incdec.push_back(decOne);
        buttonIndex++;
      }

      //shop inventory
      if (0 >= sinven->getUseables()[i])
      {
        //shopAmt->addLine("0");
      }
      else
      {
        //buttons
        incOne = Theme->load("Button");
        decOne = Theme->load("Button");
        incOne->setText("+");
        decOne->setText("-");
        incOne->setSize({ 10,10 });
        decOne->setSize({ 10,10 });

        incOne->connect("clicked", [this, _i = i]() { this->TotalBuyAmount(_i, 1); });
        decOne->connect("clicked", [this, _i = i]() { this->TotalBuyAmount(_i, -1); });
        //incOne->connect("clicked", &NewShopCreator::TotalBuyAmount, this, i, 1);
        //decOne->connect("clicked", &NewShopCreator::TotalBuyAmount, this, i, -1);
        incOne->setPosition({ 360,(35 + buttonIndex2 * 21) });
        decOne->setPosition({ 370,(35 + buttonIndex2 * 21) });
        ShopWindow->add(incOne);
        ShopWindow->add(decOne);

        //shop defaults
        AmtBuying->addLine("0");
        shopGold->addLine("0");
        shopName->addLine(use_arr[i]->getName());
        shopAmt->addLine((std::to_string(sinven->getUseables()[i])));
        //place the buttons into a vector to clear them later
        incdec.push_back(incOne);
        incdec.push_back(decOne);
        buttonIndex2++;
      }
    }

  }

  //update the shop's inventory
  //called when the player actually buys the items
  void NewShopCreator::Buy()
  {
    //amount of unique items the inventory has
    int buy_amt = AmtBuying->getLineAmount();
    if (buy_amt <= 0)
    {
      return;
    }

    //if the player does not have enough gold
    if (totalBuyCost > pinven->getGold())
    {
      //MessageAlert("Insufficient gold \n");
      return;
    }

    //how many of the item that is being bought
    int buy_total;
    std::string buys;
    //unique shop item index
    int amtIndex = 0;

    //map the inventory to the default inventory
    for (int i = 0; i < totalUseables; i++)
    {
      //if the item exists in the player's inventory
      if (pinven->getUseables()[i] > 0)
      {
        //string for the # to buy of the item
        buys = AmtBuying->getLine(amtIndex);
        //conversion to int
        buy_total = std::stoi(buys);
        //update the inventories by increasing the player's index item
        //and decreasing the shop's inventory
        pinven->updateUseables(i, buy_total);
        sinven->updateUseables(i, -buy_total);
        //go to next line (item) in the shop's inventory
        amtIndex++;
      }
    }
    //increase and decrease the shop's and player's gold respectively
    pinven->setGold(-totalBuyCost);
    sinven->setGold(totalBuyCost);
    //update the displays
    updateInventories();
    updateGold();
  }
  void NewShopCreator::Sell()
  {
    int sell_amt = AmtSelling->getLineAmount();
    if (sell_amt <= 0)
    {
      return;
    }
    if (totalSellCost > sinven->getGold())
    {
      //MessageAlert("Insufficient gold \n");
      return;
    }
    int sell_total;
    std::string sells;
    int amtIndex = 0;

    for (int i = 0; i < totalUseables; i++)
    {
      if (pinven->getUseables()[i] > 0)
      {
        sells = AmtSelling->getLine(amtIndex);
        sell_total = std::stoi(sells);
        pinven->updateUseables(i, -sell_total);
        sinven->updateUseables(i, sell_total);
        amtIndex++;
      }
    }
    pinven->setGold(totalSellCost);
    sinven->setGold(-totalSellCost);
    updateInventories();
    updateGold();
    //gold
  }
  //index = the index of the original default item array, not the user's array
  //delta = the amount to change in the to sell items display
  void NewShopCreator::TotalSellAmount(int index, int delta)
  {
    int amt = AmtSelling->getLineAmount();
    if (amt <= 0)
    {
      return;
    }
    std::vector<std::string> str_vec;
    int total;
    std::string totals;
    int amtIndex = 0;

    for (int i = 0; i < totalUseables; i++)
    {
      if (i == index)
      {
        totals = AmtSelling->getLine(amtIndex);
        total = std::stoi(totals);
        if (pinven->incrementUseables(i, -(total + delta)) && total + delta >= 0)
          total += delta;
        str_vec.push_back(std::to_string(total));
        amtIndex++;
      }
      else if (pinven->getUseables()[i] > 0)
      {
        totals = AmtSelling->getLine(amtIndex);
        str_vec.push_back(totals);
        amtIndex++;
      }
    }
    AmtSelling->removeAllLines();
    for (int i = 0; i < amt; i++)
    {
      AmtSelling->addLine(str_vec[i]);
    }
    updateGold();
  }

  //displays the total amount that the player plans on buying
  //used in the shop's display
  void NewShopCreator::TotalBuyAmount(int index, int delta)
  {
    //will be equal to the total amount of unique items the shop's inventory has
    int amt = AmtBuying->getLineAmount();
    if (amt <= 0)
    {
      return;
    }

    //the vector that will be put into the updated display
    std::vector<std::string> str_vec;
    //total amount of items to be bought and string conversion
    int total;
    std::string totals;
    //index for items already in the display
    int amtIndex = 0;

    //map the lines to update to the default inventory for display
    for (int i = 0; i < totalUseables; i++)
    {
      //increment the amount the player plans on buying within bounds
      if (i == index)
      {
        totals = AmtBuying->getLine(amtIndex);
        total = std::stoi(totals);
        if (sinven->incrementUseables(i, -(total + delta)) && total + delta >= 0)
          total += delta;
        str_vec.push_back(std::to_string(total));
        amtIndex++;
      }
      //else just take whatever is in the shop's inventory and keep it as is
      else if (pinven->getUseables()[i] > 0)
      {
        totals = AmtBuying->getLine(amtIndex);
        str_vec.push_back(totals);
        amtIndex++;
      }
    }
    //update the lines
    AmtBuying->removeAllLines();
    for (int i = 0; i < amt; i++)
    {
      AmtBuying->addLine(str_vec[i]);
    }
    //update the gold display
    updateGold();
  }
  void NewShopCreator::OpenTheme()
  {


    ShopWindow = Theme->load("ChildWindow");
    ShopWindow->setPosition({ 10,10 });
    ShopWindow->setSize({ 700, 400 });

    tgui::ChatBox::Ptr pi = Theme->load("ChatBox");
    tgui::ChatBox::Ptr si = Theme->load("ChatBox");
    tgui::ChatBox::Ptr pa = Theme->load("ChatBox");
    tgui::ChatBox::Ptr sa = Theme->load("ChatBox");
    tgui::ChatBox::Ptr as = Theme->load("ChatBox");
    tgui::ChatBox::Ptr ab = Theme->load("ChatBox");
    tgui::ChatBox::Ptr pg = Theme->load("ChatBox");
    tgui::ChatBox::Ptr sg = Theme->load("ChatBox");
    tgui::ChatBox::Ptr st = Theme->load("ChatBox");
    tgui::ChatBox::Ptr pt = Theme->load("ChatBox");

    pi->addLine("Player Inventory");
    si->addLine("Shop Inventory");
    pa->addLine("#");
    sa->addLine("#");
    as->addLine("Sell");
    ab->addLine("Buy");
    pg->addLine("Gold");
    sg->addLine("Gold");
    st->addLine("Current Gold");
    pt->addLine("Current Gold");
    st->addLine("Total Gold");
    pt->addLine("Total Gold");
    pt->addLine("Gold Left");
    st->addLine("Gold Left");
    st->setLinesStartFromTop();
    pt->setLinesStartFromTop();


    as->setSize({ 50,23 });
    as->setPosition({ 10,5 });
    pi->setSize({ 190, 25 });
    pi->setPosition({ 90, 5 });
    pa->setSize({ 20,25 });
    pa->setPosition({ 70,5 });
    ab->setSize({ 50,23 });
    ab->setPosition({ 360,5 });
    si->setSize({ 190, 25 });
    si->setPosition({ 440, 5 });
    sa->setSize({ 20,25 });
    sa->setPosition({ 420,5 });
    pg->setSize({ 60, 25 });
    pg->setPosition({ 280,5 });
    sg->setSize({ 60,25 });
    sg->setPosition({ 630,5 });
    pt->setSize({ 210,70 });
    pt->setPosition({ 70,280 });
    st->setSize({ 210,70 });
    st->setPosition({ 420,280 });

    ShopWindow->add(pi);
    ShopWindow->add(si);
    ShopWindow->add(as);
    ShopWindow->add(ab);
    ShopWindow->add(sa);
    ShopWindow->add(pg);
    ShopWindow->add(sg);
    ShopWindow->add(pa);
    ShopWindow->add(st);
    ShopWindow->add(pt);

    //initializations
    buttonBuy = Theme->load("Button");
    buttonSell = Theme->load("Button");
    AmtBuying = Theme->load("ChatBox");
    AmtSelling = Theme->load("ChatBox");
    playerName = Theme->load("ChatBox");
    playerAmt = Theme->load("ChatBox");
    shopName = Theme->load("ChatBox");
    shopAmt = Theme->load("ChatBox");
    playerGold = Theme->load("ChatBox");
    shopGold = Theme->load("ChatBox");
    playerCost = Theme->load("ChatBox");
    shopCost = Theme->load("ChatBox");

    playerName->setLinesStartFromTop();
    playerAmt->setLinesStartFromTop();
    shopName->setLinesStartFromTop();
    shopAmt->setLinesStartFromTop();
    AmtBuying->setLinesStartFromTop();
    AmtSelling->setLinesStartFromTop();
    playerCost->setLinesStartFromTop();
    shopCost->setLinesStartFromTop();
    playerGold->setLinesStartFromTop();
    shopGold->setLinesStartFromTop();
    
    GUI->add(ShopWindow);
    GUI->focusWidget(ShopWindow);
    ShopWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
    // PlayerWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
    //MessageAlert("Insufficient gold \n");
  }

  void NewShopCreator::Close()
  {
    ShopWindow->remove(ShopWindow);
    ShopWindow->destroy();
  }
//}

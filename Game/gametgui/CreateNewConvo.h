#ifndef CREATE_CONVO_H
#define CREATE_CONVO_H

#include <TGUI\TGUI.hpp>
#include "../Conversation.h"
#include "../ListReader.h"
#include "Engine/Engine.h"
#include "Globals/GlobalHooks.h"

//Call using CreateConvo
//example call:
//std::shared_ptr<NewConvoCreator> convoPtr;
//convoPtr = std::make_shared<NewConvoCreator>();
//convoPtr->CreateConvo("hey.txt");
//convoPtr->setSize(x,y);
//convoPtr->setPosition(x,y);
  class NewConvoCreator
  {
  public:
    NewConvoCreator() = default;
    ~NewConvoCreator() = default;

    //Call this function to create a new conversation during collisions, pass in the filename
    void CreateConvo(std::string filename);// , MainCharacter mc);
   // void OpenTheme(tgui::Theme::Ptr Theme);
    void Close();
   // void setVariables(int numChoices, std::string contentText, std::string buttonText);
    void setSize(int x, int y);
    void setPosition(int x, int y);



   // void NewWindow();
    void LoadConvo(int cur);
   // void NewConvo();
   // void addChoice();
    void LoadNewChoices(int cur, int j);
  protected:
    tgui::Theme::Ptr Theme;
    tgui::ChildWindow::Ptr CreationWindow;

    tgui::EditBox::Ptr EditChoice;
    tgui::EditBox::Ptr EditChoiceID;
    tgui::EditBox::Ptr EditContent;
    tgui::EditBox::Ptr EditID;
    tgui::EditBox::Ptr EditCharacter;
    tgui::Button::Ptr EditSave;
    tgui::Button::Ptr EditAddChoice;
    tgui::Button::Ptr EditLoad;

    tgui::Button::Ptr CreateConversations;
    tgui::Button::Ptr LoadGameConvo;
    tgui::ChatBox::Ptr CharSpeaking;
    tgui::TextBox::Ptr ContentText;
    tgui::Button::Ptr ChoiceButton;
    std::string nodeID;

    std::vector<tgui::Button::Ptr> choices_vec;

    int textSize;
    int buttonPos;
    int m_numChoices;
    std::string m_contentText;
    std::string m_buttonText;
    std::string m_id;
    //std::vector<std::shared_ptr<Conversation>> convo_arr;
    int totalNodes = 0;
    Conversation** convo_arr;

    std::vector<std::shared_ptr<std::string>> nodeIDs;

    std::shared_ptr<tgui::Gui> GUI;
    MainCharacter my_mc;
    std::string my_filename;

    float x_dim;
    float y_dim;

    float x_pos;
    float y_pos;
    

  };


#endif

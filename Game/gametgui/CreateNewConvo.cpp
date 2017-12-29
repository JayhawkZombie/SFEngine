#include "CreateNewConvo.h"
#include <filesystem>

//namespace Engine {

void NewConvoCreator::CreateConvo(std::string filename)//, MainCharacter mc)
  {
    std::unique_ptr<ListReader> reader = std::make_unique<ListReader>();
    Theme = std::make_shared<tgui::Theme>("././SFEngine/Source/CoreFiles/UIThemes/Black.txt");
    //This will cause a compiler failure, please use a cloning method
    //my_filename = "Game/ContentFiles/Conversation/ConvoJohnWakeUp.txt";
    my_filename = filename;
    GUI = GUI;
    MainCharacter mc;
    convo_arr = reader->readConversation(my_filename, mc);
    totalNodes = reader->getNumConversations();
    x_dim = 700;
    y_dim = 400;
    y_pos = 400;
    x_pos = 10;

    LoadConvo(0);

  }
void NewConvoCreator::setSize(int x, int y) {
  x_dim = x;
  y_dim = y;
  }
void NewConvoCreator::setPosition(int x, int y) {
  x_pos = x;
  y_pos = y;
}
  void NewConvoCreator::LoadNewChoices(int cur, int j)
  {
    if (convo_arr[cur]->getNumChoices() == 0)
    {
      Close();
    }

    for (int i = 0; i < totalNodes; i++)
    {
      if (convo_arr[i]->getConvoID() == convo_arr[cur]->getConvoNodes(j))
      {
        Close();
        LoadConvo(i);
        return;
      }
    }

  }
  /*
  void NewConvoCreator::setVariables(int numChoices, std::string contentText, std::string buttonText)
  {
    m_numChoices = numChoices;
    m_contentText = contentText;
    m_buttonText = buttonText;
  }
  
  void NewConvoCreator::NewWindow()
  {
    CreationWindow->remove(CreationWindow);
    CreationWindow->destroy();
    OpenTheme(Theme);
  }
  */
  void NewConvoCreator::LoadConvo(int cur)
  {
    buttonPos = 0;
    textSize = 0;
    
    if (convo_arr == NULL)
    {
      return;
    }
    CreationWindow = Theme->load("ChildWindow");
   // float xDiff = WindowSize.x - 700.f;
   // float yDiff = WindowSize.y - 400.f;

    CreationWindow->setPosition({ x_pos,y_pos });
    CreationWindow->setSize({ x_dim,y_dim });

   // CreationWindow->setPosition({ x_pos,y_pos });
    //CreationWindow->setSize({ v1.x,v1.y });
    float y_size = y_dim/(convo_arr[cur]->getNumChoices() + 4);
    //CreationWindow->setPosition({ xDiff / 2.f, yDiff / 4.f });
    //CreationWindow->setSize({ 700, 400 });

    CharSpeaking = Theme->load("ChatBox");
    CharSpeaking->addLine(convo_arr[cur]->getUserID());
    CharSpeaking->setSize({ x_dim,y_size });
    CharSpeaking->setPosition({ 0,0 });

 //   CharSpeaking->setSize({ 680, 30 });
   // CharSpeaking->setPosition({ 10, 10 });

    textSize = 110;
    ContentText = Theme->load("TextBox");
    ContentText->addText(convo_arr[cur]->getContent());
    ContentText->setSize({ x_dim, y_size*3 });
    ContentText->setPosition({ 0, y_size });

    buttonPos = y_size*4;

    for (int j = 0; j < convo_arr[cur]->getNumChoices(); j++)
    {
      ChoiceButton = Theme->load("Button");
      ChoiceButton->setText(convo_arr[cur]->getConvoNodesContent(j));
      ChoiceButton->setSize({ x_dim, y_size });
      ChoiceButton->setPosition({ 0, buttonPos });

      nodeID = (convo_arr[cur]->getConvoNodes(j));
      ChoiceButton->connect("clicked", [this, _j = j, _cur = cur ]() { this->LoadNewChoices(_cur, _j); });
      //ChoiceButton->connect("clicked", &NewConvoCreator::LoadNewChoices, this, cur, j);
      buttonPos += y_size;
      CreationWindow->add(ChoiceButton);
    }

    CreationWindow->add(CharSpeaking);
    CreationWindow->add(ContentText);
    
    GUI->add(CreationWindow);
    GUI->focusWidget(CreationWindow);
    CreationWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));

  }
  /*
  void NewConvoCreator::NewConvo()
  {
    buttonPos = 200;
    textSize = 0;
    Close();
    float xDiff = WindowSize.x - 700.f;
    float yDiff = WindowSize.y - 400.f;
    CreationWindow = Theme->load("ChildWindow");
    CreationWindow->setPosition({ xDiff / 2.f, yDiff / 4.f });
    CreationWindow->setSize({ 700, 400 });


    EditCharacter = Theme->load("EditBox");
    EditCharacter->setDefaultText("Character speaking");
    EditCharacter->setTextSize(10);
    EditCharacter->setSize({ 400, 25 });
    EditCharacter->setPosition({ 10, 10 });

    EditID = Theme->load("EditBox");
    EditID->setDefaultText("# ID");
    EditID->setTextSize(10);
    EditID->setSize({ 150, 25 });
    EditID->setPosition({ 500, 10 });

    EditContent = Theme->load("EditBox");
    EditContent->setDefaultText("Add conversation content here...");
    EditContent->setTextSize(15);
    EditContent->setSize({ 680, 150 });
    EditContent->setPosition({ 10, 40 });

    EditAddChoice = Theme->load("Button");
    EditAddChoice->setText("Add Choice");
    EditAddChoice->setSize({ 100, 20 });
    EditAddChoice->setPosition({ 550, 360 });
    EditAddChoice->connect("clicked", [this]() {this->addChoice(); });

    EditSave = Theme->load("Button");
    EditSave->setText("Save");
    EditSave->setSize({ 100, 20 });
    EditSave->setPosition({ 10, 360 });
    EditSave->connect("clicked", [this]() {this->addChoice(); });

    EditLoad = Theme->load("Button");
    EditLoad->setText("Load");
    EditLoad->setSize({ 100, 20 });
    EditLoad->setPosition({ 550, 360 });
    EditLoad->connect("clicked", [this]() {this->addChoice(); });

    CreationWindow->add(EditAddChoice);
    CreationWindow->add(EditSave);
    CreationWindow->add(EditID);
    CreationWindow->add(EditContent);
    CreationWindow->add(EditCharacter);

    GUI->add(CreationWindow);
    GUI->focusWidget(CreationWindow);
    CreationWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }
  void NewConvoCreator::addChoice()
  {
    if (buttonPos < 360)
    {
      
      EditChoiceID = Theme->load("EditBox");
      EditChoiceID->setDefaultText("Go to ID #");
      EditChoiceID->setTextSize(10);
      EditChoiceID->setSize({ 70, 30 });
      EditChoiceID->setPosition(10, buttonPos);

      EditChoice = Theme->load("EditBox");
      EditChoice->setDefaultText("Add dialogue for choice...");
      EditChoice->setSize({ 600, 30 });
      EditChoice->setPosition(75, buttonPos);
      buttonPos += 40;

      CreationWindow->add(EditChoice);
      CreationWindow->add(EditChoiceID);
    }

  }
  
  void NewConvoCreator::OpenTheme(tgui::Theme::Ptr ThemePtr)
  {
    Theme = ThemePtr;

    float xDiff = WindowSize.x - 700.f;
    float yDiff = WindowSize.y - 400.f;
    //create the window
    CreationWindow = Theme->load("ChildWindow");
    CreationWindow->setPosition({ xDiff / 2.f, yDiff / 4.f });
    CreationWindow->setSize({ 700, 400 });

    CreateConversations = Theme->load("Button");
    CreateConversations->setText("Create a new conversation graph");
    CreateConversations->setSize({ 320, 380 });
    CreateConversations->setPosition({ 10, 10 });
    CreateConversations->connect("clicked", [this]() {this->NewConvo(); });

    LoadGameConvo = Theme->load("Button");
    LoadGameConvo->setText("Load in the game");
    LoadGameConvo->setSize({ 320, 380 });
    LoadGameConvo->setPosition({ 350, 10 });
    LoadGameConvo->connect("clicked", [this]() {this->LoadConvo(0); });


    CreationWindow->add(CreateConversations);
    CreationWindow->add(LoadGameConvo);

    GUI->add(CreationWindow);
    GUI->focusWidget(CreationWindow);
    CreationWindow->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }
  */
  void NewConvoCreator::Close()
  {
    CreationWindow->remove(CreationWindow);
    CreationWindow->destroy();
  }
//}

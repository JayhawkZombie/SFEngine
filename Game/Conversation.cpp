#include "Conversation.h"
Conversation::Conversation()
{
	m_character = NULL;
	m_currentConvoNodes = 0;
	for (int i = 0; i < 255; i++)
	{
		m_convoNodes[i] = "";
		m_convoNodesContent[i] = "";
	}
	//std::shared_ptr<int> m_convoNodes;
	m_userID = "";
	m_convoID = "";
	m_content = "";
	m_choiceID = "";
	m_numNodes = 0;
	m_numChoices = 0;
	m_exitStatus = 0;
}
Conversation::~Conversation()
{}
//getters
const std::string Conversation::getUserID()
{
	return m_userID;
}
const std::string Conversation::getConvoID()
{
	return m_convoID;
}
const std::string Conversation::getConvoNodes(int choice)
{
	return m_convoNodes[choice];
}
const std::string Conversation::getConvoNodesContent(int choice)
{
	return m_convoNodesContent[choice];
}
const int Conversation::getNumChoices()
{
	return m_numChoices;
}
const std::string Conversation::getContent()
{
	return m_content;
}
//const int Conversation::getAffinity()

const std::string Conversation::getChoiceID()
{
	return m_choiceID;
}

//setters
void Conversation::setUserID(std::string &userID)
{
	m_userID = userID;
}
void Conversation::setConvoID(std::string &convoID)
{
	m_convoID = convoID;
} //ID of main conversation node
void Conversation::setContent(std::string &content)
{
	m_content = content;
}
void Conversation::setChoiceID(std::string &choiceID)
{
	m_choiceID = choiceID;
} //ID of choices in conversation
void Conversation::setConvoNodes(std::string &convoNode)
{
	m_convoNodes[m_currentConvoNodes] = convoNode;
	m_currentConvoNodes++;
}
void Conversation::setConvoNodesContent(std::string &convoNode)
{
	m_convoNodesContent[m_currentConvoNodes] = convoNode;
}
void Conversation::setNumChoices(int &numChoices)
{
	m_numChoices = numChoices;
}
void Conversation::setCharacter(MainCharacter* character)
{
	m_character = character;
}
void Conversation::setAffinity(int &affinity, int &increment)
{
}
const int Conversation::getExitStatus()
{
	return m_exitStatus;
}
void Conversation::setExitStatus(int &exitStatus)
{
	m_exitStatus = exitStatus;
}
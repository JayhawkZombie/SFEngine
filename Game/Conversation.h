#ifndef CONVERSATION_H
#define CONVERSATION_H
//#include "Companion.h"
#include "MainCharacter.h"
#include <string>
#include <memory>

/*
Conversation trees
Reads in one conversation tree
They're all technically seperate nodes, but they can be easily compared against each other
Nodes are not directly connected
*/
class Conversation
{
public:
	Conversation();
	~Conversation();
	//getters
	const std::string getUserID();
	const std::string getConvoID();
	const std::string getConvoNodes(int choice);
	const std::string getConvoNodesContent(int choice);
	const int getNumChoices();
	const std::string getContent();
	//const int getAffinity(); //int?
	const std::string getChoiceID();
	const int getExitStatus();

	//setters
	void setUserID(std::string &userID);
	void setConvoID(std::string &convoID); //ID of main conversation node
	void setContent(std::string &content);
	void setChoiceID(std::string &choiceID); //ID of choices in conversation
	void setConvoNodes(std::string &convoNode); //possibly to place them into an array
	void setConvoNodesContent(std::string &convoNode);
	void setNumChoices(int &numChoices);
	void setCharacter(MainCharacter* character);
	void setAffinity(int &affinity, int &increment);
	void setExitStatus(int &exitStatus);
	//affinity, value, check if affinity is greater than the value
	//255 max convo nodes in a conversation
private:
	//main character for the conversation tree
	MainCharacter* m_character;

	//current number of conversation nodes that are read in
	//needed because the conversation nodes are passed into an array
	int m_currentConvoNodes;

	//conversation nodes, aka conversation node IDs of the reponses
	//ie. "sleepingResponse"
	std::string m_convoNodes[255];

	//conversation node content of the possible responses
	//ie. "Tell him I'll be right there"
	std::string m_convoNodesContent[255];

	/***
	Testing, ignore
	std::shared_ptr<int> m_convoNodes;
	***/

	//userID, aka the person you are having the conversation with
	//ie. "John"
	std::string m_userID;

	//ID of the current conversation node
	//can possibly be the same as another conversation node's m_convoNodes[x]
	//ie. "intro" or "MorningBirdResponse"
	std::string m_convoID;

	//content of the conversation node, can possibly be the same as m_convoNodesContent[x]
	//ie. "Wake up sleepy head, Dad's got stuff for you to do"
	std::string m_content;

	//I don't think i used this one
	std::string m_choiceID;

	//total number of nodes in the entire conversation
	//i also don't think i used this one
	int m_numNodes;

	//total number of choices from the current node
	//ie. first node, intro, has 4 responses
	int m_numChoices;

	//exit status
	int m_exitStatus;
};

#endif
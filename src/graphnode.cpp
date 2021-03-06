#include "graphnode.h"
#include "graphedge.h"

GraphNode::GraphNode(int id) : _id(id) { _chatBot = nullptr; }

GraphNode::~GraphNode() {}

void GraphNode::AddToken(std::string token) { _answers.push_back(token); }

void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
  _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge) {
  _childEdges.emplace_back(std::move(edge));
}

void GraphNode::MoveChatbotHere(ChatBot chatbot) {
  _chatBot = std::make_unique<ChatBot>();
  // move assignment operator is called here
  *_chatBot = std::move(chatbot);
  _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode) {
  newNode->MoveChatbotHere(std::move(*_chatBot));
  _chatBot = nullptr;
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {
  return _childEdges[index].get();
}
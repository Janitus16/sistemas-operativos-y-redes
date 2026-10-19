#pragma once
#include "Vector2.h"
#include "INodeContent.h"
#include <mutex>

class Node
{
public:
	Node(Vector2 position);

	INodeContent* GetContent();

	//TODO: LUEGO

	//TODO: NO LUEGO

	void SetContent(INodeContent* newContent);
	void DrawContent(Vector2 offset);

	void Lock();
	void UnLock();

private:
	Vector2 _position;
	INodeContent* _content;
	std::mutex _classMutex;
};


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
	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent, T>::value>::type>
	T* GetContent() {
		if (_content == nullptr)
			return nullptr;
		T* contentCasted = dynamic_cast<T*>(_content);
		return contentCasted;
	}

	//TODO: NO LUEGO
	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent, T>::value>::type>
	bool GetContent(T* outContent) {
		if (_content == nullptr)
			return false;

		outContent = dynamic_cast<T*>(_content);
		return outContent;
	}

	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent, T>::value>::type>
	bool HaveContent() {
		if (_content == nullptr)
			return false;

		T* contentCasted = dynamic_cast<T*>(_content);
		return contentCasted != nullptr;
	}


	void SetContent(INodeContent* newContent);
	void DrawContent(Vector2 offset);

	void Lock();
	void UnLock();

private:
	Vector2 _position;
	INodeContent* _content;
	std::mutex _classMutex;
};


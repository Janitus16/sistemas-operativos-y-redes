#pragma once

#include "Node.h"

#include <vector>
#include <list>
#include <functional>
#include <mutex>

class NodeMap
{
public:
	typedef std::vector<Node*> NodeColumn;
	typedef std::vector<NodeColumn*> NodeGrid;

	typedef std::function<void(Node* node)> SafePick;
	typedef std::function<void(std::list<Node*> nodes)> SafeMultiPick;

public:

	NodeMap(Vector2 size, Vector2 offset);

	Vector2 GetSize();
	// Set Size --> No usamos, no implementamos


	void UnSafeDraw();
	void SafePickNode(Vector2 position, SafePick safePickAction);
	void SafeMultiPickNode(std::list<Vector2> positions, SafeMultiPick safeMultiPickAction);

private:

	Vector2 _offset;

	Vector2 _size;
	std::mutex _sizeMutex;

	NodeGrid _grid;
	std::mutex _gridMutex;

	std::mutex _safeMultiNodeLockMutex;

	Node* UnSafeGetNode(Vector2 position);

};


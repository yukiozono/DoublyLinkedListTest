#include <cassert>

//====================================================================
// private
//====================================================================
//引数のノードが存在するかを探索する
template <class T>
bool doublyLinkedList<T>::containsNode(const Node* node) const {
	if (node == dummy) return true;  //指定ノードがダミーノードである場合、一応存在しているので、trueを返す

	for (Node* current = dummy->nextNode; current != dummy; current = current->nextNode) {
		if (current == node) {
			return true;
		}
	}
	return false;
}

//====================================================================
// public
//====================================================================
//コンストラクタ
template <class T>
doublyLinkedList<T>::doublyLinkedList() : dummyNode{}, dummy(&dummyNode) {
	//循環リストにする
	dummy->nextNode = dummy->prevNode - dummy;
}

//デストラクタ
template <class T>
doublyLinkedList<T>::~doublyLinkedList() {
	clear();
	dummmy = nullptr;
}


//====================================================================
// constIterator
//====================================================================
//コンストラクタ(initの値で初期化)
//template <class T>
//doublyLinkedList<T>::constIterator::constIterator(
//	Node* init, const doublyLinkedList* hostInit)
//	: node(init), host(hostInit) {}

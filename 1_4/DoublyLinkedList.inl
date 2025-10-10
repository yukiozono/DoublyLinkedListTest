#include <cassert>

//====================================================================
// private
//====================================================================
//引数のノードが存在するかを探索する
template <class T>
bool doublyLinkedList<T>::containsNode(const Node* node) const {
	if (node == &dummy) return true;  //指定ノードがダミーノードである場合、一応存在しているので、trueを返す

	for (Node* current = dummy.nextNode; current != &dummy; current = current->nextNode) {
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
doublyLinkedList<T>::doublyLinkedList() : dummy{} {
	//循環リストにする
	dummy.nextNode = dummy.prevNode = &dummy;
}

//デストラクタ
template <class T>
doublyLinkedList<T>::~doublyLinkedList() {
	clear();
}


//====================================================================
// constIterator
//====================================================================
//コンストラクタ(initの値で初期化)
template <class T>
doublyLinkedList<T>::constIterator::constIterator(
	Node* init, const doublyLinkedList* hostInit)
	: node(init), host(hostInit) {}

//デフォルトコンストラクタ
template <class T>
doublyLinkedList<T>::constIterator::constIterator() = default;

//前置デクリメント用(--it)
template <class T>
typename doublyLinkedList<T>::constIterator& doublyLinkedList<T>::constIterator::operator--() {
	//もしend()などから末尾(ダミーノード)を指定してデクリメントした場合、
	if (this->node == &this->host->dummy) {
		//もしダミーのprevNodeが自身を指していた場合、リストは空なので、assert発生
		assert(this->node->prevNode != this->node);
	}
	//実際に中身があるノードだった場合
	else {
		//prevNodeがダミーだった場合、先頭を通り越しているので、assert発生
		assert(this->node->prevNode != &this->host->dummy);
	}
	this->node = this->node->prevNode;
	return *this;
}

//後置デクリメント用(it--)
template <class T>
typename doublyLinkedList<T>::constIterator doublyLinkedList<T>::constIterator::operator--(int) {
	constIterator it = *this; 
	--(*this); 
	return it;
}

//前置インクリメント用(++it)
template <class T>
typename doublyLinkedList<T>::constIterator& doublyLinkedList<T>::constIterator::operator++() {
	//nullptrではない場合と、ダミーノードではない場合のみ通す
	assert(this->node != nullptr && this->node != &this->host->dummy);
	this->node = this->node->nextNode;
	return *this;
}

//後置インクリメント用(it++)
template <class T>
typename doublyLinkedList<T>::constIterator doublyLinkedList<T>::constIterator::operator++(int) {
	constIterator it = *this;
	++(*this);
	return it;
}

//間接参照
template <class T>
const T&
doublyLinkedList<T>::constIterator::operator*() const {
	//nullptrではない場合と、ダミーノードではない場合のみ通す
	assert(this->node != nullptr && this->node != &this->host->dummy);
	return this->node->data;
}

//代入
template <class T>
typename doublyLinkedList<T>::constIterator& doublyLinkedList<T>::constIterator::operator=(const constIterator& source) = default;

//等値比較
template <class T>
bool doublyLinkedList<T>::constIterator::operator==(const constIterator& comp) const {
	return this->host == comp.host && this->node == comp.node;
}

//非等値比較
template <class T>
bool doublyLinkedList<T>::constIterator::operator!=(const constIterator& comp)const {
	return !(*this == comp);
}

//====================================================================
// iterator
//====================================================================
//コンストラクタ(initの値で初期化)
template <class T>
doublyLinkedList<T>::iterator::iterator(
	Node* init, const doublyLinkedList* hostInit)
	:constIterator(init, hostInit) {}

//デフォルトコンストラクタ
template<class T>
doublyLinkedList<T>::iterator::iterator() = default;

//前置デクリメント用(--it)
template <class T>
typename doublyLinkedList<T>::iterator& doublyLinkedList<T>::iterator::operator--() {
	//もしend()などから末尾(ダミーノード)を指定してデクリメントした場合、
	if (this->node == &this->host->dummy) {
		//もしダミーのprevNodeが自身を指していた場合、リストは空なので、assert発生
		assert(this->node->prevNode != this->node);
	}
	//実際に中身があるノードだった場合
	else {
		//prevNodeがダミーだった場合、先頭を通り越しているので、assert発生
		assert(this->node->prevNode != &this->host->dummy);
	}
	this->node = this->node->prevNode;
	return *this;
}

//後置デクリメント用(it--)
template <class T>
typename doublyLinkedList<T>::iterator doublyLinkedList<T>::iterator::operator--(int) {
	iterator it = *this;
	--(*this); 
	return it;
}

///前置インクリメント用(++it)
template <class T>
typename doublyLinkedList<T>::iterator& doublyLinkedList<T>::iterator::operator++() {
	//nullptrではない場合と、ダミーノードではない場合のみ通す
	assert(this->node != nullptr && this->node != &this->host->dummy);
	this->node = this->node->nextNode;
	return *this;
}

///後置インクリメント用(it++)
template <class T>
typename doublyLinkedList<T>::iterator doublyLinkedList<T>::iterator::operator++(int) {
	iterator it = *this;
	++(*this);
	return it;
}

//間接参照
template <class T>
T& doublyLinkedList<T>::iterator::operator*() {
	//nullptrではない場合と、ダミーノードではない場合のみ通す
	assert(this->node != nullptr && this->node != &this->host->dummy);
	return this->node->data;
}

//等値比較
template <class T>
bool doublyLinkedList<T>::iterator::operator==(const iterator& comp)const {
	return this->host == comp.host && this->node == comp.node;
}

//非等値比較
template <class T>
bool doublyLinkedList<T>::iterator::operator!=(const iterator& comp)const {
	return !(*this == comp);
}


//====================================================================
// リスト内要素操作関数
//====================================================================
//データ数の取得]
template <class T>
size_t doublyLinkedList<T>::size() const {
	return listSize;
}

//先頭イテレータの取得
template <class T>
typename doublyLinkedList<T>::iterator doublyLinkedList<T>::begin() {
	return iterator(dummy.nextNode, this);
}

//先頭コンストイテレータの取得
template <class T>
typename doublyLinkedList<T>::constIterator doublyLinkedList<T>::cbegin() const {
	return constIterator(dummy.nextNode, this);
}

//末尾イテレータの取得
template <class T>
typename doublyLinkedList<T>::iterator doublyLinkedList<T>::end() {
	return iterator(&dummy, this);
}

//末尾コンストイテレータの取得
template <class T>
typename doublyLinkedList<T>::constIterator doublyLinkedList<T>::cend() const {
	constIterator it = {};
	it.node = const_cast<Node*>(&dummy);
	it.host = this;
	return it;
}

//リスト内の要素先頭から全消去
template <class T>
void doublyLinkedList<T>::clear() {
	Node* current = dummy.nextNode;
	//currentがdummyになるまでループし、deleteNodeでノードを削除
	while (current != &dummy) {
		Node* next = current->nextNode;
		deleteData(iterator(current, this));
		current = next;
	}
}

//位置nodePosの直前に挿入(iterator)
template <class T>
bool doublyLinkedList<T>::insertData(const iterator& nodePos, const T& data) {
	//nodePosに対してstatic_castを行い、constIteratorのinsertDataを使用
	return insertData(static_cast<const constIterator&>(nodePos), data);
}

//位置nodePosの直前に挿入(constIterator)
template <class T>
bool doublyLinkedList<T>::insertData(const constIterator& nodePos, const T& datas) {
	//イテレータの所有者が自分でない場合、falseを返す
	if (nodePos.host != this) {
		return false;
	}

	if (nodePos.node != nullptr && !containsNode(nodePos.node)) {
		return false;
	}

	//ノードを追加
	Node* next = {};

	//nodePosが空でない場合
	if (nodePos.node != nullptr) {
		//挿入先を代入
		next = nodePos.node;
	}
	//それ以外の場合はダミーを代入
	else {
		next = &dummy;
	}

	//新規ノードを生成し、接続を再編成
	Node* current = new Node();
	current->prevNode = next->prevNode;
	current->nextNode = next;
	next->prevNode->nextNode = current;
	next->prevNode = current;

	//データを代入し、ダミーではないと判別する
	current->data = datas;

	//リストサイズを管理する変数を+1
	++listSize;

	return true;
}

//位置nodePosにある要素を削除(iterator)
template <class T>
bool doublyLinkedList<T>::deleteData(const iterator& nodePos) {
	//nodePosに対してstatic_castを行い、constIteratorのdeleteDataを使用
	return deleteData(static_cast<const constIterator&> (nodePos));
}

//位置nodePosにある要素を削除(constIterator)
template <class T>
bool doublyLinkedList<T>::deleteData(const constIterator& nodePos) {
	if (listSize == 0)               return false;
	if (nodePos.host != this)        return false;
	if (nodePos.node == nullptr)     return false;
	if (nodePos.node == &dummy)       return false;
	if (!containsNode(nodePos.node)) return false;

	Node* current = nodePos.node;

	//ノードの前後のポインタを再編成
	current->nextNode->prevNode = current->prevNode;
	current->prevNode->nextNode = current->nextNode;

	//currentを削除し、リストサイズも減らす
	delete current;
	--listSize;

	return true;
}

//クイックソート
template <class T>
void doublyLinkedList<T>::sortList(const int sortKey,  const bool isAscend) {
	//もしリストサイズが1もしくはそれ以下だった場合、中断
	//if (this->size() <= 1) return;

	//分割判断基準を先頭に指定
	//Node* element = dummy->nextNode;

	//Node* indexI = element->nextNode;
	//Node* indexJ = dummy->prevNode;

	//初回のソートを行う
	//for (Node* current = element->nextNode; current != &dummy; current = current->nextNode) {
		
		//if (current > element) {

		//}
	//}
}

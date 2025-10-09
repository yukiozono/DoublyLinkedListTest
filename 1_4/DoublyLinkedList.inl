#include <cassert>

//====================================================================
// private
//====================================================================
//�����̃m�[�h�����݂��邩��T������
template <class T>
bool doublyLinkedList<T>::containsNode(const Node* node) const {
	if (node == &dummy) return true;  //�w��m�[�h���_�~�[�m�[�h�ł���ꍇ�A�ꉞ���݂��Ă���̂ŁAtrue��Ԃ�

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
//�R���X�g���N�^
template <class T>
doublyLinkedList<T>::doublyLinkedList() : dummy{} {
	//�z���X�g�ɂ���
	dummy.nextNode = dummy.prevNode = &dummy;
}

//�f�X�g���N�^
template <class T>
doublyLinkedList<T>::~doublyLinkedList() {
	clear();
}


//====================================================================
// constIterator
//====================================================================
//�R���X�g���N�^(init�̒l�ŏ�����)
template <class T>
doublyLinkedList<T>::constIterator::constIterator(
	Node* init, const doublyLinkedList* hostInit)
	: node(init), host(hostInit) {}

//�f�t�H���g�R���X�g���N�^
template <class T>
doublyLinkedList<T>::constIterator::constIterator() = default;

//�O�u�f�N�������g�p(--it)
template <class T>
typename doublyLinkedList<T>::constIterator& doublyLinkedList<T>::constIterator::operator--() {
	//����end()�Ȃǂ��疖��(�_�~�[�m�[�h)���w�肵�ăf�N�������g�����ꍇ�A
	if (this->node == &this->host->dummy) {
		//�����_�~�[��prevNode�����g���w���Ă����ꍇ�A���X�g�͋�Ȃ̂ŁAassert����
		assert(this->node->prevNode != this->node);
	}
	//���ۂɒ��g������m�[�h�������ꍇ
	else {
		//prevNode���_�~�[�������ꍇ�A�擪��ʂ�z���Ă���̂ŁAassert����
		assert(this->node->prevNode != &this->host->dummy);
	}
	this->node = this->node->prevNode;
	return *this;
}

//��u�f�N�������g�p(it--)
template <class T>
typename doublyLinkedList<T>::constIterator doublyLinkedList<T>::constIterator::operator--(int) {
	constIterator it = *this; 
	--(*this); 
	return it;
}

//�O�u�C���N�������g�p(++it)
template <class T>
typename doublyLinkedList<T>::constIterator& doublyLinkedList<T>::constIterator::operator++() {
	//nullptr�ł͂Ȃ��ꍇ�ƁA�_�~�[�m�[�h�ł͂Ȃ��ꍇ�̂ݒʂ�
	assert(this->node != nullptr && this->node != &this->host->dummy);
	this->node = this->node->nextNode;
	return *this;
}

//��u�C���N�������g�p(it++)
template <class T>
typename doublyLinkedList<T>::constIterator doublyLinkedList<T>::constIterator::operator++(int) {
	constIterator it = *this;
	++(*this);
	return it;
}

//�ԐڎQ��
template <class T>
const T&
doublyLinkedList<T>::constIterator::operator*() const {
	//nullptr�ł͂Ȃ��ꍇ�ƁA�_�~�[�m�[�h�ł͂Ȃ��ꍇ�̂ݒʂ�
	assert(this->node != nullptr && this->node != &this->host->dummy);
	return this->node->data;
}

//���
template <class T>
typename doublyLinkedList<T>::constIterator& doublyLinkedList<T>::constIterator::operator=(const constIterator& source) = default;

//���l��r
template <class T>
bool doublyLinkedList<T>::constIterator::operator==(const constIterator& comp) const {
	return this->host == comp.host && this->node == comp.node;
}

//�񓙒l��r
template <class T>
bool doublyLinkedList<T>::constIterator::operator!=(const constIterator& comp)const {
	return !(*this == comp);
}

//====================================================================
// iterator
//====================================================================
//�R���X�g���N�^(init�̒l�ŏ�����)
template <class T>
doublyLinkedList<T>::iterator::iterator(
	Node* init, const doublyLinkedList* hostInit)
	:constIterator(init, hostInit) {}

//�f�t�H���g�R���X�g���N�^
template<class T>
doublyLinkedList<T>::iterator::iterator() = default;

//�O�u�f�N�������g�p(--it)
template <class T>
typename doublyLinkedList<T>::iterator& doublyLinkedList<T>::iterator::operator--() {
	//����end()�Ȃǂ��疖��(�_�~�[�m�[�h)���w�肵�ăf�N�������g�����ꍇ�A
	if (this->node == &this->host->dummy) {
		//�����_�~�[��prevNode�����g���w���Ă����ꍇ�A���X�g�͋�Ȃ̂ŁAassert����
		assert(this->node->prevNode != this->node);
	}
	//���ۂɒ��g������m�[�h�������ꍇ
	else {
		//prevNode���_�~�[�������ꍇ�A�擪��ʂ�z���Ă���̂ŁAassert����
		assert(this->node->prevNode != &this->host->dummy);
	}
	this->node = this->node->prevNode;
	return *this;
}

//��u�f�N�������g�p(it--)
template <class T>
typename doublyLinkedList<T>::iterator doublyLinkedList<T>::iterator::operator--(int) {
	iterator it = *this;
	--(*this); 
	return it;
}

///�O�u�C���N�������g�p(++it)
template <class T>
typename doublyLinkedList<T>::iterator& doublyLinkedList<T>::iterator::operator++() {
	//nullptr�ł͂Ȃ��ꍇ�ƁA�_�~�[�m�[�h�ł͂Ȃ��ꍇ�̂ݒʂ�
	assert(this->node != nullptr && this->node != &this->host->dummy);
	this->node = this->node->nextNode;
	return *this;
}

///��u�C���N�������g�p(it++)
template <class T>
typename doublyLinkedList<T>::iterator doublyLinkedList<T>::iterator::operator++(int) {
	iterator it = *this;
	++(*this);
	return it;
}

//�ԐڎQ��
template <class T>
T& doublyLinkedList<T>::iterator::operator*() {
	//nullptr�ł͂Ȃ��ꍇ�ƁA�_�~�[�m�[�h�ł͂Ȃ��ꍇ�̂ݒʂ�
	assert(this->node != nullptr && this->node != &this->host->dummy);
	return this->node->data;
}

//���l��r
template <class T>
bool doublyLinkedList<T>::iterator::operator==(const iterator& comp)const {
	return this->host == comp.host && this->node == comp.node;
}

//�񓙒l��r
template <class T>
bool doublyLinkedList<T>::iterator::operator!=(const iterator& comp)const {
	return !(*this == comp);
}


//====================================================================
// ���X�g���v�f����֐�
//====================================================================
//�f�[�^���̎擾]
template <class T>
size_t doublyLinkedList<T>::size() const {
	return listSize;
}

//�擪�C�e���[�^�̎擾
template <class T>
typename doublyLinkedList<T>::iterator doublyLinkedList<T>::begin() {
	return iterator(dummy.nextNode, this);
}

//�擪�R���X�g�C�e���[�^�̎擾
template <class T>
typename doublyLinkedList<T>::constIterator doublyLinkedList<T>::cbegin() const {
	return constIterator(dummy.nextNode, this);
}

//�����C�e���[�^�̎擾
template <class T>
typename doublyLinkedList<T>::iterator doublyLinkedList<T>::end() {
	return iterator(&dummy, this);
}

//�����R���X�g�C�e���[�^�̎擾
template <class T>
typename doublyLinkedList<T>::constIterator doublyLinkedList<T>::cend() const {
	constIterator it = {};
	it.node = const_cast<Node*>(&dummy);
	it.host = this;
	return it;
}

//���X�g���̗v�f�擪����S����
template <class T>
void doublyLinkedList<T>::clear() {
	Node* current = dummy.nextNode;
	//current��dummy�ɂȂ�܂Ń��[�v���AdeleteNode�Ńm�[�h���폜
	while (current != &dummy) {
		Node* next = current->nextNode;
		deleteData(iterator(current, this));
		current = next;
	}
}

//�ʒunodePos�̒��O�ɑ}��(iterator)
template <class T>
bool doublyLinkedList<T>::insertData(const iterator& nodePos, const T& data) {
	//nodePos�ɑ΂���static_cast���s���AconstIterator��insertData���g�p
	return insertData(static_cast<const constIterator&>(nodePos), data);
}

//�ʒunodePos�̒��O�ɑ}��(constIterator)
template <class T>
bool doublyLinkedList<T>::insertData(const constIterator& nodePos, const T& datas) {
	//�C�e���[�^�̏��L�҂������łȂ��ꍇ�Afalse��Ԃ�
	if (nodePos.host != this) {
		return false;
	}

	if (nodePos.node != nullptr && !containsNode(nodePos.node)) {
		return false;
	}

	//�m�[�h��ǉ�
	Node* next = {};

	//nodePos����łȂ��ꍇ
	if (nodePos.node != nullptr) {
		//�}�������
		next = nodePos.node;
	}
	//����ȊO�̏ꍇ�̓_�~�[����
	else {
		next = &dummy;
	}

	//�V�K�m�[�h�𐶐����A�ڑ����ĕҐ�
	Node* current = new Node();
	current->prevNode = next->prevNode;
	current->nextNode = next;
	next->prevNode->nextNode = current;
	next->prevNode = current;

	//�f�[�^�������A�_�~�[�ł͂Ȃ��Ɣ��ʂ���
	current->data = datas;

	//���X�g�T�C�Y���Ǘ�����ϐ���+1
	++listSize;

	return true;
}

//�ʒunodePos�ɂ���v�f���폜(iterator)
template <class T>
bool doublyLinkedList<T>::deleteData(const iterator& nodePos) {
	//nodePos�ɑ΂���static_cast���s���AconstIterator��deleteData���g�p
	return deleteData(static_cast<const constIterator&> (nodePos));
}

//�ʒunodePos�ɂ���v�f���폜(constIterator)
template <class T>
bool doublyLinkedList<T>::deleteData(const constIterator& nodePos) {
	if (listSize == 0)               return false;
	if (nodePos.host != this)        return false;
	if (nodePos.node == nullptr)     return false;
	if (nodePos.node == &dummy)       return false;
	if (!containsNode(nodePos.node)) return false;

	Node* current = nodePos.node;

	//�m�[�h�̑O��̃|�C���^���ĕҐ�
	current->nextNode->prevNode = current->prevNode;
	current->prevNode->nextNode = current->nextNode;

	//current���폜���A���X�g�T�C�Y�����炷
	delete current;
	--listSize;

	return true;
}

//�N�C�b�N�\�[�g
template <class T>
void doublyLinkedList<T>::sortList(const int sortKey,  const bool isAscend) {
	//�������X�g�T�C�Y��1�������͂���ȉ��������ꍇ�A���f
	if (this->size() <= 1) return;

	//�������f���擪�Ɏw��
	const T element = *this->begin();


}
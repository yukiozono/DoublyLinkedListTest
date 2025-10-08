#include <cassert>

//====================================================================
// private
//====================================================================
//�����̃m�[�h�����݂��邩��T������
template <class T>
bool doublyLinkedList<T>::containsNode(const Node* node) const {
	if (node == dummy) return true;  //�w��m�[�h���_�~�[�m�[�h�ł���ꍇ�A�ꉞ���݂��Ă���̂ŁAtrue��Ԃ�

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
//�R���X�g���N�^
template <class T>
doublyLinkedList<T>::doublyLinkedList() : dummyNode{}, dummy(&dummyNode) {
	//�z���X�g�ɂ���
	dummy->nextNode = dummy->prevNode - dummy;
}

//�f�X�g���N�^
template <class T>
doublyLinkedList<T>::~doublyLinkedList() {
	clear();
	dummmy = nullptr;
}


//====================================================================
// constIterator
//====================================================================
//�R���X�g���N�^(init�̒l�ŏ�����)
//template <class T>
//doublyLinkedList<T>::constIterator::constIterator(
//	Node* init, const doublyLinkedList* hostInit)
//	: node(init), host(hostInit) {}

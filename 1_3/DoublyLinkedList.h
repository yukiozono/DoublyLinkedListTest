#pragma once
#include <string>
#include <fstream>
#include <cassert>

struct scoreData {
	int            score = 0;
	std::string    userName = {};
};

/**
 * @class doublyLinkedList
 * @brief �w�肳�ꂽ�f�[�^����荞�݁A�o�͉\�ȃ��X�g
 */
class doublyLinkedList {
private:
	struct Node {
		Node* prevNode = nullptr;    //��O�̃m�[�h�̃|�C���^
		Node* nextNode = nullptr;    //���̃m�[�h�̃|�C���^
		scoreData data = {};
	};
	size_t listSize = 0;   //���݂̃��X�g�̃T�C�Y
	Node  dummyNode;       //�_�~�[�m�[�h
	Node* dummy = nullptr;  //�_�~�[�m�[�h�A�h���X

	/**
     * @brief  �����̃m�[�h�����݂��邩��T������
     * @param  node �Ώۂ̃|�C���^
	 * @return ���݂���ꍇ��true�A�����ꍇ��false��Ԃ�
     */
	bool containsNode(const Node* node) const {
		if (node == dummy) return true;  //�w��m�[�h���_�~�[�m�[�h�ł���ꍇ�A�ꉞ���݂��Ă���̂ŁAtrue��Ԃ�

		for (Node* current = dummy->nextNode; current != dummy; current = current->nextNode) {
			if (current == node) {
				return true;
			}
		}
		return false;
	}
	

public:
	/**
	 * @brief �R���X�g���N�^
	 */
	doublyLinkedList() : dummyNode{}, dummy(&dummyNode) {

		//�z���X�g�ɂ���
		dummy->nextNode = dummy->prevNode = dummy;
	}

	/**
	 * @brief �f�X�g���N�^�Ń��X�g�̓��e���S����
	 */
	~doublyLinkedList() {
		clear();
		dummy = nullptr;
	}


	class constIterator {
		//doublyLinkedList����A�N�Z�X���邽�߂̐錾
		friend class doublyLinkedList;

	protected:
		Node* node = nullptr;

		//������
		const doublyLinkedList* host = nullptr;

		//�R���X�g���N�^(init�̒l�ŏ�����)
		explicit constIterator(Node* init, const doublyLinkedList* hostInit) : node(init), host(hostInit) {}

	public:
	    /**
	     * @brief  �f�t�H���g�R���X�g���N�^(iterator()�ďo���Anode��nullptr��)
	     */
		constIterator() = default;

		/** 
		 * @brief  �O�u�f�N�������g�p(--it)(���X�g�̐擪�Ɍ������Ĉ�i�߂�[operator--]())
		 * @return *this
		 */
		constIterator& operator--() { 
			//����end()�Ȃǂ��疖��(�_�~�[�m�[�h)���w�肵�ăf�N�������g�����ꍇ�A
			if (node == host->dummy) {
				//�����_�~�[��prevNode�����g���w���Ă����ꍇ�A���X�g�͋�Ȃ̂ŁAassert����
				assert(node->prevNode != node);
			}
			//���ۂɒ��g������m�[�h�������ꍇ
			else {
				//prevNode���_�~�[�������ꍇ�A�擪��ʂ�z���Ă���̂ŁAassert����
				assert(node->prevNode != host->dummy);
			}
			node = node->prevNode;
			return *this;;
		}

		/**
		 * @brief  ��u�f�N�������g�p(it--)(���X�g�̐擪�Ɍ������Ĉ�i�߂�[operator--]())
		 * @return �O�ɖ߂�ȑO��constIterator
		 */
		constIterator  operator--(int) { constIterator it = *this; --(*this); return it; }

		/**
		 * @brief  �O�u�C���N�������g�p(++it)(���X�g�̖����Ɍ������Ĉ�i�߂�[operator++]())
		 * @return *this
		 */
		constIterator& operator++() {
			//nullptr�ł͂Ȃ��ꍇ�ƁA�_�~�[�m�[�h�ł͂Ȃ��ꍇ�̂ݒʂ�
			assert(node != nullptr && node != host->dummy);
			node = node->nextNode; 
			return *this; 
		}

		/**
		 * @brief  ��u�C���N�������g�p(it++)(���X�g�̖����Ɍ������Ĉ�i�߂�[operator++]())
		 * @return ���ɐi�ވȑO��constIterator
		 */
		constIterator  operator++(int) { constIterator it = *this; ++(*this); return it; }

		/**
		 * @brief  �ԐڎQ��(�߂�l const scoreData&)�i�C�e���[�^�̎w���v�f���擾����[operator* const��]())
		 * @return const scoreData&
		 */
		const scoreData& operator*() const { 
			//nullptr�ł͂Ȃ��ꍇ�ƁA�_�~�[�m�[�h�ł͂Ȃ��ꍇ�̂ݒʂ�
			assert(node != nullptr && node != host->dummy);
			return node->data; 
		}

		/**
		 * @brief   �R�s�[������Z�q(iterator�̈ʒu�|�C���^���㏑��)(������s��[operator=]())
		 * @param   source �����
		 * @return  *this
		 */
		constIterator& operator=(const constIterator& source) = default;
		
		/**
		 * @brief   ���l��r(==�ł����true��Ԃ�)(�l�Ə��L�҂����ꂩ��r����[operator==]())
		 * @param   comp ��r����
		 * @return  �������ꍇ�Atrue
		 */
		bool operator==(const constIterator& comp) const {
			return host == comp.host && node == comp.node;
		}

		/**
		 * @brief   �񓙒l��r(!=�ł����true��Ԃ�)(�قȂ邩����r����[operator!=]()
		 * @param   comp ��r����
		 * @return  �������Ȃ��ꍇ�Atrue
		 */
		bool operator!=(const constIterator& comp) const {
			return !(*this == comp);
		}
	};

	class iterator : public constIterator {
		//doublyLinkedList����A�N�Z�X���邽�߂̐錾
		friend class doublyLinkedList;

		//�R���X�g���N�^(init�̒l�ŏ�����)
		explicit iterator(Node* init, const doublyLinkedList* hostInit) : constIterator(init, hostInit) {}

	public:
		//�����l��default��nullptr�ɂ��C��
		iterator() = default;

		//scoreData�ɃA�N�Z�X���邽�߂̊ԐڎQ��
		scoreData& operator*() {

			//nullptr�ł͂Ȃ��ꍇ�ƁA�_�~�[�m�[�h�ł͂Ȃ��ꍇ�̂ݒʂ�
			assert(node != nullptr && node != host->dummy);
			return node->data; 
		}

		//�擪�ł������ł��Ȃ��C�e���[�^���ڎw��p
		/**
		 * @brief  �O�u�f�N�������g�p(--it)(���X�g�̐擪�Ɍ������Ĉ�i�߂�[operator--]())
		 * @return *this
		 */
		iterator& operator--() {
			//����end()�Ȃǂ��疖��(�_�~�[�m�[�h)���w�肵�ăf�N�������g�����ꍇ�A
			if (node == host->dummy) {
				//�����_�~�[��prevNode�����g���w���Ă����ꍇ�A���X�g�͋�Ȃ̂ŁAassert����
				assert(node->prevNode != node);
			}
			//���ۂɒ��g������m�[�h�������ꍇ
			else {
				//prevNode���_�~�[�������ꍇ�A�擪��ʂ�z���Ă���̂ŁAassert����
				assert(node->prevNode != host->dummy);
			}
			node = node->prevNode; 
			return *this; 
		}

		/**
		 * @brief  ��u�f�N�������g�p(it--)(���X�g�̐擪�Ɍ������Ĉ�i�߂�[operator--]())
		 * @param  dummy(int)
		 * @return �O�ɖ߂�ȑO��iterator
		 */
		iterator  operator--(int) { iterator it = *this; --(*this); return it; }

		/**
		 * @brief  �O�u�C���N�������g�p(++it)(���X�g�̖����Ɍ������Ĉ�i�߂�[operator++]())
		 * @return *this
		 */
		iterator& operator++() {
			//nullptr�ł͂Ȃ��ꍇ�ƁA�_�~�[�m�[�h�ł͂Ȃ��ꍇ�̂ݒʂ�
			assert(node != nullptr && node != host->dummy);
			node = node->nextNode; 
			return *this; 
		}

		/**
		 * @brief  ��u�C���N�������g�p(it++)(���X�g�̖����Ɍ������Ĉ�i�߂�[operator++]())
		 * @param  dummy(int)
		 * @return ���ɐi�ވȑO��iterator
		 */
		iterator  operator++(int) { iterator it = *this; ++(*this); return it; }

		/**
		 * @brief   ���l��r(==�ł����true��Ԃ�)(���ꂩ��r����[operator==]())
		 * @param   comp ��r����
		 * @return  �������ꍇ�Atrue
		 */
		bool operator==(const iterator& comp) const {
			return host == comp.host && node == comp.node;
		}

		/**
		 * @brief   �񓙒l��r(!=�ł����true��Ԃ�)(�قȂ邩����r����[operator!=]()
		 * @param   comp ��r����
		 * @return  �������Ȃ��ꍇ�Atrue
		 */
		bool operator!=(const iterator& comp) const {
			return !(*this == comp);
		}
	};


public:
	//�f�[�^���̎擾
	size_t size() const { return listSize; }

	//�擪/�����C�e���[�^�̎擾
	/**
	* @brief   �擪�C�e���[�^�̎擾
	* @return  �z���X�g�ׁ̈A��Ƀ_�~�[�̎���n��
	*/
	iterator begin() {
		return iterator(dummy->nextNode, this);
	}

	/**
	* @brief   �擪�R���X�g�C�e���[�^�̎擾
	* @return  �z���X�g�ׁ̈A��Ƀ_�~�[�̎���n��
	*/
	constIterator cbegin() const {
		return constIterator(dummy->nextNode, this);
	}

	/**
	* @brief   �����C�e���[�^�̎擾
	* @return  �z���X�g�ׁ̈A��Ƀ_�~�[��n��
	*/
	iterator end() {
		return iterator(dummy, this);
	}

	/**
	* @brief   �����R���X�g�C�e���[�^�̎擾
	* @return  �z���X�g�ׁ̈A��Ƀ_�~�[��n��
	*/
	constIterator cend() const {
		return constIterator(dummy, this);
	}

	/**
	 * @brief          �m�[�h�ǉ�
	 * @param nodePos  �}����̃m�[�h�̈ʒu
	 * @param datas    �ǉ�����f�[�^string
	 * @return         �ǉ������m�[�h�̈ʒu
	 */
	iterator addNode(const constIterator& nodePos, const scoreData& datas) {
		Node* next = {};

		//nodePos����łȂ��ꍇ
		if (nodePos.node != nullptr) {
			//�}�������
			next = nodePos.node;
		}
		//����ȊO�̏ꍇ�̓_�~�[����
		else {
			next = dummy;
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

		return iterator(current, this);
	}


	/**
	 * @brief          �m�[�h�폜
	 * @param nodePos  �폜����m�[�h�̈ʒu
	 * @return         ���̃m�[�h�̈ʒu
	 */
	iterator deleteNode(const iterator& nodePos) {
		Node* current = nodePos.node;

		//������Ȃ������ꍇ�������̓_�~�[�������ꍇ�́A�폜�s�Ȃ̂Ń_�~�[��return
		if (current == nullptr || current == dummy) return iterator(dummy,this);

		Node* next = current->nextNode;
		Node* prev = current->prevNode;
		//�m�[�h�̑O��̃|�C���^���ĕҐ�
		prev->nextNode = next;
		next->prevNode = prev;

		//current���폜���A���X�g�T�C�Y�����炷
		delete current;
		--listSize;
		return iterator(next, this);
	}

	/**
	 * @brief ���X�g���̗v�f�擪����S����
	 */
	void clear() {
		Node* current = dummy->nextNode;
		//current��dummy�ɂȂ�܂Ń��[�v���AdeleteNode�Ńm�[�h���폜
		while (current != dummy) {
			Node* next = current->nextNode;
			deleteNode(iterator(current,this));
			current = next;
		}
		dummy->nextNode = dummy;
		dummy->prevNode = dummy;
		listSize = 0;
	}

	/**
	 * @brief �R�s�[�R���X�g���N�^���폜�B
	 */
	doublyLinkedList(const doublyLinkedList&) = delete;

	/**
	 * @brief �R�s�[������Z�q���폜�B
	 */
	doublyLinkedList& operator=(const doublyLinkedList&) = delete;

	/**
	 * @brief  �ʒunodePos�̒��O�ɑ}��(iterator)
	 * @param  nodePos �m�[�h�ʒu
	 * @param  data    ���̓f�[�^
	 * @return �����ł����true�A�s���C�e���[�^���̏ꍇ��false��Ԃ�
	 */
	bool insertData(const iterator& nodePos, const scoreData& data) {
		//nodePos�ɑ΂���static_cast���s���AconstIterator��insertData���g�p
		return insertData(static_cast<const constIterator&>(nodePos), data);
	}

	/**
	 * @brief  �ʒunodePos�̒��O�ɑ}��(constIterator)
	 * @param  nodePos �m�[�h�ʒu
	 * @param   data   ���̓f�[�^
	 * @return �����ł����true�A�s���C�e���[�^���̏ꍇ��false��Ԃ�
	 */
	bool insertData(const constIterator& nodePos, const scoreData& data) {
		//�C�e���[�^�̏��L�҂������łȂ��ꍇ�Afalse��Ԃ�
		if (nodePos.host != this) {
			return false;
		}

		if (nodePos.node != nullptr && !containsNode(nodePos.node)) {
			return false;
		}
		addNode(nodePos, data);
		return true;
	}

	/**
	 * @brief  �ʒunodePos�ɂ���v�f���폜(iterator)
	 * @param  nodePos �m�[�h�ʒu
	 * @return �����ł����true�A�����ċ�Ahost�s��v�AnodePos==end�������͕s���ł����false��Ԃ�
	 */
	bool deleteData(const iterator& nodePos) {
		//nodePos�ɑ΂���static_cast���s���AconstIterator��deleteData���g�p
		return deleteData(static_cast<const constIterator&> (nodePos));
	}

	/**
	 * @brief  �ʒunodePos�ɂ���v�f���폜(constIterator)
	 * @param  nodePos �m�[�h�ʒu
	 * @return �����ł����true�A���s�̏ꍇ��false��Ԃ�
	 */
	bool deleteData(const constIterator& nodePos) {
		if (listSize == 0)               return false;
		if (nodePos.host != this)        return false;
		if (nodePos.node == nullptr)     return false;
		if (nodePos.node == dummy)       return false;
		if (!containsNode(nodePos.node)) return false;

		deleteNode(iterator(nodePos.node,this));

		return true;
	}
};
#include "pch.h"
#include "../1_3/ScoreData.h"
#include "../1_3/DoublyLinkedList.h"

/**
* @brief ID0_0     ���X�g����ł���ꍇ�̖߂�l
*/
TEST(doublyLinkedListTest, ID0_0_ifListEmpty_return0) {
    doublyLinkedList<scoreData> list;

    EXPECT_EQ(0, list.size());        
}

/**
* @brief ID0_1     ���X�g�����ւ̑}�����s�����ۂ̖߂�l
*/
TEST(doublyLinkedListTest, ID0_1_insertToTail_return1) {
    doublyLinkedList<scoreData> list;

    //�����ɕ������}��
    list.insertData(list.cend(), scoreData{ 1, "A" });
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_2     ���X�g�����ւ̑}�������s�����ۂ̖߂�l
*/
TEST(doublyLinkedListTest, ID0_2_ifInsertToTailFailed_return0) {
    doublyLinkedList<scoreData> list1, list2;
    list2.insertData(list2.cend(), scoreData{ 1, "A" });

    //list1��list2�̐擪�C�e���[�^��n��(���s)
    list1.insertData(list2.begin(), scoreData{ 2, "B" });

    EXPECT_EQ(0, list1.size());
}

/**
* @brief ID0_3     �f�[�^�̑}�����s�����ۂ̖߂�l
*/
TEST(doublyLinkedListTest, ID0_3_ifInsertList_return1) {
    doublyLinkedList<scoreData> list;

    //�f�[�^��}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_4     �f�[�^�̑}���Ɏ��s�����ۂ̖߂�l
*/
TEST(doublyLinkedListTest, ID0_4_ifInsertListFailed_return0) {
    doublyLinkedList<scoreData> list1, list2;

    //list2��list1�̃C�e���[�^��n��(���s)
    list2.insertData(list1.cend(), scoreData{ 2, "B" });

    EXPECT_EQ(0, list2.size());
}

/**
* @brief ID0_5     �f�[�^�̍폜���s�����ۂ̖߂�l
*/
TEST(doublyLinkedListTest, ID0_5_ifDeleteList_return0) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //�f�[�^�폜
    list.deleteData(list.begin());

    EXPECT_EQ(0, list.size());
}

/**
* @brief ID0_6     �f�[�^�̍폜�����s�����ۂ̖߂�l
*/
TEST(doublyLinkedListTest, ID0_6_ifDeleteListFailed_return1) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //���݂��Ȃ��m�[�hend()���w�肵�A�폜
    int result = list.deleteData(list.end());
    EXPECT_EQ(1, list.size());
}

/**
* @brief ID0_7     ���X�g����ł���ꍇ�ɁA�f�[�^�̍폜���s�����ۂ̖߂�l
*/
TEST(doublyLinkedListTest, ID0_7_ifListEmptyDeleteData_return0) {
    doublyLinkedList<scoreData> list;

    //�v�f��ǉ��������̂܂܃m�[�h�폜���w��
    list.deleteData(list.end());
    EXPECT_EQ(0, list.size());
}

/**
* @brief ID0_8     const�̃��\�b�h�ł��邩(�r���h���ʂ�̂ŁAconst�ł���)
*/
size_t(doublyLinkedList<scoreData>::* checkConst)() const = &doublyLinkedList<scoreData>::size;

/**
* @brief ID0_9     ���X�g����ł���ꍇ�ɁA�}�������ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_9_ifListEmptyInsert_returnTRUE) {
    doublyLinkedList<scoreData> list;
    
    //�擪�֑}�������݁A��������Ԃ�
    bool check= list.insertData(list.cbegin(), scoreData{ 1, "A" });
    EXPECT_TRUE(check);

    //���X�g���N���A���čČ���
    list.clear();

    //�����֑}�������݁A��������Ԃ�
    check = list.insertData(list.cend(), scoreData{ 2, "B" });
    EXPECT_TRUE(check);

    //����ɖ����֑}�������݁A2,B������Ă��邩���m�F
    check = list.insertData(list.cend(), scoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //�������ʒu��2,B�����邩�`�F�b�N
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).name);

    //��O�i���A���e���`�F�b�N
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);


}

/**
* @brief ID0_10    ���X�g�ɕ����̗v�f������ꍇ�ɁA�擪�C�e���[�^��n���āA�}�������ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_10_ifListHasSeveralNodesInsertHeadIterator_returnTRUE) {
    doublyLinkedList<scoreData> list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });


    //����ɐ擪�֑}��
    bool check = list.insertData(list.cbegin(), scoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //�������ʒu��2,B�����邩�`�F�b�N
    doublyLinkedList<scoreData>::constIterator it = list.begin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).name);
}

/**
* @brief ID0_11        ���X�g�ɕ����̗v�f������ꍇ�ɁA�����C�e���[�^��n���āA�}�������ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_11_ifListHasSeveralNodesInsertTailIterator_returnTRUE) {
    doublyLinkedList<scoreData> list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });


    //�����֑}��
    bool check = list.insertData(list.cend(), scoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //�������ʒu��3,C�����邩�`�F�b�N
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    doublyLinkedList<scoreData>::constIterator last = it;
    for (; it != list.cend(); ++it) {
        last = it;
    }
    EXPECT_EQ(3, (*last).score);
    EXPECT_EQ(std::string("C"), (*last).name);
}

/**
* @brief ID0_12        ���X�g�ɕ����̗v�f������ꍇ�ɁA�擪�ł������ł��Ȃ��C�e���[�^��n���đ}�������ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_12_ifListHasSeveralNodesInsertMidIterator_returnTRUE) {
    doublyLinkedList<scoreData> list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 3, "C" });

    doublyLinkedList<scoreData>::iterator it = list.begin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    bool check= list.insertData(it, scoreData{ 2,"B" });
    EXPECT_TRUE(check);

    //�v�f��̐擪�Ɩ����ɑ}�����s�����ꍇ�̃P�[�X��ID0_10��ID0_11�ɂăe�X�g�ςȂ̂ŏȗ�
}

/**
* @brief ID0_13        ConstIterator���w�肵�đ}�����s�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_13_handConstIteratorAndInsert_returnTRUE) {
    doublyLinkedList<scoreData> list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), scoreData{ 2, "B" });
    list.insertData(list.cbegin(), scoreData{ 4, "D" });

    //ConstIterator���w�肵�A���Ԉʒu�܂ňړ�������
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    bool check = list.insertData(it, scoreData{ 3,"C" });
    EXPECT_TRUE(check);

    //�擪�ɑ}��
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //�����ɑ}��
    list.insertData(list.cbegin(), scoreData{ 5, "E" });
}

/**
* @brief ID0_14        �s���ȃC�e���[�^��n���āA�}�������ꍇ�̋���
*/
TEST(doublyLinkedListTest, ID0_14_InsertInvalidIterator_returnFALSE) {
    doublyLinkedList<scoreData> list1, list2;

    //list2��list1�̃C�e���[�^��n��(���s)
    bool check = list2.insertData(list1.begin(), scoreData{ 2, "B" });

    EXPECT_FALSE(check);

    //���g���`�F�b�N����
}

/**
* @brief ID0_15        ��const�̃��\�b�h�ł��邩(�Ӑ}���ꂽ�r���h�G���[�̂��߁A�R�����g�A�E�g)
*/
//bool (doublyLinkedList<scoreData>::* checkNotConst)(const doublyLinkedList<scoreData>::iterator&, const scoreData&) const= &doublyLinkedList<scoreData>::insertData;

/**
* @brief ID0_16        ���X�g����ł���ꍇ�ɁA�폜���s�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_16_deleteNodeWhileEmpty_returnFALSE) {
    doublyLinkedList<scoreData> list;

    //�v�f��ǉ��������̂܂܃m�[�h�폜���w��
      //�������w�肵�A�`�F�b�N
    bool check = list.deleteData(list.cend());
    EXPECT_FALSE(check);

      //�擪���w�肵�A�`�F�b�N
    check = list.deleteData(list.cbegin());
    EXPECT_FALSE(check);

}

/**
* @brief ID0_17        ���X�g�ɕ����̗v�f������ꍇ�ɁA�擪�C�e���[�^��n���āA�폜�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_17_ifListHasSeveralNodesInsertHeadIterator_andDelete_returnTRUE) {
    doublyLinkedList<scoreData> list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });


    //����ɐ擪�֑}��
    list.insertData(list.cbegin(), scoreData{ 3,"C" });

    //�擪�v�f���폜
    bool check = list.deleteData(list.cbegin());
    EXPECT_TRUE(check);
}

/**
* @brief ID0_18        ���X�g�ɕ����̗v�f������ꍇ�ɁA�����C�e���[�^��n���āA�폜�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_18_ifListHasSeveralNodesInsertTailIterator_andDelete_returnFALSE) {
    doublyLinkedList<scoreData> list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });


    //�����֑}��
    list.insertData(list.cend(), scoreData{ 3,"C" });

    //�v�f���폜
    bool check = list.deleteData(list.cend());
    EXPECT_FALSE(check);
}

/**
* @brief ID0_19        ���X�g�ɕ����̗v�f������ꍇ�ɁA�擪�ł������ł��Ȃ��C�e���[�^��n���č폜�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_19_ifListHasSeveralNodesInsertMidIterator_andDelete_returnTRUE) {
    doublyLinkedList<scoreData> list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 3, "C" });

    doublyLinkedList<scoreData>::iterator it = list.begin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    list.insertData(it, scoreData{ 2,"B" });

    //���Ԃ̃C�e���[�^�ɖ߂�
    --it;

    //���Ԃ̗v�f���폜
    bool check = list.deleteData(it);
    EXPECT_TRUE(check);
}

/**
* @brief ID0_20        ConstIterator���w�肵�č폜���s�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_20_handConstIteratorAndInsert_andDelete_returnTRUE) {
    doublyLinkedList<scoreData> list;

    //�擪�֕����}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 3, "C" });

    //ConstIterator���w�肵�A���Ԉʒu�܂ňړ�������
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    list.insertData(it, scoreData{ 2,"B" });

    --it;

    //���Ԃ̗v�f���폜
    bool check = list.deleteData(it);
    EXPECT_TRUE(check);
}

/**
* @brief ID0_21        �s���ȃC�e���[�^��n���āA�폜�����ꍇ�̋���
*/
TEST(doublyLinkedListTest, ID0_21_deleteInvalidIterator_returnFALSE) {
    doublyLinkedList<scoreData> list1, list2;

    //list2��list1�̃C�e���[�^��n���A�폜������(���s)
    bool check = list2.deleteData(list1.begin());

    EXPECT_FALSE(check);
}

/**
* @brief ID0_22        ��const�̃��\�b�h�ł��邩(�Ӑ}���ꂽ�r���h�G���[�̂��߁A�R�����g�A�E�g)
*/
//bool (doublyLinkedList<scoreData>::* checkNotConst)(const doublyLinkedList<scoreData>::iterator&) const= &doublyLinkedList<scoreData>::deleteData;

/**
* @brief ID0_23        ���X�g����ł���ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_23_ifHaveNoNodeInList_ReturnDummyBeginIterator) {
    doublyLinkedList<scoreData> list;

    //�擪�Ɩ����C�e���[�^���擾
    doublyLinkedList<scoreData>::iterator beginIt = list.begin();
    doublyLinkedList<scoreData>::iterator endIt = list.end();

    //�����Ƃ��_�~�[�ł��邽�߁A���l�ł���͂�
    EXPECT_TRUE(beginIt == endIt);
}

/**
* @brief ID0_24        ���X�g�ɗv�f�������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_24_ifHaveOneNodeInList_returnBeginIterator) {
    doublyLinkedList<scoreData> list;

    //�����ɕ������}��
    list.insertData(list.end(), scoreData{ 1, "A" });
    
    //�擪�C�e���[�^���m�F
    doublyLinkedList<scoreData>::iterator it = list.begin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).name);
}

/**
* @brief ID0_25        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_25_ifHaveMoreThanTwoNodeInList_returnBeginIterator) {
    doublyLinkedList<scoreData> list;

    //�擪�ɕ������}��
    list.insertData(list.begin(), scoreData{ 1, "A" });
    list.insertData(list.begin(), scoreData{ 2, "B" });

    //�擪�C�e���[�^���m�F
    doublyLinkedList<scoreData>::iterator it = list.begin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).name);
}

/**
* @brief ID0_26        �f�[�^�̑}�����s������ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_26_afterInserted_returnBeginIterator) {
    doublyLinkedList<scoreData> list;

    //�����ɕ������}��
    list.insertData(list.cend(), scoreData{ 1, "A" });
    //�擪�C�e���[�^���m�F
    doublyLinkedList<scoreData>::iterator it = list.begin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).name);

    //�擪�ɂɕ������}��
    list.insertData(list.cbegin(), scoreData{ 3, "C" });
    //�擪�C�e���[�^���m�F
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);

    it = list.begin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    list.insertData(it, scoreData{ 2,"B" });
    //�ēx�擪�C�e���[�^���m�F
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);
    
}

/**
* @brief ID0_27        �f�[�^�̍폜���s������ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_27_afterDeleted_returnBeginIterator) {
    doublyLinkedList<scoreData> list;

    //�v�f��ǉ�
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });
    list.insertData(list.begin(), scoreData{ 3,"C" });
    
    doublyLinkedList<scoreData>::iterator it = list.begin();
    ++it;

    //���ԗv�f���폜
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);

    //�����v�f���폜
    ++it;
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);

    //�擪�v�f��ǉ����A�폜
    list.insertData(list.begin(), scoreData{ 1,"A" });
    
    //3C���w���Ă��邽�߁A��xit��߂�
    it = list.begin();
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.begin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);
}

/**
* @brief ID0_28        const�̃��X�g����AConstIterator�łȂ�Iterator�̎擾���s���Ȃ������`�F�b�N(�Ӑ}���ꂽ�r���h�G���[�̂��߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID0_28_checkIfPossibleToGetNonConstIterator) {
    const doublyLinkedList<scoreData> list;
    doublyLinkedList<scoreData>::iterator it = list.begin();
}
*/

/**
* @brief ID0_29        ���X�g����ł���ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_29_ifHaveNoNodeInList_ReturnDummyBeginConstIterator) {
    doublyLinkedList<scoreData> list;

    //�擪�Ɩ����C�e���[�^���擾
    doublyLinkedList<scoreData>::constIterator beginIt = list.cbegin();
    doublyLinkedList<scoreData>::constIterator endIt = list.cend();

    //�����Ƃ��_�~�[�ł��邽�߁A���l�ł���͂�
    EXPECT_TRUE(beginIt == endIt);
}

/**
* @brief ID0_30        ���X�g�ɗv�f�������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_30_ifHaveOneNodeInList_returnBeginConstIterator) {
    doublyLinkedList<scoreData> list;

    //�����ɕ������}��
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //�擪�C�e���[�^���m�F
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).name);
}

/**
* @brief ID0_31        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_31_ifHaveMoreThanTwoNodeInList_returnBeginConstIterator) {
    doublyLinkedList<scoreData> list;

    //�擪�ɕ������}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });

    //�擪�C�e���[�^���m�F
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).name);
}

/**
* @brief ID0_32        �f�[�^�̑}�����s������ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_32_afterInserted_returnBeginConstIterator) {
    doublyLinkedList<scoreData> list;

    //�����ɕ������}��
    list.insertData(list.cend(), scoreData{ 1, "A" });
    //�擪�C�e���[�^���m�F
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    EXPECT_EQ(1, (*it).score);
    EXPECT_EQ(std::string("A"), (*it).name);

    //�擪�ɂɕ������}��
    list.insertData(list.cbegin(), scoreData{ 3, "C" });
    //�擪�C�e���[�^���m�F
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);

    it = list.cbegin();
    ++it;

    //���Ԃ̃C�e���[�^��n���đ}��
    list.insertData(it, scoreData{ 2,"B" });
    //�ēx�擪�C�e���[�^���m�F
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);

}

/**
* @brief ID0_33        �f�[�^�̍폜���s������ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_23_afterDeleted_returnBeginConstIterator) {
    doublyLinkedList<scoreData> list;

    //�v�f��ǉ�
    list.insertData(list.cbegin(), scoreData{ 1,"A" });
    list.insertData(list.cbegin(), scoreData{ 2,"B" });
    list.insertData(list.cbegin(), scoreData{ 3,"C" });

    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    ++it;

    //���ԗv�f���폜
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);

    //�����v�f���폜
    ++it;
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);

    //�擪�v�f��ǉ����A�폜
    list.insertData(list.cbegin(), scoreData{ 1,"A" });

    //3C���w���Ă��邽�߁A��xit��߂�
    it = list.cbegin();
    list.deleteData(it);

    //�擪�ɖ߂��A�v�f���`�F�b�N
    it = list.cbegin();
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);
}

/**
* @brief ID0_34        const�̃��\�b�h�ł��邩
*/
TEST(doublyLinkedListTest, ID0_34_checkIfConst) {
    const doublyLinkedList<scoreData> list;
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();  //�R���p�C���G���[�ɂȂ�Ȃ��ׁAconst�ł���
}


/**
* @brief ID0_35        ���X�g����ł���ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_29_ifHaveNoNodeInList_ReturnDummyEndConstIterator) {
    doublyLinkedList<scoreData> list;

    //�擪�Ɩ����C�e���[�^���擾
    doublyLinkedList<scoreData>::constIterator beginIt = list.begin();
    doublyLinkedList<scoreData>::constIterator endIt = list.end();

    //�����Ƃ��_�~�[�ł��邽�߁A���l�ł���͂�
    EXPECT_TRUE(beginIt == endIt);
}

/**
* @brief ID0_36        ���X�g�ɗv�f�������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_36_ifHaveOneNodeInList_returnEndIterator) {
    doublyLinkedList<scoreData> list;

    //�����ɕ������}��
    list.insertData(list.end(), scoreData{ 1, "A" });

    //�����C�e���[�^���擾
    doublyLinkedList<scoreData>::iterator endIt = list.end();

    //�����̃C�e���[�^�����Ƀf�[�^��}��
    list.insertData(endIt, scoreData{ 2, "B" });

    //�����̃C�e���[�^�Ő������}���ł��Ă��邩���m�F
    doublyLinkedList<scoreData>::iterator it = list.begin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).name);
}

/**
* @brief ID0_37        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_37_ifHaveMoreThanTwoNodeInList_returnEndIterator) {
    doublyLinkedList<scoreData> list;

    //�擪�ɕ������}��
    list.insertData(list.begin(), scoreData{ 1, "A" });
    list.insertData(list.begin(), scoreData{ 2, "B" });

    //�����C�e���[�^���擾
    doublyLinkedList<scoreData>::iterator endIt = list.end();

    //�����̃C�e���[�^�����Ƀf�[�^��}��
    list.insertData(endIt, scoreData{ 3, "C" });

    //�����̃C�e���[�^�Ő������}���ł��Ă��邩���m�F
    doublyLinkedList<scoreData>::iterator it = list.begin();
    ++it;
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);
}

/**
* @brief ID0_38        �f�[�^�̑}�����s������ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_38_afterInserted_returnEndIterator) {
    doublyLinkedList<scoreData> list;

    //�����̃C�e���[�^�����Ƀf�[�^��}��
    list.insertData(list.end(), scoreData{2, "B"});

    //�����C�e���[�^���擾
    doublyLinkedList<scoreData>::iterator endIt = list.end();

    //�������m�F
    EXPECT_EQ(endIt,list.end());

    //�擪�ɂɕ������}��
    list.insertData(list.begin(), scoreData{ 1, "A" });
    //�������m�F
    EXPECT_EQ(endIt, list.end());
    
    //���Ԃ̃C�e���[�^��n���đ}��
    doublyLinkedList<scoreData>::iterator it = list.begin();
    ++it;
    list.insertData(it, scoreData{ 3,"C" });

    //�������m�F
    EXPECT_EQ(endIt, list.end());

}

/**
* @brief ID0_39        �f�[�^�̍폜���s������ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_39_afterDeleted_returnEndIterator) {
    doublyLinkedList<scoreData> list;

    //�v�f��ǉ�
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });
    list.insertData(list.begin(), scoreData{ 3,"C" });

    doublyLinkedList<scoreData>::iterator it = list.begin();
    ++it;

    //���ԗv�f���폜
    list.deleteData(it);

    //�擪�ɖ߂�
    it = list.begin();
    doublyLinkedList<scoreData>::iterator endIt = it;

    //�����܂ňړ����A�����Ɠ��l���m�F
    ++endIt;
    ++endIt;
    EXPECT_EQ(endIt, list.end());


    //�����v�f���폜
    ++it;
    list.deleteData(it);

    //�擪�ɖ߂�
    it = list.begin();
    endIt = it;

    //�����܂ňړ����A�����Ɠ��l���m�F
    ++endIt;
    EXPECT_EQ(endIt, list.end());

    //�擪�v�f��ǉ����A�폜
    list.insertData(list.begin(), scoreData{ 1,"A" });
    it = list.begin();
    list.deleteData(it);

    //�����܂ňړ����A�����Ɠ��l���m�F
    it = list.begin();
    endIt = it;
    ++endIt;
    EXPECT_EQ(endIt, list.end());
}

/**
* @brief ID0_40        const�̃��X�g����AConstIterator�łȂ�Iterator�̎擾���s���Ȃ������`�F�b�N(�Ӑ}���ꂽ�r���h�G���[�̂��߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID0_40_checkIfPossibleToGetNonConstIterator) {
    const doublyLinkedList<scoreData> list;
    doublyLinkedList<scoreData>::iterator it = list.end();
}
*/

/**
* @brief ID0_41        ���X�g����ł���ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_41_ifHaveNoNodeInList_ReturnDummyEndConstIterator) {
    doublyLinkedList<scoreData> list;

    //�擪�Ɩ����C�e���[�^���擾
    doublyLinkedList<scoreData>::constIterator beginIt = list.cbegin();
    doublyLinkedList<scoreData>::constIterator endIt = list.cend();

    //�����Ƃ��_�~�[�ł��邽�߁A���l�ł���͂�
    EXPECT_TRUE(beginIt == endIt);
}

/**
* @brief ID0_42        ���X�g�ɗv�f�������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_42_ifHaveOneNodeInList_returnEndConstIterator) {
    doublyLinkedList<scoreData> list;

    //�����ɕ������}��
    list.insertData(list.cend(), scoreData{ 1, "A" });

    //�����R���X�g�C�e���[�^���擾
    doublyLinkedList<scoreData>::constIterator endIt = list.cend();

    //�����̃C�e���[�^�����Ƀf�[�^��}��
    list.insertData(endIt, scoreData{ 2, "B" });

    //�����̃C�e���[�^�Ő������}���ł��Ă��邩���m�F
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    ++it;
    EXPECT_EQ(2, (*it).score);
    EXPECT_EQ(std::string("B"), (*it).name);

    //�������m�F
    EXPECT_EQ(endIt, list.cend());
}

/**
* @brief ID0_43        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_43_ifHaveMoreThanTwoNodeInList_returnEndConstIterator) {
    doublyLinkedList<scoreData> list;

    //�擪�ɕ������}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    list.insertData(list.cbegin(), scoreData{ 2, "B" });

    //�����C�e���[�^���擾
    doublyLinkedList<scoreData>::constIterator endIt = list.cend();

    //�����̃C�e���[�^�����Ƀf�[�^��}��
    list.insertData(endIt, scoreData{ 3, "C" });

    //�����̃C�e���[�^�Ő������}���ł��Ă��邩���m�F
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    ++it;
    ++it;
    EXPECT_EQ(3, (*it).score);
    EXPECT_EQ(std::string("C"), (*it).name);

    //�������m�F
    EXPECT_EQ(endIt, list.cend());
}

/**
* @brief ID0_44        �f�[�^�̑}�����s������ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_44_afterInserted_returnEndConstIterator) {
    doublyLinkedList<scoreData> list;

    //�����̃C�e���[�^�����Ƀf�[�^��}��
    list.insertData(list.cend(), scoreData{2, "B"});

    //�����C�e���[�^���擾
    doublyLinkedList<scoreData>::constIterator endIt = list.cend();

    //endIt���v���X���A�����Ɠ��l���m�F
    EXPECT_EQ(endIt, list.cend());

    //�擪�ɂɕ������}��
    list.insertData(list.cbegin(), scoreData{ 1, "A" });
    //�������m�F
    EXPECT_EQ(endIt, list.cend());

    //���Ԃ̃C�e���[�^��n���đ}��
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    ++it;
    list.insertData(it, scoreData{ 3,"C" });

    //�������m�F
    EXPECT_EQ(endIt, list.cend());

}

/**
* @brief ID0_45        �f�[�^�̍폜���s������ɁA�Ăяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID0_45_afterDeleted_returnEndConstIterator) {
    doublyLinkedList<scoreData> list;

    //�v�f��ǉ�
    list.insertData(list.cbegin(), scoreData{ 1,"A" });
    list.insertData(list.cbegin(), scoreData{ 2,"B" });
    list.insertData(list.cbegin(), scoreData{ 3,"C" });

    doublyLinkedList<scoreData>::constIterator it = list.cbegin();
    ++it;

    //���ԗv�f���폜
    list.deleteData(it);

    //�擪�ɖ߂�
    it = list.cbegin();
    doublyLinkedList<scoreData>::constIterator endIt = it;

    //�����܂ňړ����A�����Ɠ��l���m�F
    ++endIt;
    ++endIt;
    EXPECT_EQ(endIt, list.cend());


    //�����v�f���폜
    ++it;
    list.deleteData(it);

    //�擪�ɖ߂�
    it = list.cbegin();
    endIt = it;

    //�����܂ňړ����A�����Ɠ��l���m�F
    ++endIt;
    EXPECT_EQ(endIt, list.cend());

    //�擪�v�f��ǉ����A�폜
    list.insertData(list.cbegin(), scoreData{ 1,"A" });
    it = list.cbegin();
    list.deleteData(it);

    //�����܂ňړ����A�����Ɠ��l���m�F
    it = list.cbegin();
    endIt = it;
    ++endIt;
    EXPECT_EQ(endIt, list.cend());
}

/**
* @brief ID0_46        const�̃��\�b�h�ł��邩
*/
TEST(doublyLinkedListTest, ID0_46_checkIfConst) {
    const doublyLinkedList<scoreData> list;
    doublyLinkedList<scoreData>::constIterator it = list.cend();  //�R���p�C���G���[�ɂȂ�Ȃ��ׁAconst�ł���
}

/**
* @brief ID1_0        ���X�g�̎Q�Ƃ��Ȃ���ԂŌĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_0_whileNoListReference_callAssert) {
    doublyLinkedList<scoreData> list;
 
    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();

        //�X�R�A����(���X�g����ł��邽�߁Aassert����)
        (*it).score = 10;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();
        //�X�R�A�ǂݎ��(���X�g����ł��邽�߁Aassert����)
        int score = (*constIt).score;
    }
}
*/

/**
* @brief ID1_1        Iterator����擾�����v�f�ɑ΂��āA�l�̑�����s���邩���`�F�b�N
*/
TEST(doublyLinkedListTest, ID1_1_ifPossibleToAssignValueFromIterator) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    doublyLinkedList<scoreData>::iterator it = list.begin();

    //�X�R�A����
    (*it).score = 10;

    //���e���ύX����Ă��邩�`�F�b�N
    EXPECT_EQ(10, (*it).score);
}

/**
* @brief ID1_2        ConstIterator����擾�����v�f�ɑ΂��āA�l�̑�����s���Ȃ������`�F�b�N(�R���p�C���G���[�Ȃ̂ŃR�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_2_ifPossibleToAssignValueFromConstIterator) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.cbegin(), scoreData{ 1,"A" });
    doublyLinkedList<scoreData>::constIterator it = list.cbegin();

    //�X�R�A����(����s�Ȃ̂ŃR���p�C���G���[)
    (*it).score = 10;

}
*/

/**
* @brief ID1_3        ���X�g����̍ۂ́A�擪�C�e���[�^�ɑ΂��ČĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_3_ifListEmptyCallBeginIterator_callAssert) {
    doublyLinkedList<scoreData> list;
    
    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.begin();

        //�X�R�A����(���X�g����Ȃ̂�assert����)
        (*it).score = 10;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cbegin();
        //�X�R�A�ǂݎ��(���X�g����Ȃ̂�assert����)
        int score = (*constIt).score;
    }
}
*/

/**
* @brief ID1_4        �����C�e���[�^�ɑ΂��ČĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_4_callFromEndIterator_callAssert) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();

        //�X�R�A����(�����͋�Ȃ̂�assert����)
        (*it).score = 10;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();
        //�X�R�A�ǂݎ��(�_�~�[�m�[�h�Ȃ̂�assert����)
        int score = (*constIt).score;
    }
}
*/

/**
* @brief ID1_5        ���X�g�̎Q�Ƃ��Ȃ���ԂŌĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_5_whileNoListReference_callAssert) {
    doublyLinkedList<scoreData> list;

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();

        //�v�f����i�߂�(�_�~�[�m�[�h�ł��邽�߁Aassert����)
        ++it;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();
        //�X�R�A�ǂݎ��(�_�~�[�m�[�h�ł��邽�߁Aassert����)
        int score = (*constIt).score;
    }
}
*/

/**
* @brief ID1_6        ���X�g����̍ۂ́A�擪�C�e���[�^�ɑ΂��ČĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_6_ifListEmptyIncrementFromBeginIterator_callAssert) {
    doublyLinkedList<scoreData> list;
    
    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.begin();

        //�v�f����i�߂�(�_�~�[�m�[�h�ł��邽�߁Aassert����)
        ++it;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cbegin();
        //�v�f����i�߂�(�_�~�[�m�[�h�Ȃ̂�assert����)
        ++constIt;
    }
}
*/

/**
* @brief ID1_7        �����C�e���[�^�ɑ΂��ČĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_7_usingIncremetFromEndIterator_callAssert) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();

        //�v�f����i�߂�(�����͋�Ȃ̂�assert����)
        ++it;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();
        //�v�f����i�߂�(�����͋�Ȃ̂�assert����)
        ++constIt;
    }
}
*/

/**
* @brief ID1_8        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɌĂяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID1_8_ifHaveMoreThanTwoElementsUsingIncrement) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });
    list.insertData(list.begin(), scoreData{ 3,"C" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.begin();

        //���g���m�F
        EXPECT_EQ(3, (*it).score);

        //�v�f����i�߁A���g���m�F
        ++it;
        EXPECT_EQ(2, (*it).score);

        //�v�f����i�߁A���g���m�F
        ++it;
        EXPECT_EQ(1, (*it).score);
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cbegin();

        //���g���m�F
        EXPECT_EQ(3, (*constIt).score);

        //�v�f����i�߁A���g���m�F
        ++constIt;
        EXPECT_EQ(2, (*constIt).score);

        //�v�f����i�߁A���g���m�F
        ++constIt;
        EXPECT_EQ(1, (*constIt).score);
    }
}

/**
* @brief ID1_9        �O�u�C���N�������g���s�����ۂ̋���( ++���Z�q�I�[�o�[���[�h�Ŏ��������ꍇ )
*/
TEST(doublyLinkedListTest, ID1_9_ifUsingPreIncrement) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.begin();
        doublyLinkedList<scoreData>::iterator headIt = list.begin();
        doublyLinkedList<scoreData>::iterator checkIt;

        //���g���m�F
        EXPECT_EQ(2, (*headIt).score);

        //�v�f����i�߁A���g���m�F
        checkIt = ++it;
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ(2, (*headIt).score);

        //�߂�l�����������m�F
        EXPECT_EQ(checkIt, it);
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cbegin();
        doublyLinkedList<scoreData>::constIterator constHeadIt = list.cbegin();
        doublyLinkedList<scoreData>::constIterator constCheckIt;

        //���g���m�F
        EXPECT_EQ(2, (*constHeadIt).score);

        //�v�f����i�߁A���g���m�F
        constCheckIt = ++constIt;
        EXPECT_EQ(1, (*constIt).score);
        EXPECT_EQ(2, (*constHeadIt).score);

        //�߂�l�����������m�F
        EXPECT_EQ(constCheckIt, constIt);
    }
}


/**
* @brief ID1_10        ��u�C���N�������g���s�����ۂ̋���( ++���Z�q�I�[�o�[���[�h�Ŏ��������ꍇ )
*/
TEST(doublyLinkedListTest, ID1_9_ifUsingPostIncrement) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.begin();
        doublyLinkedList<scoreData>::iterator headIt = list.begin();
        doublyLinkedList<scoreData>::iterator checkIt;

        //���g���m�F
        EXPECT_EQ(2, (*headIt).score);

        //�v�f����i�߁A���g���m�F
        checkIt = it++;
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ(2, (*headIt).score);

        //�߂�l�����������m�F(����O�̐擪�A�h���X�Ɠ��l�ł���͂�)
        EXPECT_EQ(checkIt, headIt);
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cbegin();
        doublyLinkedList<scoreData>::constIterator constHeadIt = list.cbegin();
        doublyLinkedList<scoreData>::constIterator constCheckIt;

        //���g���m�F
        EXPECT_EQ(2, (*constHeadIt).score);

        //�v�f����i�߁A���g���m�F
        constCheckIt = constIt++;
        EXPECT_EQ(1, (*constIt).score);
        EXPECT_EQ(2, (*constHeadIt).score);

        //�߂�l�����������m�F(����O�̐擪�A�h���X�Ɠ��l�ł���͂�)
        EXPECT_EQ(constCheckIt, constHeadIt);
    }
}

/**
* @brief ID1_11        ���X�g�̎Q�Ƃ��Ȃ���ԂŌĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_11_whileNoListReference_callAssert) {
    doublyLinkedList<scoreData> list;

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();

        //�v�f����i�߂�(�_�~�[�m�[�h�ł��邽�߁Aassert����)
        --it;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();
        //�v�f����i�߂�(�_�~�[�m�[�h�ł��邽�߁Aassert����)
        --constIt;
    }
}
*/

/**
* @brief ID1_12        ���X�g����̍ۂ́A�����C�e���[�^�ɑ΂��ČĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_12_ifListEmptyDecrementFromEndIterator_callAssert) {
    doublyLinkedList<scoreData> list;

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();

        //�v�f����i�߂�(�_�~�[�m�[�h�ł��邽�߁Aassert����)
        --it;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();
        //�v�f����i�߂�(�_�~�[�m�[�h�ł��邽�߁Aassert����)
        --constIt;
    }
}
*/

/**
* @brief ID1_13        �擪�C�e���[�^�ɑ΂��ČĂяo�����ۂ̋���(assert���������邽�߁A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_13_usingDecremetFromBeginIterator_callAssert) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.begin();

        //�v�f����i�߂�(�����͋�Ȃ̂�assert����)
        --it;
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cbegin();
        //�v�f����i�߂�(�����͋�Ȃ̂�assert����)
        --constIt;
    }
}
*/

/**
* @brief ID1_14        ���X�g�ɓ�ȏ�̗v�f������ꍇ�ɌĂяo�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID1_14_ifHaveMoreThanTwoElementsUsingDecrement) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });
    list.insertData(list.begin(), scoreData{ 3,"C" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();
        

        //�_�~�[�m�[�h�����߂��A���g���m�F
        --it;
        EXPECT_EQ(1, (*it).score);

        //�v�f����߂��A���g���m�F
        --it;
        EXPECT_EQ(2, (*it).score);

        //�v�f����߂��A���g���m�F
        --it;
        EXPECT_EQ(3, (*it).score);
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();

        //�_�~�[�m�[�h�����߂��A���g���m�F
        --constIt;
        EXPECT_EQ(1, (*constIt).score);

        //�v�f����i�߁A���g���m�F
        --constIt;
        EXPECT_EQ(2, (*constIt).score);

        //�v�f����i�߁A���g���m�F
        --constIt;
        EXPECT_EQ(3, (*constIt).score);
    }
}
/**
* @brief ID1_15        �O�u�f�N�������g���s�����ۂ̋���( --���Z�q�I�[�o�[���[�h�Ŏ��������ꍇ )
*/
TEST(doublyLinkedListTest, ID1_15_ifUsingPreDecrement) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();
        doublyLinkedList<scoreData>::iterator endIt = list.end();
        doublyLinkedList<scoreData>::iterator checkIt;

        //���g���m�F
        --endIt;
         checkIt = --it;
        EXPECT_EQ(1, (*endIt).score);

        //�߂�l�����������m�F(�擪�����i�񂾃A�h���X�Ɠ��l�ł���͂�)
        endIt = list.begin();
        ++endIt;
        EXPECT_EQ(checkIt, endIt);

        //�v�f����i�߁A���g���m�F
        checkIt = --it;
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ(1, (*endIt).score);

        //�߂�l�����������m�F(�擪�Ɠ��l�ł���͂�)
        it = list.begin();
        EXPECT_EQ(checkIt, it);
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();
        doublyLinkedList<scoreData>::constIterator constEndIt = list.cend();
        doublyLinkedList<scoreData>::constIterator constCheckIt;

        //���g���m�F
        --constIt;
        constCheckIt = --constEndIt;
        EXPECT_EQ(1, (*constEndIt).score);

        //�߂�l�����������m�F(�擪�����i�񂾃A�h���X�Ɠ��l�ł���͂�)
        constEndIt = list.begin();
        ++constEndIt;
        EXPECT_EQ(constCheckIt, constEndIt);

        //�v�f����i�߁A���g���m�F
        constCheckIt = --constIt;
        EXPECT_EQ(2, (*constIt).score);
        EXPECT_EQ(1, (*constEndIt).score);

        //�߂�l�����������m�F(�擪�Ɠ��l�ł���͂�)
        constIt = list.begin();
        EXPECT_EQ(constCheckIt, constIt);
    }
}

/**
* @brief ID1_16        ��u�f�N�������g���s�����ۂ̋���( --���Z�q�I�[�o�[���[�h�Ŏ��������ꍇ )
*/
TEST(doublyLinkedListTest, ID1_16_ifUsingPostDecrement) {
    doublyLinkedList<scoreData> list;
    list.insertData(list.begin(), scoreData{ 1,"A" });
    list.insertData(list.begin(), scoreData{ 2,"B" });

    {
        //iterator���Ńe�X�g
        doublyLinkedList<scoreData>::iterator it = list.end();
        doublyLinkedList<scoreData>::iterator endIt = list.end();
        doublyLinkedList<scoreData>::iterator checkIt;

        //���g���m�F
        endIt--;
        checkIt = it--;
        EXPECT_EQ(1, (*endIt).score);

        //�߂�l�����������m�F(�����Ɠ��l�ł���͂�)
        EXPECT_EQ(checkIt, list.end());

        //�v�f����i�߁A���g���m�F
        checkIt = it--;
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ(1, (*endIt).score);

        //�߂�l�����������m�F(�擪�����i�񂾃A�h���X�Ɠ��l�ł���͂�)
        endIt = list.begin();
        ++endIt;
        EXPECT_EQ(checkIt, endIt);
    }

    {
        //constIterator���Ńe�X�g
        doublyLinkedList<scoreData>::constIterator constIt = list.cend();
        doublyLinkedList<scoreData>::constIterator constEndIt = list.cend();
        doublyLinkedList<scoreData>::constIterator constCheckIt;

        //���g���m�F
        constCheckIt = constIt--;
        constEndIt--;
        EXPECT_EQ(1, (*constEndIt).score);

        //�߂�l�����������m�F(�����Ɠ��l�ł���͂�)
        EXPECT_EQ(constCheckIt, list.end());

        //�v�f����i�߁A���g���m�F
        constCheckIt = constIt--;
        EXPECT_EQ(2, (*constIt).score);
        EXPECT_EQ(1, (*constEndIt).score);

        //�߂�l�����������m�F(�擪�����i�񂾃A�h���X�Ɠ��l�ł���͂�)
        constEndIt = list.begin();
        ++constEndIt;
        EXPECT_EQ(constCheckIt, constEndIt);
    }
}

/**
* @brief ID1_17        ConstIterator����AIterator�̃R�s�[���쐬����Ȃ������`�F�b�N(�R���p�C���G���[�ׁ̈A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_17_checkNotPossibleToCreateCopyOfIteratorFromConst) {
    doublyLinkedList<scoreData> list;

    //�R�s�[���쐬�ł��Ȃ��ׁA�R���p�C���G���[
    doublyLinkedList<scoreData>::iterator it = list.cbegin();
 
}
*/

/**
* @brief ID1_18        �R�s�[�R���X�g���N�g��̒l���R�s�[���Ɠ��������Ƃ��`�F�b�N
*/
TEST(doublyLinkedListTest, ID1_18_checkIfAfterCopyHasSameValue) {
    doublyLinkedList<scoreData> list;

    //�R�s�[���s��
    doublyLinkedList<scoreData>::iterator it = list.begin();

    EXPECT_EQ(it, list.begin());
}

/**
* @brief ID1_19        Iterator��ConstIterator�����ł��Ȃ������`�F�b�N(�R���p�C���G���[�ׁ̈A�R�����g�A�E�g)
*/
/*
TEST(doublyLinkedListTest, ID1_20_checkNotPossibleAssignConstIntoIterator) {
    doublyLinkedList<scoreData> list;

    doublyLinkedList<scoreData>::iterator      it      = list.begin();
    doublyLinkedList<scoreData>::constIterator constIt = list.cbegin();

    //����ł��Ȃ��ׁA�R���p�C���G���[
    it = constIt;
}
*/

/**
* @brief ID1_20        �����̒l���R�s�[���Ɠ��������Ƃ��`�F�b�N
*/
TEST(doublyLinkedListTest, ID1_20_checkIfAfterAssignHasSameValue) {
    doublyLinkedList<scoreData> list;

    //�R�s�[���s��
    doublyLinkedList<scoreData>::iterator it = list.begin();
    doublyLinkedList<scoreData>::iterator it2;

    //�l����
    it2 = it;

    EXPECT_EQ(it, it2);
}

/**
* @brief ID1_21        ���X�g����̏�Ԃł̐擪�C�e���[�^�Ɩ����C�e���[�^���r�����ۂ̋������`�F�b�N
*/
TEST(doublyLinkedListTest, ID1_21_checkIfCompareBetweenBeginAndEndIterator_returnTRUE) {
    doublyLinkedList<scoreData> list;
    doublyLinkedList<scoreData>::iterator it = list.begin();
    doublyLinkedList<scoreData>::iterator it2;

    EXPECT_TRUE(list.end() == list.begin());
}

/**
* @brief ID1_22        ����̃C�e���[�^���r�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID1_22_checkIfCompareBetweenSameIterator_returnTRUE) {
    doublyLinkedList<scoreData> list;

    doublyLinkedList<scoreData>::iterator it = list.begin();
    doublyLinkedList<scoreData>::iterator it2 = list.begin();
    EXPECT_TRUE(it == it2);
}

/**
* @brief ID1_23        �قȂ�C�e���[�^���r�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID1_23_checkIfCompareBetweenDifferentIterator_returnFALSE) {
    doublyLinkedList<scoreData> list;



    //�f�[�^��}��
    list.insertData(list.begin(), scoreData{ 1,"A" });

    doublyLinkedList<scoreData>::iterator it = list.begin();
    doublyLinkedList<scoreData>::iterator it2 = list.begin();

    //�O�i���A�قȂ�C�e���[�^�ɂ���
    ++it2;


    EXPECT_FALSE(it == it2);
}

/**
* @brief ID1_24        ���X�g����̏�Ԃł̐擪�C�e���[�^�Ɩ����C�e���[�^���r�����ۂ̋������`�F�b�N
*/
TEST(doublyLinkedListTest, ID1_24_checkIfCompareBetweenBeginAndEndIterator_returnFALSE) {
    doublyLinkedList<scoreData> list;
    doublyLinkedList<scoreData>::iterator it = list.begin();
    doublyLinkedList<scoreData>::iterator it2;

    EXPECT_FALSE(list.end() != list.begin());
}

/**
* @brief ID1_25        ����̃C�e���[�^���r�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID1_25_checkIfCompareBetweenSameIterator_returnFALSE) {
    doublyLinkedList<scoreData> list;

    doublyLinkedList<scoreData>::iterator it = list.begin();
    doublyLinkedList<scoreData>::iterator it2 = list.begin();
    EXPECT_FALSE(it != it2);
}

/**
* @brief ID1_26        �قȂ�C�e���[�^���r�����ۂ̋���
*/
TEST(doublyLinkedListTest, ID1_26_checkIfCompareBetweenDifferentIterator_returnTRUE) {
    doublyLinkedList<scoreData> list;



    //�f�[�^��}��
    list.insertData(list.begin(), scoreData{ 1,"A" });

    doublyLinkedList<scoreData>::iterator it = list.begin();
    doublyLinkedList<scoreData>::iterator it2 = list.begin();

    //�O�i���A�قȂ�C�e���[�^�ɂ���
    ++it2;


    EXPECT_TRUE(it != it2);
}

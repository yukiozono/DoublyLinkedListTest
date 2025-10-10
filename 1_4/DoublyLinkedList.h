#pragma once
#include <string>
#include <cassert>

/**
 * @class doublyLinkedList
 * @brief 指定されたデータを取り込み、出力可能なリスト
 */
template <class T>
class doublyLinkedList {
private:
	struct Node {
		Node* prevNode = nullptr;    //一つ前のノードのポインタ
		Node* nextNode = nullptr;    //一つ後のノードのポインタ
		T data = {};
	};
	size_t listSize = 0;   //現在のリストのサイズ
	Node  dummy = {};       //ダミーノード

	/**
     * @brief  引数のノードが存在するかを探索する
     * @tparam  node 対象のポインタ
	 * @return 存在する場合はtrue、無い場合はfalseを返す
     */
	bool containsNode(const Node* node) const;

	

public:
	/**
	 * @brief コンストラクタ
	 */
	doublyLinkedList();

	/**
	 * @brief デストラクタでリストの内容物全消去
	 */
	~doublyLinkedList();

	class constIterator {
		//doublyLinkedListからアクセスするための宣言
		friend class doublyLinkedList;

	protected:
		Node* node = nullptr;

		//生成元
		const doublyLinkedList* host = nullptr;

		//コンストラクタ(initの値で初期化)
		explicit constIterator(Node* init, const doublyLinkedList* hostInit);

	public:
	    /**
	     * @brief  デフォルトコンストラクタ(iterator()呼出時、nodeをnullptrに)
	     */
		constIterator();

		/** 
		 * @brief  前置デクリメント用(--it)(リストの先頭に向かって一つ進める[operator--]())
		 * @return *this
		 */
		constIterator& operator--();

		/**
		 * @brief  後置デクリメント用(it--)(リストの先頭に向かって一つ進める[operator--]())
		 * @return 前に戻る以前のconstIterator
		 */
		constIterator  operator--(int);

		/**
		 * @brief  前置インクリメント用(++it)(リストの末尾に向かって一つ進める[operator++]())
		 * @return *this
		 */
		constIterator& operator++();

		/**
		 * @brief  後置インクリメント用(it++)(リストの末尾に向かって一つ進める[operator++]())
		 * @return 次に進む以前のconstIterator
		 */
		constIterator  operator++(int);

		/**
		 * @brief  間接参照(戻り値 const T&)（イテレータの指す要素を取得する[operator* const版]())
		 * @return const T&
		 */
		const T& operator*()const;

		/**
		 * @brief   コピー代入演算子(iteratorの位置ポインタを上書き)(代入を行う[operator=]())
		 * @tparam   source 代入元
		 * @return  *this
		 */
		constIterator& operator=(const constIterator& source);
		
		/**
		 * @brief   等値比較(==であればtrueを返す)(値と所有者が同一か比較する[operator==]())
		 * @tparam   comp 比較相手
		 * @return  等しい場合、true
		 */
		bool operator==(const constIterator& comp) const;

		/**
		 * @brief   非等値比較(!=であればtrueを返す)(異なるかか比較する[operator!=]()
		 * @tparam   comp 比較相手
		 * @return  等しくない場合、true
		 */
		bool operator!=(const constIterator& comp) const;
	};

	class iterator : public constIterator {
		//doublyLinkedListからアクセスするための宣言
		friend class doublyLinkedList;

		//コンストラクタ(initの値で初期化)
		explicit iterator(Node* init, const doublyLinkedList* hostInit);

	public:
		//初期値はdefaultのnullptrにお任せ
		iterator();

		//先頭でも末尾でもないイテレータ直接指定用
		/**
		 * @brief  前置デクリメント用(--it)(リストの先頭に向かって一つ進める[operator--]())
		 * @return *this
		 */
		iterator& operator--();

		/**
		 * @brief  後置デクリメント用(it--)(リストの先頭に向かって一つ進める[operator--]())
		 * @tparam  dummy(int)
		 * @return 前に戻る以前のiterator
		 */
		iterator  operator--(int);

		/**
		 * @brief  前置インクリメント用(++it)(リストの末尾に向かって一つ進める[operator++]())
		 * @return *this
		 */
		iterator& operator++();

		/**
		 * @brief  後置インクリメント用(it++)(リストの末尾に向かって一つ進める[operator++]())
		 * @tparam  dummy(int)
		 * @return 次に進む以前のiterator
		 */
		iterator  operator++(int);

		/**
		 * @brief  間接参照(戻り値 T&)（イテレータの指す要素を取得する[operator*]())
		 * @return T&
		 */
		T& operator*();

		/**
		 * @brief   等値比較(==であればtrueを返す)(同一か比較する[operator==]())
		 * @tparam   comp 比較相手
		 * @return  等しい場合、true
		 */
		bool operator==(const iterator& comp) const;

		/**
		 * @brief   非等値比較(!=であればtrueを返す)(異なるかか比較する[operator!=]()
		 * @tparam   comp 比較相手
		 * @return  等しくない場合、true
		 */
		bool operator!=(const iterator& comp) const;
	};


public:
	/**
	* @brief   データ数の取得
	* @return  現在リスト内にある要素数を返す
	*/
	size_t size() const;

	//先頭/末尾イテレータの取得
	/**
	* @brief   先頭イテレータの取得
	* @return  循環リストの為、常にダミーの次を渡す
	*/
	iterator begin();

	/**
	* @brief   先頭コンストイテレータの取得
	* @return  循環リストの為、常にダミーの次を渡す
	*/
	constIterator cbegin() const;

	/**
	* @brief   末尾イテレータの取得
	* @return  循環リストの為、常にダミーを渡す
	*/
	iterator end();

	/**
	* @brief   末尾コンストイテレータの取得
	* @return  循環リストの為、常にダミーを渡す
	*/
	constIterator cend() const;

	/**
	 * @brief リスト内の要素先頭から全消去
	 */
	void clear();

	/**
	 * @brief コピーコンストラクタを削除
	 */
	doublyLinkedList(const doublyLinkedList&) = delete;

	/**
	 * @brief コピー代入演算子を削除
	 */
	doublyLinkedList& operator=(const doublyLinkedList&) = delete;

	/**
	 * @brief  位置nodePosの直前に挿入(iterator)
	 * @tparam  nodePos ノード位置
	 * @tparam  data    入力データ
	 * @return 成功であればtrue、不正イテレータ等の場合はfalseを返す
	 */
	bool insertData(const iterator& nodePos, const T& data);

	/**
	 * @brief  位置nodePosの直前に挿入(constIterator)
	 * @tparam  nodePos ノード位置
	 * @tparam   data   入力データ
	 * @return 成功であればtrue、不正イテレータ等の場合はfalseを返す
	 */
	bool insertData(const constIterator& nodePos, const T& datas);

	/**
	 * @brief  位置nodePosにある要素を削除(iterator)
	 * @tparam  nodePos ノード位置
	 * @return 成功であればtrue、そして空、host不一致、nodePos==endもしくは不正であればfalseを返す
	 */
	bool deleteData(const iterator& nodePos);

	/**
	 * @brief  位置nodePosにある要素を削除(constIterator)
	 * @tparam  nodePos ノード位置
	 * @return 成功であればtrue、失敗の場合はfalseを返す
	 */
	bool deleteData(const constIterator& nodePos);

	/**
	 * @brief  リストをクイックソートでソートする
	 * @tparam  element  ソートキー
	 * @tparam  isAscend 昇順であるかどうか
	 * @return 成功であればtrue、失敗の場合はfalseを返す
	 * @note   参考URL:(https://www.seplus.jp/dokushuzemi/ec/fe/fenavi/similar_programming/quick_sort/)(https://algs4.cs.princeton.edu/23quicksort/)
	 */
	void sortList(const int sortKey, const bool isAscend);
};

//.inlをインクルード
#include "DoublyLinkedList.inl"
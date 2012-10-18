// CORE.Collection.h
//////////////////////////////////////////////////

#ifndef __CORE_COLLECTION_H_
#define __CORE_COLLECTION_H_

namespace GameCore {

	template <class T>
	class Node {
	public:
		Node() {
			this->m_pNext = NULL;
			this->m_pPrev = NULL;
			this->m_pData = NULL;
		}

		Node *m_pNext, *m_pPrev;
		T* m_pData;
	};

	template <class T>
	class Collection {
		Node<T>* m_pCurrent;

	public:
		Node<T>* m_pRoot;

		Collection() {
			this->m_pCurrent = NULL;
			this->m_pRoot = NULL;
		}

		// Collection has the ability to Enumerate
		void _BeginEnumerate() {
			this->m_pCurrent = this->m_pRoot;
		}

		Node<T>* _GetNextNode() {
			Node<T>* pRet = this->m_pCurrent;
			if(this->m_pCurrent != NULL) {
				this->m_pCurrent = this->m_pCurrent->m_pNext;
			}
			return pRet;
		}

		T* _GetNextData() {
			Node<T>* pRet = this->m_pCurrent;
			if(this->m_pCurrent != NULL) {
				this->m_pCurrent = this->m_pCurrent->m_pNext;
			}
			return pRet != NULL ? pRet->m_pData : NULL;
		}
		
		// Collection has the ability to Add and Remove
		void _Add(Node<T>* pNode) {
			// Validate parameters
			if(pNode == NULL) return;
			// Check for adding at beginning condition
			if(this->m_pRoot == NULL) {
				this->m_pRoot = pNode;
			} else {
				// Find the end of the list
				Node<T>* pCurr = this->m_pRoot;
				while(pCurr->m_pNext != NULL) {
					pCurr = pCurr->m_pNext;
				}
				// Attach the given node at the end of the list
				pCurr->m_pNext = pNode;
				pNode->m_pPrev = pCurr;
				// Make sure trailing value is NULL
				// (This will prevent bugs)
				pNode->m_pNext = NULL;
			}
		}

		void _Add(T* pData) {
			Node<T>* pNode = new Node<T>();
			if(pNode == NULL) return;

			pNode->m_pData = pData;
			this->_Add(pNode);
		}

		void _DeleteAll() {
			Node<T>* pCurr = this->m_pRoot;
			this->m_pRoot = NULL;

			while(pCurr != NULL) {
				Node<T>* pNext = pCurr->m_pNext;
				delete pCurr->m_pData;
				delete pCurr;
				pCurr = pNext;
			}
		}

		void _Remove(Node<T>* pNode) {
			// Validate parameters
			if(pNode == NULL) return;
			// Start at the beginning of the list...
			Node<T>* pCurr = this->m_pRoot;
			// Navigate until pNode is found or until NULL...
			while(pCurr != pNode && pCurr != NULL) {
				pCurr = pCurr->m_pNext;
			}
			// If we found it...
			if(pCurr == pNode) {
				// Bind up the previous node to this node's next
				if(pCurr->m_pPrev != NULL) {
					pCurr->m_pPrev->m_pNext = pCurr->m_pNext;
				}
				// Bind up the next node to this node's previous
				if(pCurr->m_pNext != NULL) {
					pCurr->m_pNext->m_pPrev = pCurr->m_pPrev;
				}
				// The node has been removed.
			}
		}

		void _Remove(T* pData) {
			// Validate parameters
			if(pData == NULL) return;
			// Start at the beginning of the list...
			Node<T>* pCurr = this->m_pRoot;
			// Navigate until pNode is found or until NULL...
			while(pCurr != NULL && pCurr->m_pData != pData) {
				pCurr = pCurr->m_pNext;
			}
			// If we found it...
			if(pCurr != NULL && pCurr->m_pData == pData) {
				// Bind up the previous node to this node's next
				if(pCurr->m_pPrev != NULL) {
					pCurr->m_pPrev->m_pNext = pCurr->m_pNext;
				}
				// Bind up the next node to this node's previous
				if(pCurr->m_pNext != NULL) {
					pCurr->m_pNext->m_pPrev = pCurr->m_pPrev;
				}
				// The node has been removed.
			}
		}
	};

}

#endif
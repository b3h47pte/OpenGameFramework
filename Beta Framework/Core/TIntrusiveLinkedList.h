#pragma once
#ifndef _TINTRUSIVELINKEDLIST_H
#define _TINTRUSIVELINKEDLIST_H

#include "TIntrusiveLink.h"
/*
 * Instrusive Linked Lists provide the flexibility to delete an element just by knowing the pointer to the object instead of having to search the 
 * entire linked list for that element. Greatly inspired by and modeled after: http://www.codeofhonor.com/blog/avoiding-game-crashes-related-to-linked-lists
 * NOT THREAD SAFE. (At least I'm pretty sure it's not).
 */
template<typename T, size_t inOffset>
class TIntrusiveLinkedList
{
public:
	TIntrusiveLinkedList(void): mOffset(inOffset) {
	}

	~TIntrusiveLinkedList(void) {
	}

	/*
	 * Get Head and Tail pointers (for iteration).
	 */ 
	TIntrusiveLink<T>* GetHead() { 
		return mLink.mPrev;
	}

	TIntrusiveLink<T>* GetTail() {
		return mLink.mNext;
	}

	/* 
	 * Get and Tail elements (for iteration)
	 */
	T* GetHeadElement() {
		return ((mLink.mPrev != NULL) ? mLink.mPrev->mObject : NULL);
	}

	T* GetTailElement() {
		return ((mLink.mNext != NULL) ? mLink.mNext->mObject : NULL);
	}

	/* 
	 * Add to linked list at the tail.
	 */
	void AppendElement(T* newEle) {
		TIntrusiveLink<T>* newLink = GetLinkFromElement(newEle);
		mLink.AddPrevious(newLink, newEle);
	}

	/*
	 * Get the Link element from the input element which definitely has a link element
	 */
	TIntrusiveLink<T>* GetLinkFromElement(T* newEle) {
		return (TIntrusiveLink<T>*)((size_t)(newEle + mOffset));
	}

	/*
	 * Get Next/Previous Link OR Get Next/Previous Element
	 * Note that if next/previous happens to link back to mLink then we should ignore that! Never pass mLink to anyone
	 */ 
	TIntrusiveLink<T>* GetPreviousLink(TIntrusiveLink<T>* inLink) {
		if (inLink->mPrev == &mLink) 
			return NULL;

		return inLink->mPrev;
	}

	TIntrusiveLink<T>* GetNextLink(TIntrusiveLink<T>* inLink) {
		if (inLink->mNext == &mLink) 
			return NULL;

		return inLink->mNext;
	}

	T* GetPreviousElement(T* inObj) {
		TIntrusiveLink<T>* inLink = GetLinkFromElement(inObj);
		TIntrusiveLink<T>* relLink = GetPreviousLink(inLink);
		if (relLink) 
			return relLink->mObject;
		return NULL;
	}


	T* GetNextElement(T* inObj) {
		TIntrusiveLink<T>* inLink = GetLinkFromElement(inObj);
		TIntrusiveLink<T>* relLink = GetNextLink(inLink);
		if (relLink) 
			return relLink->mObject;
		return NULL;
	}

private:
	// Link to the head
	TIntrusiveLink<T> mLink;
	size_t mOffset;
};

#endif // _TIntrusiveLinkEDLIST_H

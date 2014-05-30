#pragma once
#ifndef _TINTRUSIVELINK_H
#define _TINTRUSIVELINK_H

template<typename T>
class TIntrusiveLink
{
public:
  TIntrusiveLink(void): mPrev(this), mNext(this),
    mObject(NULL) {
  }

  ~TIntrusiveLink(void) {
  }

  /* 
   * Unlink from the list.
   */ 
  void Unlink() {
    if (mPrev)
      mPrev->mNext = mNext;

    if (mNext)
      mNext->mPrev = mPrev;

    mObject = NULL;
  }

  /* 
   * Set Object since the instrusive link must get its object set either when its added to the list. 
   */
  void SetObject(T* inObj) {
    mObject = inObj;
  }

  /*
   * Link to Previous.
   */
  void AddPrevious(TIntrusiveLink<T>* newEle, T* newObj) {
    // New Node:
    //  Next: This node
    //  Previous: Previous node
    newEle->mNext = this;
    newEle->mPrev = mPrev;
    newEle->mObject = newObj;  

    // Old Previous Node:
    //  Next: New node
    //  Previous: Unchanged
    mPrev->mNext = newEle;

    // This Node:
    //  Next: Unchanged
    //  Previous: New node.
    mPrev = newEle;
  }

  /*
   * Link to Next.
   */ 
  void AddNext(TIntrusiveLink<T>* newEle, T* newObj) {
    // New Node:
    //  Next: Next node
    //  Previous: This node
    newEle->mPrev = this;
    newEle->mNext = mNext;
    newEle->mObject = newObj;

    // Old Next Node:
    //  Next: Unchanged
    //  Previous: New node
    mNext->mPrev = newEle;

    // This Node:
    //  Next: New node.
    //  Previous: Unchanged
    mNext = newEle;
  }

  template<typename T1, size_t inOffset> friend class TIntrusiveLinkedList;
private:
  TIntrusiveLink<T>* mPrev;
  TIntrusiveLink<T>* mNext;

  T* mObject;

};


#endif // _TIntrusiveLink_H

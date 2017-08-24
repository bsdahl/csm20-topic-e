//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Array-based implementation of the ADT heap.
 @file ArrayMaxHeap.cpp */

 
#include "ArrayMaxHeap.h"
#include "PrecondViolatedExcep.h"
#include <algorithm>
#include <cmath>

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}  // end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
    return (2 * nodeIndex) + 2;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
    return (nodeIndex - 1) / 2;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(int nodeIndex) const
{
    if (!(getLeftChildIndex(nodeIndex) < itemCount) && !(getRightChildIndex(nodeIndex) < itemCount))
        return true;
    else
        return false;
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int subTreeRootIndex)
{
    //page 509
    if (!isLeaf(subTreeRootIndex))
    {
        // The root must have a left child; assume it is the larger child.
        int largerChildIndex = 2 * subTreeRootIndex + 1; // Left child index
        
        if (getRightChildIndex(subTreeRootIndex) != 0)
        {
            int rightChildIndex = largerChildIndex + 1; // Right child index
            if (items[rightChildIndex] > items[largerChildIndex])
                largerChildIndex = rightChildIndex; // Larger child index
        }
        
        // If the item in the root is smaller than the item in the larger child, swap items
        if (items[subTreeRootIndex] <= items[largerChildIndex])
        {
            swap(items[subTreeRootIndex], items[largerChildIndex]);
            //Transform the semiheap rooted at largerChildIndex into a heap
            heapRebuild(largerChildIndex);
        }
    } // Else root is a leaf, so you are done
}  // end heapRebuild

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate() 
{
   for (int index = itemCount / 2; index >= 0; index--)
   {
      heapRebuild(index);  
   }  // end for
}  // end heapCreate

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
    items = new ItemType[maxItems];
}

template<class ItemType>
ArrayMaxHeap<ItemType>::
ArrayMaxHeap(const ItemType someArray[], const int arraySize):
             itemCount(arraySize), maxItems(2 * arraySize)
{
   // Allocate the array
   items = new ItemType[2 * arraySize];
   
   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   
   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
    delete[] items;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
    if (itemCount == 0)
        return true;
    else
        return false;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
    return itemCount + 1;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
    return ceil(log2(itemCount + 1));
}

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw(PrecondViolatedExcep)
{
   if (isEmpty())
      throw PrecondViolatedExcep("Attempted peek into an empty heap.");
   
   return items[0];
} // end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData)
{
    //page 511

    if (itemCount == maxItems)
        return false;
    
    // Insert newData into the bottom of the tree
    items[itemCount] = newData;
    
    // Trickle new item up to the appropriate spot in the tree
    int newDataIndex = itemCount;
    bool inPlace = false;
    
    // Repeat the process as long as newDataIndex is greater than zero
    // and inPlace is false
    while (newDataIndex > 0 && !inPlace)
    {
        // Get the parent node's index
        int parentIndex = (newDataIndex - 1) / 2;
        
        // Item is in place if the priority value of the newData is
        // lesser or equal than the parent node's value
        if (items[newDataIndex] <= items[parentIndex])
            inPlace = true;
        else
        {
            // Otherwise, swap newDataIndex's value with the parentIndex
            swap(items[newDataIndex], items[parentIndex]);
            // set newDataIndex to the parentIndex to repeat the process
            newDataIndex = parentIndex;
        }
    }
    
    // Increase the itemCount
    itemCount++;
    
    // The process is done, returns true.
    return true;
}  // end add

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
    if (isEmpty())
        return false;
    
    //page 508
    // Copy the item from the last node into the root
    items[0] = items[itemCount - 1];
    
    // Remove the last node
    itemCount--;
    
    // Transform the semiheap back into the heap
    heapRebuild(0);

    return true;
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
    itemCount = 0;
}
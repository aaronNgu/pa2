/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template <class T>
void Queue<T>::enqueue(T const& newItem)
{
    /**
     * @todo Your code here!
     */
 
    inStack.add(newItem);
    
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::dequeue()
{
    /**
     * @todo Your code here! 
     */

         while(!inStack.isEmpty()){
             outStack.add(inStack.remove());
        }               
        return outStack.remove();
      
}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Queue<T>::add(const T& theItem)
{
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to add the element to the Queue.
     */
 
    enqueue(theItem);
    
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Queue<T>::remove()
{
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to remove an element from the Queue and return it. 
     */
   
     return dequeue();
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template <class T>
T Queue<T>::peek()
{
    /**
     * @todo Your code here! 
     */
    // printf("in peek()");
    //  while(!inStack.isEmpty()){
    //         printf("in peek2");
    //         outStack.push(inStack.pop());
    //     }
    // T front = outStack.peek();
    // while(!outStack.isEmpty()){
    //         printf("in peek3");
    //         inStack.push(outStack.pop());
    //     }
    // return front;

     if(outStack.isEmpty()){
         while(!inStack.isEmpty()){
             outStack.add(inStack.remove());
         }
         return  outStack.peek();
         
    }

}

/**
 * Determines if the Queue is empty.
 * 
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template <class T>
bool Queue<T>::isEmpty() const
{
    /**
     * @todo Your code here! 
    //  */

    return inStack.isEmpty() && outStack.isEmpty();
}

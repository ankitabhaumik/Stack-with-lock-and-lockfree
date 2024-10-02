#include "my_stack.h"
//Stack with producer consumer

class my_stack_prod_cons
{
   Node *head;
   //mutex mtx;
   //condition_variable cv;
   int size;

   public:
   my_stack_prod_cons()
   {
      size=0;
   }
   
   void push(int val)
   { 
    //   unique_lock<mutex> ul(mtx);
    //   cv.wait(ul,[this]
    //              {return getsize() < MAX_SIZE; });
      Node* temp = new Node(val);
      if(isempty())
      {
         head=temp;
         size++;
         return;
      }
      
      temp->next = head;
      head=temp;
      size++;
   }

   void pop()
   {
    //   unique_lock<mutex> ul(mtx);
    //   cv.wait(ul, [this]
    //               {return !isempty(); });
      if(isempty())
      {
          cout<<"Stack is empty"<<endl;
          return;
      }

     Node * temp = head;
     head = head->next;
     delete temp;
     size--;

   }

   int top()
   {
     //unique_lock<mutex> ul(mtx);
     if(head!=nullptr){
        return head->value;
     }
     else 
        return -1;
   }

   bool isempty()
   {
       //unique_lock<mutex> ul(mtx);
        if(head == NULL)
            return true;
        else
            return false;

   }

   int getsize()
   {
      return size;
   }

};

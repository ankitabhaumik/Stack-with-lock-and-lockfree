#include "my_stack.h"

class my_stack
{
   Node *head;
   shared_mutex mtx;

   public:
   
   void push(int val)
   { 
     unique_lock<shared_mutex> ul(mtx);
      Node* temp = new Node(val);
      if(isempty())
      {
         head=temp;
         return;
      }
      
      temp->next = head;
      head=temp;
   }

   void pop()
   {
      unique_lock<shared_mutex> ul(mtx);
      if(isempty())
      {
          cout<<"Stack is empty"<<endl;
          return;
      }

     Node * temp = head;
     head = head->next;
     delete temp;


   }

   int top()
   {
     shared_lock<shared_mutex> ul(mtx);
     if(head!=nullptr){
        return head->value;
     }
     else 
        return -1;
   }

   int isempty()
   {
       // shared_lock<shared_mutex> ul(mtx);
        return (head == NULL);
   }

};
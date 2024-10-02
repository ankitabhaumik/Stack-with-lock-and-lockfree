#include "stack_uniq_shared.cpp"
#include "stack_pr_con.cpp"

mutex mtx;
condition_variable cv;

void callpush_prod_cons(my_stack_prod_cons &t)
{
    for(int i=1;i<=MAX_SIZE;i++)
    {
        unique_lock<mutex> ul(mtx);
         cv.wait(ul,[&t]
                 {return t.getsize() < MAX_SIZE; });
        cout<<"Push i = "<<i<<" is called"<<endl;
        t.push(i);
    }
}

void callpop_prod_cons(my_stack_prod_cons &t)
{
    for(int i=1;i<=MAX_SIZE;i++)
    {
       unique_lock<mutex> ul(mtx);
       cv.wait(ul, [&t]
                  {return !t.isempty(); });
        cout<<"Pop i = "<<i<<" is called"<<endl;

        if(i==7)
           cout<<"Top value is : "<<t.top()<<endl;         
 
        t.pop();

    }
}



void callpush(my_stack &t)
{
    for(int i=1;i<=MAX_SIZE;i++)
    {
        cout<<"Push i = "<<i<<" is called"<<endl;
        t.push(i);
    }
}

void callpop(my_stack &t)
{
    for(int i=1;i<=MAX_SIZE;i++)
    {
        cout<<"Pop i = "<<i<<" is called"<<endl;
        t.pop();

    }
}


int main()
{
//   my_stack s;
//   thread t1(callpush, ref(s));
//   thread t2(callpop, ref(s));

//   t1.join();
//   t2.join();

  my_stack_prod_cons s1;
  thread t3(callpush_prod_cons, ref(s1));
  thread t4(callpop_prod_cons, ref(s1));

  t3.join();
  t4.join();

}



//Push and pop are mainly consumer producer problem . cz both are modufying it 
//As push and pop both are modifying so deending on the condition variable we will push it and pop it
//And pop and top is more of a reader writer problem cz in pop we are modifying it but here in top we are just reading it .
//so in the pop we can use unique lock and in the top we can use shared lock
//Every where we cant use lock everywhere only the lines which are needed otherwise it will degrde the performance


// What s unique lock and shared lock??
// In unique lock it is exclusive lock once we put unique lock no other threads and come and read it and modigy it also 
// in shared lock if one thread is reading then other thread can also come and access/ read it .

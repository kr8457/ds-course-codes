#include<iostream>
using namespace std;

class Node{
    private:
    int element;
    Node* next_Node;
    public:
    Node(int e,Node* n ):element(e),next_Node(n){};


    void setelement(int e)
    {
        element = e;
    }
    void setnext(Node *n)
    {
        next_Node=n;
    }
    int retrieve()const
    {
        return element;
    }
    Node* next()const{
        return next_Node;
    }
};

class S_list{
    private:
    Node* list_Head;
    public:
    S_list():list_Head(nullptr){};
      
    bool empty() const;
        Node *head() const;
        int front() const;
        void display() const;
        int size() const;
        int count(int) const;
        int end() const;
        
        
        void push_front(int);
        int pop_front();
        void push_end(int);
        void pop_end();
        int erase(int);

    ~S_list() {
         while (!empty())
              pop_front();
        }


    };


int S_list::erase(int n)
{
    if (empty()) 
        throw "Underflow";

    Node* ptr = list_Head;
    Node* prev = nullptr;
    int count = 0;

    while (ptr != nullptr)
    {
        if (ptr->retrieve() == n)
        {
            // delete head node
            if (prev == nullptr)
            {
                list_Head = ptr->next();
                delete ptr;
                ptr = list_Head;
            }
            else
            {
                prev->setnext(ptr->next());
                delete ptr;
                ptr = prev->next();
            }
            count++;
        }
        else
        {
            prev = ptr;
            ptr = ptr->next();
        }
    }

    return count;
}

  

void S_list::pop_end(){
   if (empty()) throw "Underflow";

    if (list_Head->next() == nullptr) {
        delete list_Head;
        list_Head = nullptr;
        return;
    }

    Node* temp = list_Head;
    while (temp->next()->next() != nullptr)
        temp = temp->next();

    delete temp->next();
    temp->setnext(nullptr);
}

    

int S_list::pop_front(){
    if (empty())
        throw "Underflow";
    Node* temp = list_Head;
    int val = temp->retrieve();
    list_Head = temp->next();
    delete temp;
    return val;

}   

int S_list:: end() const
    {
      Node* temp = list_Head;   // make a traversal pointer
    while (temp->next() != nullptr) { // loop until end of list
       
        temp = temp->next();    // move to next node
    }
     return temp->retrieve();
    };   
int S_list::size() const
 {  
    int count =0;
    Node* temp = list_Head;   // make a traversal pointer
    while (temp != nullptr) { // loop until end of list
        count += 1;
        temp = temp->next();    // move to next node
    }
    return count;
 }    
int S_list::count(int n) const
 {  
    int count =0;
    Node* temp = list_Head;   // make a traversal pointer
    while (temp != nullptr) { // loop until end of list
        if(temp->retrieve()==n)
            {
                count += 1;
            }   
        temp = temp->next();    // move to next node
    }
    return count;
 }    
bool S_list:: empty()const
    {

    return list_Head==nullptr;
    }

    Node* S_list::head()const{
        return list_Head;
    }

int S_list::front()const
    {
   if(empty())
    {
        throw "Under flow";
    }
    else;
    return list_Head->retrieve();
    }    
void S_list::push_front(int n)
    {
       list_Head=  new Node(n,head());
    }

void S_list::push_end(int n)
{
    if(empty())
    {
      push_front(n);
    }
    else
    {
         Node* temp = list_Head;   // make a traversal pointer
    while (temp->next()!= nullptr) 
        { // loop until end of list
        
         temp = temp->next();    // move to next node
        }
        temp->setnext(new Node(n,nullptr));
    }
}

void S_list::display() const 
    {
    Node* temp = list_Head;   // make a traversal pointer
    while (temp != nullptr) { // loop until end of list
        cout << " " << temp->retrieve();
        temp = temp->next();    // move to next node
    }
    cout << endl;
    }



int main()
    {

    S_list l;
    l.push_end(12);
    l.push_front(1);
     l.push_front(12);
    l.push_front(12);
     l.push_front(12);
    l.push_front(12);
     l.display();
    cout<<"size is:"<<l.size()<<endl;
    cout<<"count of n is:"<<l.count(0)<<endl;
    cout<<"front is :"<<l.front()<<endl;
    cout<<"end is:"<<l.end()<<endl;
   // l.pop_front();
    //l.pop_end();
    cout<<l.erase(12)<<endl;
   cout<<"at the end "<< endl;
    l.display();
    return 0;
    }
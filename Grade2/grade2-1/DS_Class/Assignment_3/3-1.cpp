#include <iostream>
using namespace std;
enum Boolean { FALSE, TRUE};
template <class Type> class List;
template <class Type> class ListIterator;

template <class Type>
class ListNode
{
friend class List<Type>;
friend class ListIterator<Type>;
public:
    ListNode(Type element){
        data = element;
        link = 0;
    }
private:
    Type data;
    ListNode *link;
};

template <class Type>
class List
{
friend class ListIterator<Type>;
public:
    List(){
        first = 0;
    }
    void Insert(Type k){
        ListNode<Type> *newnode = new ListNode<Type>(k);
        newnode->link = first;
        first = newnode;
    }
    void Delete(Type k){
        ListNode<Type> *previous = 0;
        ListNode<Type> *current = first;
        while(current && current->data != k){
            previous = current;
            current = current->link;
        }
        if (current){
            if (previous) previous->link = current->link;
            else first = first->link;
            delete current;
    }
    }
    void Invert(){
        // A chain x is inverted so that if x = (a0, a1, ..., an),
        // then, after execution, x = (an, ..., a1)
        ListNode<Type> *p = first, *q = 0; // q trails p
        while (p) {
            ListNode<Type> *r = q; q = p; // r trails q
            p = p->link; // p moves to next node
            q->link = r; // link q to preceding node
        }
        first = q;
    }
    void Concatenate(List<Type> b){
        if (! first) {
            first = b.first;
            return;
        }
        ListNode<Type> *p = first;
        if (b.first) {
            while(p->link){
                p = p->link;
            }
            p->link = b.first;
        }
    }
    //Here is the funtion
    int length(){
        if(!first){return 0;}
        else{
            int count = 0;
            ListNode<Type> *cur = first;
            while(cur){
                cur = cur->link;
                count++;
            }
            return count;
        }
    }
    Type atNth(int n){
        int len = length(), d;
        ListNode<Type> *cur = first;
        if(n==1) return cur->data;
        if(n>0 && n<=len){
            while(--n){
                cur = cur->link;
                d = cur->data;
            }
            return d;
        }
        else{
            return NULL;
        }
    }
    void shift(char ch, int n){
        ListNode<Type> *cur = first;
        int len = length();
        Type arr[len];
        for(int i=0;i<len;i++){
            arr[i] = cur->data;
            cur = cur->link;
        }
        if(ch=='R'){
            for(int i=0;i<len;i++){
                int pos = (i+1)-n;
                if(pos<=0) pos = pos + len;
                Type temp = atNth(pos);
                ListNode<Type> *q = first, *p = first;
                while(--pos){
                    q = q->link;
                }
                q->data = arr[i]; //cur
                while(1){
                    if(p->data == arr[i]) break;
                    p = p->link;
                }
                p->data = temp;
            }
        }
        if(ch=='L'){
            for(int i=0;i<len;i++){
                int pos = (i+1)+n;
                if(pos>len) pos = pos - len;
                Type temp = atNth(pos);
                ListNode<Type> *q = first, *p = first;
                while(--pos){
                    q = q->link;
                }
                q->data = arr[i]; //cur
                while(1){
                    if(p->data == arr[i]) break;
                    p = p->link;
                }
                p->data = temp;
            }
        }
        
    }
    void print(){
        ListNode<Type> *cur = first;
        while(cur!=NULL){
            cout<<cur->data<<" ";
            cur = cur->link;
        }
        cout<<endl;
    }
    Boolean symmetric(){
        ListNode<Type> *cur = first;
        int len = length();
        Type arr[len];
        for(int i=0;i<len;i++){
            arr[i] = cur->data;
            cur = cur->link;
        }
        int same = 0;
        for(int i=0;i<len/2;i++){
            if(arr[i]==arr[len-1-i]){
                same++;
            }
        }
        if(same==(len/2)) return TRUE;
        else return FALSE;
    }
    void deleteAll(int n, Type d){
        ListNode<Type> *cur = first;
        while(cur!=NULL){
            if(n==0) break;
            if(cur->data==d){
                cur = cur->link;
                Delete(d);
                n--;
            }
            else cur = cur->link;
        }
    }
private:
    ListNode<Type> *first;
};

template <class Type>
class ListIterator {
public:
    ListIterator(const List<Type>& l): list(l), current (l.first) {};
    Boolean NotNull(){
        if (current) return TRUE;
        else return FALSE;
    }
    Boolean NextNotNull(){// check that the next element in list is non-null
        if (current && current->link) return TRUE;
        else return FALSE;
    }
    Type* First(){// return a pointer to the first element of list
        if (list.first) return &list.first->data;
        else return 0;
    }
    Type* Next(){// return a pointer to the next element of list
        if (current) {
            current = current->link;
            return &current->data;
        }
        else return 0;
    }
private:
    const List<Type> &list;  // refers to an existing list
    ListNode<Type>* current; // points to a node in list
};

int sum(const List<int>& l)
{
  ListIterator<int> li(l);  //li is associated with list l
  if (!li.NotNull()) return 0; // empty list, return 0
  int retvalue = *li.First(); // get first element
  while (li.NextNotNull())  // make sure that next element exists
     retvalue += *li.Next(); // get it, add it to current total
return retvalue;
}

//template <class Type>
ostream& operator<<(ostream& os, List<char>& l)
{
    ListIterator<char> li(l);
    if (!li.NotNull()) return os;
    os << *li.First() << endl;
    while  (li.NextNotNull())
	 os << *li.Next() << endl;
    return os;
}

main()
{
   List<int> intlist;
    intlist.Insert(5);//4
    intlist.Insert(15);//3
    intlist.Insert(25);//2
    intlist.Insert(35);//1
    intlist.Insert(5);
    cout << sum(intlist) << endl;
    cout << "Length:" << intlist.length() << endl;
    cout << "atNth:" << intlist.atNth(5) << endl;
    //intlist.shift('R', 3);
    //cout<<"Shift right,3:";
    intlist.print();
    if(intlist.symmetric()) cout<<"Symmetric"<<endl;
    else cout<<"Not symmetric"<<endl;
    intlist.deleteAll(2, 5);
    intlist.print();
    intlist.Delete(20);
    intlist.Delete(15);
    intlist.Delete(35);
    cout << sum(intlist) << endl;

  List<char> charlist;
    cout << "shd be empty: " << charlist << endl;
    charlist.Invert();
    cout << "shd be empty: " << charlist << endl;
    charlist.Insert('d');
    charlist.Invert();
    cout << "shd have d : " << charlist << endl;
    charlist.Insert('c');
    charlist.Insert('b');
    charlist.Insert('a');
    cout << "shd have abcd: "<<endl;
    cout << charlist << endl;
    charlist.Invert();
    cout << "shd invert prev list"<<endl;
    cout << charlist << endl;

    List<char> char2list;
    charlist.Concatenate(char2list);
    cout << charlist << endl;
    char2list.Insert('e');
    char2list.Insert('f');
    char2list.Concatenate(charlist);
    charlist.Delete('e');
    charlist.Delete('c');
    cout << char2list << endl;
    char2list.Invert();
    cout << char2list << endl;
    cout << "Length:" << char2list.length() << endl;
    cout << "atNth:" << char2list.atNth(2) << endl;
    char2list.shift('L',2);
    cout<<"Shift left, 2: ";
    char2list.print();
    if(char2list.symmetric()) cout<<"Symmetric"<<endl;
    else cout<<"Not symmetric"<<endl;
}

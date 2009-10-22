//-------------------------

/* Example:

   data List t1 = Nil | Cons t1 (List t1);

   ----------------
   
   int main() {
       int x = 1;
       List<int> empty(Nil);
       List<int> one(Cons, &x, &empty);
   }
*/

// Above definition will be transformed to:
//-----------------------------------------

enum Dummy_List_Nil {} Nil;
enum Dummy_List_Cons {} Cons;

template <typename T1> class List;

template <typename T1> struct List_Nil {};
template <typename T1> struct List_Cons {
    T1 *t1;
    List<T1> *t2;
};


template <typename T1> class List {
    enum List_Sum {
        List_Sum_INVALID,
        List_Sum_Nil,
        List_Sum_Cons,
    };
    union List_Data {
        List_Nil<T1> Nil;
        List_Cons<T1> Cons;
    };

    union List_Data m_data;
    enum List_Sum m_constructor;
    
    List() {
        m_constructor = List_Sum_INVALID;
    };
    
public:    
    List(enum Dummy_List_Nil dummy) {
        m_constructor = List_Sum_Nil;
    };
    List(enum Dummy_List_Cons dummy, T1 *t1, List<T1> *t2) {
        m_constructor = List_Sum_Cons;
        m_data.Cons.t1 = t1;
        m_data.Cons.t2 = t2;
    };
};



#include <stdio.h>

int main() {
    int x = 1;
    
    List<int> empty(Nil);
    List<int> one(Cons, &x, &empty);
    
}

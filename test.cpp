//-------------------------

/* Example:

   data MyT t1 t2 = Cons1 t1 | Cons2 t1 t2;

   int main() {
       MyT<int, int> my_t(Cons1, 3);
       printf("Hi.\n");
   }
*/

// will be transformed to:
//-------------------------

enum MyT_Sum {
    T_INVALID,
    T_CONS1,
    T_CONS2,
};

enum Dummy_T_Cons1 {} _Cons1;
enum Dummy_T_Cons2 {} _Cons2;

template <typename T1, typename T2> class MyT {
    struct MyT_Cons1 {
        T1 t1;
    };
    struct MyT_Cons2 {
        T1 t1;
        T2 t2;
    };
    union MyT_Data {
        struct MyT_Cons1 Cons1;
        struct MyT_Cons2 Cons2;
    };

    union MyT_Data m_data;
    enum MyT_Sum m_constructor;
    
    MyT() {
        m_constructor = T_INVALID;
    };
    
public:    
    MyT(enum Dummy_T_Cons1 dummy, T1 t1) {
        m_constructor = T_CONS1;
        m_data.Cons1.t1 = t1;
    };
    MyT(enum Dummy_T_Cons2 dummy,T1 t1, T1 t2) {
        m_constructor = T_CONS2;
        m_data.Cons2.t1 = t1;
        m_data.Cons2.t2 = t2;
    };
};



#include <stdio.h>

int main() {
    MyT<int, int> my_t(Cons1, 3);
    printf("Hi.\n");
}

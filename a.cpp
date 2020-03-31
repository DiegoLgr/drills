#include <iostream>


struct A {
    //virtual void f( void) = 0;
};

struct C: public A {
    C( std::string s): s(s) {}
    const std::string s;

    //void f( void){}
};

struct B: public A {
    B( const A& a): a(a) {}
    const A& a;

    //void f( void){}
};
B f(){
    const C c {"hii"};
    const B b { c };
    return b;
}
int main( void){
    const C c = C {"hii"};
    std::string s{ "basuraaaa" };
    B bb = f();
    const B b { c };

    // A virtual function is needed here for dynamic_cast,
    // otherwise it trows a compile error: A is not polymorphic.
    // It can be a static cast tho.
    const C* cc = static_cast <const C*>(&b.a);
    std::cout << cc->s << std::endl;
    return 0;
}

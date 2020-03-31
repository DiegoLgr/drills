#include<iostream>

class Object {
    public:
        Object( int i, int j) : i{i}, j{j} {};
        //Object( Object o) : i{o.i}, j{o.j} {}; Compilation error.
        Object( const Object& o) : i{o.i}, j{o.j} {};
        Object( const Object* o) : i{o->i}, j{o->j} {std::cout << "toma\n";};
        Object( Object&& o) : i{o.i}, j{o.j} {
            o.reset();
        };

        void reset( void){ i=0; j=0; };
        void print( void) const { std::cout << i << ", " << j << std::endl; };
        void inc( void) { i++; j++; };
        void is_valid( void) const {std::cout << "** " << (i>0 && j>0 ? "valid" : "nop") << std::endl;} ;

    private:
        int i;
        int j;
};


void copy( void){
    Object a{ 1, 1 };

    std::cout << "Obj to Obj:" << std::endl;
    Object b{ a };
    a.is_valid();
    a.inc();
    b.print();

    std::cout << "Obj to pointer:" << std::endl;
    Object* po1{ &b } ;
    b.is_valid();
    b.inc();
    po1->print();

    // Curioso, que funcione c para un Obj y *c para un Obj*.
    std::cout << "Pointer to pointer:" << std::endl;
    Object* po2{ po1 };
    po1->is_valid();
    po1->inc();
    po2->print();

    std::cout << "Pointer to Obj:" << std::endl;
    Object c{ *po2 };
    po2->is_valid();
    po2->inc();
    c.print();

    std::cout << "Ref to pointer:" << std::endl;
    Object* po3{ &c };
    c.is_valid();
    c.inc();
    po3->print();

    // Here we get "toma".
    std::cout << "Ref to pointer:" << std::endl;
    Object d{ 1, 1};
    Object e{ &d };
    d.is_valid();
    d.inc();
    e.print();

    std::cout << "End" << std::endl;
}

void move( void){
    Object a{ 1, 1 };

    // This moves.
    std::cout << "Obj to Obj:" << std::endl;
    Object b{ std::move( a) };
    a.is_valid();
    a.inc();
    b.print();

    // This does moves.
    std::cout << "Pointer to Obj:" << std::endl;
    Object e{ 1, 1};
    Object* po1 = &e;
    Object c{ std::move( *po1) };
    po1->is_valid();
    po1->inc();
    c.print();

    // This does not move.
    // I think we are not building an Object here but a regular pointer ¬¬
    // And this says: erro: blah blah in scalar initializer... :)
    // Object* po1{ 1, 1};
    std::cout << "Obj to pointer:" << std::endl;
    Object* po2{ std::move( &b) } ;
    b.is_valid();
    b.inc();
    po2->print();


    std::cout << "End" << std::endl;
}



int main(){
    move();
    return 0;
}

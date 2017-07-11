#ifndef ADAPTOR_H
#define ADAPTOR_H



template<class Ds>
class Cadaptor{
public:
    typedef typename Ds::value_type Tipo;
    Ds  estruct;

    bool insertar(Tipo x){
        return estruct.insertar(x);
    }
    bool eliminar(Tipo x){
        return estruct.eliminar(x);
    }
    bool buscar(Tipo x){
        return estruct.found(x);
    }
    void imprimir(){
        estruct.print_();
    }
};

#endif // ADAPTOR_H

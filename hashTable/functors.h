#ifndef FUNCTORS_H
#define FUNCTORS_H

template<typename T>
struct cFxA{
    int operator()(T n,int size){
        return n % size;
        cout<<n<<","<<size<<"\n";
    }

};

template<typename T>
class cFxB{
public:
    int operator()(T n,int size){
        return (n*7) % size;
        //cout<<n<<","<<size<<"\n";
    }

};

#endif // FUNCTORS_H

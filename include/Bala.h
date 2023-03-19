#ifndef BALA_H
#define BALA_H


class Bala{
public:
    //atributos

    int x;
    int y;
    BITMAP* sprite;
    //metodos
    int ejeXbala(){return x;}
    int ejeYbala(){return y;}
    void movBala(BITMAP* pantalla);
    Bala(int x, int y); //costructor

    ~Bala();//destructor
};

 //lista de objetos tipo balas

 Bala::Bala(int x, int y){ //Const
this->x=x;
this->y=y;
this->sprite= load_bitmap("miBala.bmp",NULL);
}
void Bala::movBala(BITMAP* pantalla){
    if(y>0){
        y--;
    }

    draw_sprite(pantalla,sprite,x,y);
}

Bala::~Bala(){
//balas.remove(this);
}


#endif // BALA_H

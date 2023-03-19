#include<list>
using namespace std;

//funcion=======================================================
static bool marcaTiempo(int seg){
    static int cont=0;
     if(seg==0){
        return false;
    }
    if (cont>=seg){
        cont=0;
        return true;
    }
   cont++;
    return false;
}
//**************************************************************
class Retraso{
     public:
        int cont;
        Retraso();
        bool alarma(int seg);
};
Retraso::Retraso(){
    this->cont=0;
}
bool Retraso::alarma(int seg){

if(seg==0)
    {
    return false;
    }
    if(cont>=seg)
    {
        cont=0;
        return true;
    }
    cont++;
    return false;
}
//****************************************************************************
class Bala{
    public:
    int x;
    int y;
    int tipoBala; //Enemigo o Nave
    BITMAP* sprite;
    BITMAP* balaMala;
    SAMPLE* sonidoChoque;
     //contructor
     Bala(int x, int y, int tipo);
     //metodos
     void pintar_bala(BITMAP *pantalla);
     void disparo(BITMAP *pantalla);
     bool destructorBala();
     ~Bala();
};
list<Bala*>misBalas;
list<Bala*>::iterator itBala;

Bala::Bala(int x, int y, int tipo)
{
    this->x=x;
    this->y=y;
    this->tipoBala= tipo;
    this->sprite=load_bitmap("bala2.bmp", NULL);
    this->balaMala=load_bitmap("bomba2.bmp",NULL);
    this->sonidoChoque=load_wav("Impacto.wav");

}
void Bala::pintar_bala(BITMAP *pantalla) {
    if(tipoBala==0){//es de  Nave
    masked_blit( sprite, pantalla, 0, 0, x, y, 3, 11);
    }
    else {
        if(tipoBala==1){
            masked_blit( balaMala, pantalla, 0, 0, x, y, 12, 16);
        }
    }
}

void Bala::disparo(BITMAP *pantalla){
if(tipoBala==0){
    if (y>10){
    y-=7;
}
else
{
this->~Bala();
}
pintar_bala(pantalla);
}
else{
    if(tipoBala==1){
        if (y<500){
        y+=7;
        }
        else
        {
        this->~Bala();
        }
        pintar_bala(pantalla);
        }
}

}
Bala::~Bala()//destructor
{
    misBalas.remove(this);
}
bool Bala::destructorBala(){
     if(this->x >SCREEN_W || this->y >SCREEN_H )
    {
        return true;
    }else{
        return false;
    }
}

//********************************************************************

class Nave{
    //atributos
    public:
    int x;
    int y;
    float energia;
    int puntaje;
    int tipoNave;
    BITMAP* vidaNave;
    BITMAP* sprite;
    BITMAP* sprite2;
    BITMAP* sprite3;
    SAMPLE* sonidoBala;
    //metodos
    Nave(int tipo);
    void mov(BITMAP *pantalla);
    int naveX(){return x;}
    int naveY(){return y;}
    void CantEnergia(int cantidad, BITMAP *pantalla);
    void refrascarEnergia(BITMAP *pantalla);
};
Nave::Nave(int tipo){//constructor()
    tipoNave=tipo;
    x=400;
    y=400;
    puntaje=0;
    energia=248;
    vidaNave=load_bitmap("corazones.bmp",NULL);
    sprite=load_bitmap("navenegra.bmp",NULL);
    sprite2=load_bitmap("navenegra2.bmp",NULL);
    sprite3=load_bitmap("navenegra3.bmp",NULL);
    sonidoBala=load_wav("balaLazer1.wav");



}
void Nave::mov(BITMAP *pantalla){

        int vision=1;
        int veloc=5;

    if(key[KEY_SPACE]&& marcaTiempo(8)){

        play_sample(sonidoBala,230,200,1000,0);
        misBalas.push_back(new Bala(x+10,y,0)); //balas amarillas a la lista //y tipo  de bala
    }
    for(itBala=misBalas.begin();itBala!=misBalas.end();itBala++){
        (*itBala)->disparo(pantalla); //muevo la bala
    }

     if(key[KEY_UP]&& y >30)//el 0 es arriba
       {
           y-=veloc;
           vision=1;

       }
    if(key[KEY_DOWN] && y<490)
        {
            y+=veloc;
            vision=1;
        }
    if(key[KEY_RIGHT] && x<470)
        {
            x+=veloc;
            vision=2;
        }
    if(key[KEY_LEFT] && x>0)
        {
            x-=veloc;
            vision=0;
        }
        if (this->tipoNave==0)
        {
       masked_blit( sprite, pantalla, vision*35, 0, x, y, 35, 48);//pruebo aca
        }
        else
        {
            if (this->tipoNave==1)
            {
            masked_blit( sprite2, pantalla, vision*35, 0, x, y, 35, 48);//pruebo aca
            }
            else
            {
                if (this->tipoNave==2)
                {
                masked_blit( sprite3, pantalla, vision*35, 0, x, y, 35, 48);//pruebo aca
                }
            }
        }
        masked_blit( vidaNave, pantalla, 0, 0, 80, 0, energia, 28);


}
void Nave::CantEnergia(int cantidad, BITMAP *pantalla){//no se usa
this->energia-=cantidad;
refrascarEnergia(pantalla);
}
void Nave::refrascarEnergia(BITMAP *pantalla){
 masked_blit( vidaNave, pantalla, 0, 0, 550, 40, 14, 25*energia);
}
//**********************************************************************
class Enemigo{
    public:
    //atributos
    int t;
    int e;
    int tipoNave;
    float x;
    float y;
    BITMAP* explosion;
    BITMAP* barra_en;
    BITMAP* sprite;
    BITMAP* enemigo2;
    BITMAP* avion;
    int salud;
    int ataque; //tipo de ataque que tiene la nave ovni

    //metodos<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    Enemigo(float x, int ataque,int tipoNave);//constructor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    ~Enemigo(); //destructor
    bool destruirEnemigo();
    void pintar_nave(BITMAP *pantalla);
    void mover_nave(BITMAP *pantalla,Nave *nave);
    void crearEnemigo();
    void accionEnemiga(BITMAP *pantalla, Nave *nave);
    void pintarExplosion(BITMAP *pantalla);
    //objetos de otra clase
    Retraso* pausa;
};
//**********************************************************************

Retraso *esperar =new Retraso(); //para contar tiempos
list<Enemigo*>Ovni;
list<Enemigo*>::iterator itOvni;
list<Bala*>balaEnemiga;
list<Bala*>::iterator itbalaen;

Enemigo::Enemigo(float x, int ataque, int tipoNave){ //constructor
    this->x=x;
    y=0;
    explosion=load_bitmap("explosion.bmp",NULL);
    barra_en=load_bitmap("barrita.bmp",NULL);
    sprite=load_bitmap("ovni.bmp",NULL);
    enemigo2=load_bitmap("enemigo2.bmp",NULL);
    avion=load_bitmap("avion.bmp",NULL);
    this->pausa= new Retraso[15];
    this->ataque=ataque;
    this->salud=90;
    this->tipoNave=tipoNave;
    t=0;
    e=0;
}
//destructor
Enemigo::~Enemigo(){}
//______________________________________________________
void Enemigo::crearEnemigo(){
static int cont=0;
 if(cont<9)//cantidad de enemigos
    {
    if(esperar->alarma(40-this->t))
        {

        int p,q;
        p=rand()/100;
        q=rand()%5;
        if(cont==0 || cont==3 || cont==6)
        Ovni.push_back(new Enemigo(p,q,0));
        if(cont==1 || cont==4 || cont==7)
        Ovni.push_back(new Enemigo(p,q,1));
        if(cont==2 || cont==5 || cont==8)
        Ovni.push_back(new Enemigo(p,q,2));

         balaEnemiga.push_back(new Bala(p,q,1));
        cont++;
        }
    }
 else
    {
    if(esperar->alarma(80-this->e))
        {
        cont=0;
        }
    }
}
//--------------------------------------------------------
void Enemigo::accionEnemiga(BITMAP *buffer, Nave *nave ){
for(itOvni=Ovni.begin();itOvni!=Ovni.end();itOvni++)
    {
    (*itOvni)->mover_nave(buffer,nave);
    if( (*itOvni)->x >= nave->x && (*itOvni)->x <= nave->x+3 &&
              (*itOvni)->y >= nave->y &&(*itOvni)->y<= nave->y+15)//verd o falso)
                {

                    delete(*itOvni);
                    itOvni=Ovni.erase(itOvni);
                    nave->energia-=31;

                }
            if((*itOvni)->destruirEnemigo())
                    {

                   // this->pintarExplosion(buffer);
                    delete(*itOvni);
                    itOvni=Ovni.erase(itOvni);

                    }
    }
    for(itbalaen=balaEnemiga.begin();itbalaen!=balaEnemiga.end();itbalaen++)
        {
        (*itbalaen)->disparo(buffer); //muevo la bala
            if((*itbalaen)->y>490 )
            {
            delete (*itbalaen);
            itbalaen=balaEnemiga.erase(itbalaen);
            }
            if((*itbalaen)->x >= nave->x-10 && (*itbalaen)->x <= nave->x+35 &&
               (*itbalaen)->y >= nave->y-10 && (*itbalaen)->y <= nave->y+28)
               {
                   play_sample((*itbalaen)->sonidoChoque,230,200,1000,0);
                   nave->energia-=30.6;
                   delete (*itbalaen);
                    itbalaen=balaEnemiga.erase(itbalaen);
               }
        }
}
//--------------------------------------------------------
void Enemigo::pintar_nave(BITMAP *pantalla){
    float tamanioBarra;
    int cont=56;
    tamanioBarra=(50.0/100.0)*salud;
    if(salud<0)
    {
        stretch_sprite( pantalla,barra_en,x,y-10,tamanioBarra,5);
        masked_blit( explosion, pantalla, 0+cont, 0, x, y, 20, 20);
    }
    else
    {

    if(tipoNave==0)
        {
            stretch_sprite( pantalla,barra_en,x,y-10,tamanioBarra,5);
            masked_blit( sprite, pantalla, 0, 0, x, y, 40, 30);// te dice donde empieza
        }
    else
        {   if(tipoNave==1){
            stretch_sprite( pantalla,barra_en,x,y-10,tamanioBarra,5);
            masked_blit( enemigo2, pantalla, 0, 0, x, y, 32, 32);// te dice donde empieza
            }else {
                if(tipoNave==2){
                stretch_sprite( pantalla,barra_en,x,y-10,tamanioBarra,5);
                masked_blit( avion, pantalla, 0, 0, x, y, 34, 32);// te dice donde empieza
               // masked_blit( explosion, pantalla, 0, 0, x, y, 20, 20);
                }
            }
        }
    }//else
}
void Enemigo::pintarExplosion(BITMAP *pantalla){
     masked_blit( explosion, pantalla, 0, 0, x, y, 20, 20);
}

bool Enemigo::destruirEnemigo()
{
    if(this->x >450 || this->y >550 /*|| this->salud<=0*/ )
    {
        return true;
    }else
    {
        return false;
    }
}
//---------------------------------------------------------------------------------
void Enemigo::mover_nave(BITMAP *pantalla,Nave *nave){

    switch(this->ataque)//tipos de movimientos del enemigo 0,1,2
    {
    case 0:
        if(x<480 && y<550)
            {
            y+=6;
            x+=4;
            pintar_nave(pantalla);
            }

    break;
    case 1:
        if(x<480 && y<550)
            {
            x+=5;
            y=80;
            pintar_nave(pantalla);
            }
    break;
    case 2:
          x++;
            y+=5;
            if(y>60){
                y+=pow(x/100,2);
                pintar_nave(pantalla);
            }
    break;
    case 3:
         if(x<480 && y<550)
            {
            x--;
            y+=5;
            pintar_nave(pantalla);
            }
    break;
    }
    //-------muevo mis balas
    for(itBala=misBalas.begin();itBala!=misBalas.end();itBala++)
        {
        Bala *B =*itBala;
            if(B->x >= x && B->x <=x+35 && B->y >=y && B->y<=y+35)
            {
                play_sample(B->sonidoChoque,230,200,1000,0);
                delete B;
                this->salud-=30;
                nave->puntaje+=5;//*************puntaje
            }

        }
        for(itBala=misBalas.begin();itBala!=misBalas.end();itBala++)
        {
            Bala *B =*itBala;
            for(itbalaen=balaEnemiga.begin();itbalaen!=balaEnemiga.end();itbalaen++)
            {
                 Bala *B_en =*itbalaen;
            if((B->x >= B_en->x && B->x <= B_en->x && B->y ==B_en->y+1 )|| (B->y ==B_en->y))
                {
                 play_sample(B_en->sonidoChoque,230,200,1000,0);
                delete B_en;
                itbalaen=balaEnemiga.erase(itbalaen);
                delete B;
                itBala=misBalas.erase(itBala);
                nave->puntaje+=1;//************************puntaje
                }
            }
        }

}


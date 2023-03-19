#include <iostream>
#include <allegro.h>
#include <math.h>
#include<list>
#include "inicializacion.h"
#include "Objetos.h"
#include <stdlib.h>
#include "Bala.h"
#include "menuInicio.h"

using namespace std;
int main()
{
 inicia_allegro(660,535);//configuracionpantalla Allegro
//sonido juego
    MIDI *musica1  = load_midi("seal.mid");
 //puntero de imagenes principales
  BITMAP *nube = load_bitmap("nube.bmp",NULL);
  BITMAP *costado = load_bitmap("navecostado.bmp",NULL);
  BITMAP *costado1 = load_bitmap("navecostado1.bmp",NULL);
  BITMAP *costado2 = load_bitmap("navecostado2.bmp",NULL);
  BITMAP *buffer= create_bitmap(660,535);
  clear_to_color(buffer,0xc1c1c1);//fondo grris
//pantalla inicio
  miMenuInicio();
  //elegir nave
  int tipoNave;
  tipoNave=ElegirNave();
  play_midi(musica1,1);
//instancias
 Nave *nave= new Nave(tipoNave);
 Enemigo *enemigo=new Enemigo(-10,1,1);
 //variables
int i=300; //para pantalla con movimiento itera i--
int cont=0;//para timer
int tiempo=0;//time
int pausa=3;
//juego*********************************************************************************
while(!key[KEY_ESC]&& nave->energia>0)
{
//giro de pantalla
 blit(nube,buffer,0,--i,0,0,500,535);  if(i == 0) i=300;
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

if(nave->tipoNave==0)
    {
    blit(costado,buffer,0,0,500,0,500,535);
    }
else
    {
        if(nave->tipoNave==1)
            {
                blit(costado1,buffer,0,0,500,0,500,535);
            }
        else
            {
                if(nave->tipoNave==2)
                blit(costado2,buffer,0,0,500,0,500,535);
            }
    }


//scores
textprintf(buffer,font,5,10,pallete_color[15],"TIME: %d",tiempo);
textprintf(buffer,font,400,10,pallete_color[15],"SCORE:%d",nave->puntaje);
//timer
cont++;
if(cont%50==0) tiempo++;

//Enemigos creados y en accion
enemigo->crearEnemigo();
enemigo->accionEnemiga(buffer,nave);
//movimiento de la nave
 nave->mov(buffer);
 if(nave->energia<0)
        {
        continuarJugando(nave,enemigo);
        tiempo=0;
        cont=0;
        pausa=3;
        }
if(nave->puntaje>800 && nave->puntaje<820 || nave->puntaje>2000 && nave->puntaje<2020 || nave->puntaje>3500 && nave->puntaje<3520 )
    {
    if(nave->puntaje>800 && nave->puntaje<820){
    finEtapa(nave,enemigo);
    nave->puntaje=800+20;
    }
    else
    {
    if(nave->puntaje>2000 && nave->puntaje<2020)
        {
        finEtapa(nave,enemigo);
        nave->puntaje=2000+20;
        pausa=2;
        }
        else
        {
            if(nave->puntaje>3500 && nave->puntaje<3520)
        {
        finEtapa(nave,enemigo);
        nave->puntaje=3500+20;
        pausa=1;
        }
        }
    }

}

 blit(buffer,screen,0,0,0,0,660,535);//refresco de pantalla
 rest(pausa);//pausa y velocidad de iteraccion
}//while juego

destroy_bitmap(buffer);//desturctor
    return 0;
}
END_OF_MAIN();
//************************************************************************************+

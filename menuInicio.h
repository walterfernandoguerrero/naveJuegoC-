
#include <iostream>
#include <allegro.h>
void sonidoClick(){
SAMPLE* click;
click=load_wav("ding.wav");
 play_sample(click,230,200,1000,0);

}
void miMenuInicio()
{
    SAMPLE* titulo;
    titulo=load_wav("tema titulo.wav");
    play_sample(titulo,230,200,1000,0);
    BITMAP *buffer=create_bitmap(660,535);
    BITMAP *fondo=load_bitmap("titulo.bmp",NULL);
    BITMAP *jugar=load_bitmap("titulo2.bmp",NULL);
    BITMAP *flecha=load_bitmap("flecha2.bmp",NULL);

    int salida=0;

    while(!key[KEY_ESC]&&salida==0)
    {

        blit (fondo,buffer,0,0,0,0,660,535);
        if(mouse_x > 286 && mouse_x <410 && mouse_y >319 && mouse_y <388)
            {
                blit(jugar,buffer,0,0,0,0,660,535);
                if(mouse_b & 1)
                {
                sonidoClick();
                salida=1;
                }
            }


            masked_blit(flecha,buffer,0,0,mouse_x,mouse_y,30,15);

       blit (buffer,screen,0,0,0,0,660,535);

    }

destroy_bitmap(jugar);
destroy_bitmap(fondo);
destroy_sample(titulo);

}
int ElegirNave(){

    BITMAP *buffer=create_bitmap(800,500);
    BITMAP *fondo=load_bitmap("tipoNave.bmp",NULL);
    BITMAP *azul=load_bitmap("tipoNave1.bmp",NULL);
    BITMAP *rojo=load_bitmap("tipoNave2.bmp",NULL);
    BITMAP *verde=load_bitmap("tipoNave3.bmp",NULL);
    BITMAP *flecha=load_bitmap("flecha2.bmp",NULL);

    int salida=0;
    int tipo=0;

    while(!key[KEY_ESC]&&salida==0)
    {
        blit (fondo,buffer,0,0,0,0,800,562);

        if(mouse_x > 5 && mouse_x <183 && mouse_y >90 && mouse_y <367)
            {
                blit(verde,buffer,0,0,0,0,800,562);
                if(mouse_b & 1)
                {
                 tipo=2;
                 sonidoClick();
                 salida=1;
                }
            }

            if(mouse_x > 225 && mouse_x <405 && mouse_y >90 && mouse_y <367)
            {
                blit(rojo,buffer,0,0,0,0,800,562);
                if(mouse_b & 1)
                {
                tipo=1;
                 sonidoClick();
                 salida=1;
                }
            }
            if(mouse_x > 470 && mouse_x <650 && mouse_y >90 && mouse_y <367)
            {
                blit(azul,buffer,0,0,0,0,800,562);
                if(mouse_b & 1)
                {
                tipo=0;
                 sonidoClick();
                salida=1;
                }
            }
            masked_blit(flecha,buffer,0,0,mouse_x,mouse_y,30,15);

       blit (buffer,screen,0,0,0,0,800,562);
    }

destroy_bitmap(verde);
destroy_bitmap(rojo);
destroy_bitmap(azul);
destroy_bitmap(fondo);

return tipo;

}

void continuarJugando(Nave* nave, Enemigo* enemigo){

    BITMAP *buffer=create_bitmap(700,500);
    BITMAP *fondo=load_bitmap("fin1.bmp",NULL);
    BITMAP *jugarSi=load_bitmap("fin2.bmp",NULL);
    BITMAP *jugarNo=load_bitmap("fin3.bmp",NULL);

    BITMAP *flecha=load_bitmap("flecha2.bmp",NULL);
    SAMPLE* GameOver;
    GameOver=load_wav("game over.wav");
    play_sample(GameOver,230,200,1000,0);

    nave->x=450;
    nave->y=450;

    int salida=0;
    while(!key[KEY_ESC]&&salida==0)
    {
        blit (fondo,buffer,0,0,0,0,660,535);

        if(mouse_x > 250 && mouse_x <350 && mouse_y >448 && mouse_y <488)
            {
                blit(jugarSi,buffer,0,0,0,0,660,535);
                if(mouse_b & 1)
                {
                 sonidoClick();
                salida=1;
                nave->energia=248;
                nave->puntaje=0;
                nave->tipoNave=ElegirNave();
                enemigo->t=0;
                enemigo->e=0;

                }
            }

            if(mouse_x > 385 && mouse_x <450 && mouse_y >448 && mouse_y <488)
            {
                blit(jugarNo,buffer,0,0,0,0,660,535);
                if(mouse_b & 1)
                {
                 sonidoClick();
                salida=1;
                }
            }
            masked_blit(flecha,buffer,0,0,mouse_x,mouse_y,30,15);
       blit (buffer,screen,0,0,0,0,660,535);
    }

destroy_bitmap(jugarSi);
destroy_bitmap(jugarNo);
destroy_bitmap(fondo);
destroy_sample(GameOver);

}
void finEtapa(Nave* nave, Enemigo* enemigo){
    BITMAP *buffer=create_bitmap(700,500);
    BITMAP *fondo=load_bitmap("completada.bmp",NULL);

    SAMPLE* etapa;
    etapa=load_wav("Stage Clear.wav");
    play_sample(etapa,230,200,1000,0);


    int cont=0;
    int tiempo=39;
    while(!key[KEY_ESC]&&cont<4000)
    {
        cont++;
        blit (fondo,buffer,0,0,0,0,660,535);
        if(nave->puntaje<=820)
        {
            if(tiempo%2==0){
            textprintf(buffer,font,200,315,pallete_color[15],"LA SIGUENTE ETAPA COMIENZA EN... %d",tiempo);
            }
            textprintf(buffer,font,230,335,pallete_color[2]," SU SCORE ES DE :%d PUNTOS ..",nave->puntaje);
            textprintf(buffer,font,230,355,pallete_color[2],"LLEGAN MAS ENEMIGOS ....");
            //timer
            if(cont%100==0) tiempo--;
            enemigo->t=20;
            enemigo->e=40;
        }
        else
        {
            if(nave->puntaje<=2020)
            {
                if(tiempo%2==0){
                textprintf(buffer,font,200,315,pallete_color[15],"LA SIGUENTE ETAPA COMIENZA EN... %d",tiempo);
                }
                textprintf(buffer,font,230,335,pallete_color[2]," SU SCORE ES DE :%d PUNTOS ..",nave->puntaje);
                textprintf(buffer,font,210,355,pallete_color[2],"!!!MUY BIEN JUGAS EXELENTE ....");
                textprintf(buffer,font,180,375,pallete_color[5],"!!!TUS ENEMIGOS VAN A ATACAR A MAS VELOCIDAD!!CUIDADO....");
                //timer
                if(cont%100==0) tiempo--;
            }
            else
            {
                 if(nave->puntaje<=3520)
                {
                    if(tiempo%2==0){
                    textprintf(buffer,font,200,315,pallete_color[15],"LA SIGUENTE ETAPA COMIENZA EN... %d",tiempo);
                    }
                    textprintf(buffer,font,230,335,pallete_color[2]," SU SCORE ES DE :%d PUNTOS ..",nave->puntaje);
                    textprintf(buffer,font,100,355,pallete_color[2],"!!!REALMENTE ERES MUY BUENO TE DEVOLMEMOS TU ENERGIA TE LO MERECES  ....");
                    textprintf(buffer,font,50,375,pallete_color[4],"!!!TUS ENEMIGOS VAN A ATACAR A MAS VELOCIDAD Y CON MAYOR NUMERO!!");
                    textprintf(buffer,font,100,395,pallete_color[4],"!!!!!CUIDADO A POR ELLOS¡¡¡¡¡¡....");
                    nave->energia=248;
                    //timer
                    if(cont%100==0) tiempo--;
                    enemigo->t=30;
                    enemigo->e=60;
                }

            }
        }
       blit (buffer,screen,0,0,0,0,660,535);

    }

    nave->x=450;
    nave->y=450;
    destroy_sample(etapa);
    destroy_bitmap(fondo);
}





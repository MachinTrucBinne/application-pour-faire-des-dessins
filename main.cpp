/*
Noé Aubin-Cadot.
Codé en juin 2017.
Déposé sur GitHub en septembre 2019.
C'est une application pour faire des dessins.
*/
// Compiler avec :
// g++ $(sdl2-config --cflags) -Wall -o main  main.cpp $(sdl2-config --libs)

// Pour C++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>

// Pour SDL
#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Point mouse_position;
    SDL_Point mouse_position_previous;

    // INITIALISATION SDL2
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_DisplayMode current_display_mode;   // On prend la  taille de l'écran
    if (SDL_GetDesktopDisplayMode(0, &current_display_mode) != 0)// message d'erreur si SDL échoue
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return 1;
    }

    // CRÉATION D'UNE FENÊTRE
    window = SDL_CreateWindow("Application pour faire des dessins",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    // CRÉATION D'UN RENDERER
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    // On regarde si la fenêtre a été créée
    if (window == NULL)
    {
        // Si la fenêtre n'a pas été créée on fait un message d'erreur
        std::cout<<"La création de la fenêtre SDL a échoué : "<<SDL_GetError()<<"\n";
        return 1;
    }
    //std::cout<<"\nFenêtre SDL créée !\n\n";
    //std::cout<<"\n\nNombre de pixels horizontaux de mon écran : "<<current_display_mode.w; // c'est le nombre de pixels choisis par préférence système et non le nombre de pixels phyiques de l'écran
    //std::cout<<"\nNombre de pixels verticaux de mon écran : "<<current_display_mode.h;
    //std::cout<<"\nTaux de raffraîchissement de mon écran (Hz) : "<<current_display_mode.refresh_rate;
    // attention car ici l'écran Rétina vient affecter le nombre de pixels

    // On peut regarder le nombre de pixels disponibles dans la fenêtre :
    int gl_w=1; // on met des valeurs inutiles qui sont remplacées juste après
    int gl_h=1; // on met des valeurs inutiles qui sont remplacées juste après
    SDL_GL_GetDrawableSize(window,&gl_w,&gl_h); // ici on met les valeurs en gl_w et en gl_h
    //std::cout<<"\n\nNombre de pixels horizontaux de la fenêtre : "<<gl_w;
    //std::cout<<"\nNombre de pixels verticaux de la fenêtre : "<<gl_h<<std::endl;
    
    // CRÉATION D'UNE TEXTURE
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,gl_w,gl_h);

    bool mouse_hold_click = false;
    int currentTime;
    int lastTime = 0;

    // La fenêtre est ouverte, on peut donc entrer une boucle ici (voir SDL_PollEvent())
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        SDL_Delay(16);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) // si on change la taille de la fenêtre
                {
                    SDL_GL_GetDrawableSize(window,&gl_w,&gl_h);
                    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,gl_w,gl_h);
                    //std::cout<<"\n\nNombre de pixels horizontaux de la fenêtre : "<<gl_w;
                    //std::cout<<"\nNombre de pixels verticaux de la fenêtre : "<<gl_h<<std::endl;
                }
            }
            if (event.type == SDL_KEYDOWN)
            {   
                //std::cout<<"\n\nevent.key.keysym.sym : "<<event.key.keysym.sym;
                //std::cout<<"\nevent.key.keysym.mod : "<<event.key.keysym.mod;
                //std::cout<<"\nevent.key.keysym.scancode : "<<event.key.keysym.scancode;
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
                if (event.key.keysym.sym == 99) // la touche c
                {
                    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,gl_w,gl_h);    // on réinitialise la texture
                }
                if (event.key.keysym.sym == 115) // la touche s
                {
                    system("screencapture ~/Desktop/screenshot.jpg"); // on fait un screenshot du beau dessin
                }
            }
            mouse_position_previous = mouse_position;
            SDL_GetMouseState(&mouse_position.x,&mouse_position.y);
            // Pour la souris
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                mouse_hold_click = true;
            }
            if (mouse_hold_click == true)
            {
                SDL_RenderClear(renderer);  // on vide le renderer
                SDL_SetRenderTarget(renderer, texture); //on modifie la texture et non plus le renderer
                SDL_SetRenderDrawColor(renderer,255,255,255,255);    // le dernier param. est l'opacité
                
                for (int i=0;i<10;i++)
                {
                    for (int j=0;j<10;j++)
                    {
                        SDL_RenderDrawLine(renderer,2*mouse_position_previous.x+i,2*mouse_position_previous.y+j,2*mouse_position.x+i,2*mouse_position.y+j); // on met une ligne dans le renderer target (i.e. la texture)
                    }
                }
                texture = SDL_GetRenderTarget(renderer);
                SDL_SetRenderTarget(renderer, NULL);// Dorénavent, on modifie à nouveau le renderer et non plus la texture target
            }
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                mouse_hold_click = false;
                mouse_position_previous = mouse_position;
            }
        }
        currentTime = SDL_GetTicks(); // on prend l'heure pour le taux d'affichage
        if(currentTime > lastTime + 16) // pause avant l'affichage en millisecondes (16 = optimal car écran à 60Hz, sinon 100 donne truc intéressant)
        {
            SDL_RenderClear(renderer);  // on claire le renderer
            SDL_SetRenderDrawColor(renderer,0,0,0,0);    // on remet la couleur du renderer à noir
            SDL_RenderCopy(renderer, texture, NULL, NULL);  // on met la texture dans le renderer
            SDL_RenderPresent(renderer); // on affiche le contenu du renderer à l'écran

            lastTime = currentTime;
        }    
    }
    // Bye bye
    std::cout<<"\n\nAu revoir !\n\n";
    // On termine le programme (vider la mémoire vive utilisée)
    SDL_DestroyRenderer(renderer); // on détruit le renderer
    SDL_DestroyWindow(window);  // On ferme la fenêtre
    SDL_DestroyTexture(texture); // on détruit la texture
    SDL_Quit(); // On quitte SDL
    return 0;
}
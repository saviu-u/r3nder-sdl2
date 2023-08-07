#include <iostream>
#include "screen.h"

Screen::Screen() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
}

void Screen::show(){
  while (!quit)
  {
    // Verifica se é pra sair da tela ou não (clicando no X), se não colocar isso, só matando processo
    verifyScreenInput();

    // Desenha
    cleanScreen();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLineF(renderer, 0, 0, 200, 200);
    // (Fim) Desenha

    // Atualiza o quadro no final
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Screen::verifyScreenInput(){
  while (SDL_PollEvent(&event))
  {
      // Faz funcionar pra sair da janela
      if (event.type == SDL_QUIT) quit = 1;
  }
}

void Screen::cleanScreen(){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}
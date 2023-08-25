#include <SDL2/SDL.h>
#include <numeric>
#include <iostream>
#include <complex>
#include <process.h>

double scale_factor = 1000;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int is_in_mandelbrot_set(std::complex<double> c)
{
    std::complex<double> z(0, 0);
    for (int i = 0; i < 200; i++)
    {
        z = std::pow(z, 2) + c;
        if (std::norm(z) > 10)
        {
            return i;
        };
    }
    return 0;
}

float lerp(float a, float b, float f)
{
    return (a * (1.0 - f)) + (b * f);
}

void draw_Mandelbrot(void *pArg)
{
   
}

int main(int argv, char **args)
{
    SDL_CreateWindowAndRenderer(1000, 1000, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 2, 2);

    // int iTarget;
    // uintptr_t hLoadingThread = _beginthread(draw_Mandelbrot, 0, &iTarget);

     for (double x = 0.0; x < 1.0; x += 1 / scale_factor)
    {
        for (double y = 0.0; y < 1.0; y += 1 / scale_factor)
        {
            double loc_x = lerp(-2.0, 2.0, x);
            double loc_y = lerp(-2.0, 2.0, y);
            int iters = is_in_mandelbrot_set(std::complex<double>(loc_x, loc_y));
            if (iters == 0)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawPointF(renderer, loc_x * 100 + 200, loc_y * 100 + 200);
            }
            else
            {
                SDL_SetRenderDrawColor(
                    renderer,
                    4 * iters % 255,
                    4 * iters % 255,
                    4 * iters % 255,
                    255);
                SDL_RenderDrawPointF(renderer, loc_x * 100 + 200, loc_y * 100 + 200);
            }
        }
    }
    
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                exit;
            }
        }
        SDL_RenderPresent(renderer);
    }
    
}
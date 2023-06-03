#include <iostream>
#include <random>
#include <algorithm>
#include <SDL2/SDL.h>
#include <chrono>

using namespace std::chrono;

SDL_Renderer* setup() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(100*5, 100*5, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 5 , 5);
    return renderer;
}

void draw(std::vector<int>& v,  SDL_Renderer* renderer, unsigned int red, unsigned int blue) {
    // Clear the Screen
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    int index = 0;
    for( int i : v) {
        if(index == red)
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
        else if(index == blue)
            SDL_SetRenderDrawColor(renderer, 0,0,255,255);
        else
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderDrawLine(renderer, index, 0, index, i );
        index += 1;
    }

     // Update Window
    SDL_RenderPresent(renderer);
}

void sort(std::vector<int>& v, SDL_Renderer* renderer) {
     // Loop through V, checking if later values are smaller 
    for(unsigned int i = 0; i < v.size(); i++) {
        for(unsigned int j = i; j < v.size(); j++)
        {
            if(v[j] < v[i]) {
                std::swap(v[j], v[i]);
            }
     
            // Draw Sort
            draw(v, renderer, i, j);

        }
    }
}


std::vector<int> get_randomized_vector() {
    std::random_device rd;
    std::uniform_int_distribution<> distrib(1,99);
    std::vector<int> v;

    // Push random numbers into Vector
    for(int i = 0; i < 100; i++) {
        v.push_back(distrib(rd));
    }
    return v;
}

// int argc, char *argv[] - SDL required signatures - otherwise E: undefined reference to `SDL_main'
int main( int argc, char *argv[] )
{

    std::vector<int> v = get_randomized_vector();
    SDL_Renderer* renderer = setup();
    
    auto t1 = high_resolution_clock::now();
    sort(v, renderer);
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    


    // Foreach loop to print out sorted values
    for(int i :v) {
        std::cout << i << "\n";
    }

    if(std::is_sorted(v.begin(), v.end())) {
        std::cout << "Sorting finished!\n";
    }
    std::cout << ms_double.count() << "ms\n";
}
 

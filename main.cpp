#include <iostream>
#include <random>
#include <algorithm>
#include <SDL2/SDL.h>
#include <chrono>
#include <SDL2/SDL_Mixer.h>

using namespace std::chrono;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
Mix_Chunk *sound = nullptr;


int setup()
{

    //"VIDEO"
    SDL_CreateWindowAndRenderer(100 * 5, 100 * 5, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 5, 5);

    // AUDIO
    SDL_Init(SDL_INIT_AUDIO);
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 4;
    int audio_buffers = 0;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "COULDN'T INIT AUDIO: %s", Mix_GetError());
        exit(-1);
    }
}

void draw(std::vector<int> &v, unsigned int red, unsigned int blue)
{
    // Clear the Screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int index = 0;
    for (int i : v)
    {
        if (index == red)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (index == blue)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, index, 0, index, i);
        index += 1;
    }

    // Update Window
    SDL_RenderPresent(renderer);
}

void selection_sort_descending(std::vector<int> &v)
{
    // Loop through V, checking if later values are smaller
    for (unsigned int i = 0; i < v.size(); i++)
    {
        for (unsigned int j = i; j < v.size(); j++)
        {
            if (v[j] < v[i])
            {
                
                std::swap(v[j], v[i]);
            }
            Mix_PlayChannel(1, sound, 0);
            // Draw Sort
            draw(v, i, j);
        }
    }
}

void selection_sort_ascending(std::vector<int> &v)
{
    // Loop through V, checking if later values are larger
    for (unsigned int i = 0; i < v.size(); i++)
    {
        for (unsigned int j = i; j < v.size(); j++)
        {
            if (v[j] > v[i])
            {
                
                std::swap(v[j], v[i]);
            }
            Mix_PlayChannel(1, sound, 0);
            // Draw Sort
            draw(v, i, j);
        }
    }
}

void insertion_sort_ascending(std::vector<int> &v)
{
    for(unsigned int i = 1; i < v.size(); i++) {

        unsigned int val = v[i];
        unsigned int j = i;
        
        while (j > 0 and v[j-1] < val) {
            std::swap(v[j], v[j-1]);
            j -= 1;
            draw(v, i, j);
        }
        v[j] = val;
        draw(v, i, j);
        
    }
}
void insertion_sort_descending(std::vector<int> &v)
{
    for(unsigned int i = 1; i < v.size(); i++) {

        unsigned int val = v[i];
        unsigned int j = i;

        while (j > 0 and v[j-1] > val) {
            std::swap(v[j], v[j-1]);
            j -= 1;
            draw(v, i, j);
        }
        v[j] = val;
        draw(v, i, j);
        
    }
}

std::vector<int> get_randomized_vector()
{
    std::vector<int> v;
    std::mt19937 rng_mt(std::time(nullptr));
    std::uniform_int_distribution<> distr(1, 99);

    // Push random numbers into Vector
    for (int i = 0; i <= 100; i++)
    {
        v.push_back(distr(rng_mt));
    }
    return v;
}

void controls()
{
    std::cout
        << "    Use 0 to close the application \n"
        << "    Use 1 to start Selection Sort Algorithm.\n"
        << "    Use 2 to start Insertion Sort Algorithm.\n"
        << "    Use 3 to start Bubble Sort Algorithm.\n"
        << "    Use 4 to start Merge Sort Algorithm.\n"
        << "    Use 5 to start Quick Sort Algorithm.\n"
        << "    Use 6 to start Heap Sort Algorithm.\n"
        << "    Use q to exit out of Sorting Visualizer\n";
}

void kill()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void time_run_algorithm(void (*algorithm)(std::vector<int> &v) )
{
    std::vector<int> v;
    duration<double, std::milli> ms_double;
    system_clock::time_point t1;
    system_clock::time_point t2;

    v = get_randomized_vector();
    t1 = high_resolution_clock::now();
    algorithm(v);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    std::cout << "Finished sorting in: " << ms_double.count() << " ms\n";
}

// int argc, char *argv[] - SDL required signatures - otherwise E: undefined reference to `SDL_main'
int main(int argc, char *argv[])
{
    setup();
    sound = Mix_LoadWAV("./low.wav");
    
    bool quit = false;

    std::cout << "\n";
    controls();
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e)) // DO NOT CHECK IF EVENT IS EMPTY - OTHERWISE EVENTLOOP WON'T WORK!L
        {
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case (SDLK_0):
                    quit = true;
                    std::cout << "\nEXITING SORTING VISUALIZER.\n";
                    break;
                case (SDLK_1):
                    time_run_algorithm(selection_sort_ascending);
                    break;

                case (SDLK_2):
                    time_run_algorithm(selection_sort_descending);
                    break;
                case (SDLK_3):
                    time_run_algorithm(insertion_sort_ascending);
                    break;
                case (SDLK_4):
                    time_run_algorithm(insertion_sort_descending);
                    break;
                }
            }
        }
    }

    kill();
    return 0;
}

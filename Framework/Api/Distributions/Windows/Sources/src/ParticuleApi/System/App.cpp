#include <ParticuleApi/System/App.hpp>
#include <algorithm>
#include <stdexcept>
#include <windows.h>
#include <ParticuleApi/System/sdl2.hpp>

namespace Particule::Api
{
    Window* App::DrawWindow = nullptr; // Initialisation du pointeur statique vers la fenêtre de dessin
    Time App::time; // Instance statique de la classe Time
    App* App::instance = nullptr; // Initialisation de l'instance statique de l'application
    Window* App::MainWindow = nullptr; // Initialisation du pointeur statique vers la fenêtre principale

    App::App()
    {
        instance = this; // Assigner l'instance courante à l'instance statique
        // Initializes the SDL.
        if (sdl2::SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error("error Init " + sdl2::SDL2_GetError());
        ResetWorkingDirectory(); // Réinitialiser le répertoire de travail
        // Initializes the image library.
        if (sdl2::IMG_Init(sdl2::IMG_INIT_PNG) == 0)
            throw std::runtime_error("error IMG_Init " + sdl2::SDL2_GetError());
        // Initializes the font library.
        if (sdl2::TTF_Init() == -1)
            throw std::runtime_error("error TTF_Init " + sdl2::SDL2_GetError());
    }

    App::~App()
    {
        for (auto window : windows) // Libérer toutes les fenêtres créées
        {
            if (window != nullptr) // Vérifier si la fenêtre n'est pas nulle
            {
                window->OnClose(); // Appeler la méthode de fermeture de la fenêtre
                delete window; // Libérer la mémoire allouée pour la fenêtre
            }
        }
        windows.clear(); // Vider le vecteur de fenêtres
    }

    void App::ResetWorkingDirectory(){
        // Obtenez le chemin absolu du programme
        char *path = sdl2::SDL_GetBasePath();
        if (path == NULL)
            throw std::runtime_error("error SDL_GetBasePath "+ sdl2::SDL2_GetError());
        // Changez le répertoire de travail
        if (!SetCurrentDirectory(path))
            throw std::runtime_error("error chdir "+ sdl2::SDL2_GetError());
        sdl2::SDL_free(path);
    }
    void App::SetWorkingDirectory(std::string& path){
        // Changez le répertoire de travail
        if (!SetCurrentDirectory(path.c_str()))
            throw std::runtime_error("error chdir "+ sdl2::SDL2_GetError());
    }
    std::string App::GetWorkingDirectory(){ 
        char path[MAX_PATH];
        if (GetCurrentDirectoryA(MAX_PATH, path) == 0)
            throw std::runtime_error("error GetCurrentDirectory "+ sdl2::SDL2_GetError());
        return std::string(path);
    }

    void App::Update()
    {
        time.Update(); // Mettre à jour le temps
        uint32_t startTime = sdl2::SDL_GetTicks(); // Obtenir le temps de début
        for (auto window : windows) // Parcourir toutes les fenêtres
        {
            if (window != nullptr) // Vérifier si la fenêtre n'est pas nulle
            {
                App::DrawWindow = window; // Définir la fenêtre de dessin
                window->OnUpdate(); // Appeler la méthode de mise à jour de la fenêtre
            }
        }
        //limit a 120 fps
        uint32_t endTime = sdl2::SDL_GetTicks(); // Obtenir le temps de fin
        uint32_t deltaTime = endTime - startTime; // Calculer le temps écoulé
        if (deltaTime < 1000 / 120) // Vérifier si le temps écoulé est inférieur à la limite de 120 FPS
        {
            sdl2::SDL_Delay(1000 / 120 - deltaTime); // Attendre pour respecter la limite de FPS
        }
    }

    void App::AddWindow(Window* window)
    {
        if (window != nullptr) // Vérifier si la fenêtre n'est pas nulle
        {
            windows.push_back(window); // Ajouter la fenêtre au vecteur de fenêtres
            window->OnStart(); // Appeler la méthode de démarrage de la fenêtre
            if (MainWindow == nullptr) // Vérifier si la fenêtre principale est nulle
                MainWindow = window; // Définir la fenêtre principale
        }
    }

    void App::RemoveWindow(Window* window)
    {
        if (window != nullptr) // Vérifier si la fenêtre n'est pas nulle
        {
            auto it = std::find(windows.begin(), windows.end(), window); // Trouver la fenêtre dans le vecteur
            if (it != windows.end()) // Vérifier si la fenêtre a été trouvée
            {
                windows.erase(it); // Supprimer la fenêtre du vecteur
                if (window == MainWindow) // Vérifier si la fenêtre est la fenêtre principale
                    MainWindow = nullptr; // Réinitialiser la fenêtre principale
                window->OnClose(); // Appeler la méthode de fermeture de la fenêtre
                delete window; // Libérer la mémoire allouée pour la fenêtre
            }
        }
    }

    std::vector<Window*> App::GetWindows()
    {
        return windows; // Retourner le vecteur de fenêtres
    }

    Window* App::GetWindow(size_t index)
    {
        if (index < windows.size()) // Vérifier si l'index est valide
            return windows[index]; // Retourner la fenêtre à l'index spécifié
        return nullptr; // Retourner un pointeur nul si l'index est invalide
    }

    void App::SetIcon(Resource path)
    {
        (void)path; // Ignorer le paramètre de chemin
        //if (MainWindow != nullptr) // Vérifier si la fenêtre principale n'est pas nulle
        //    sdl2::SetWindowIcon(MainWindow->window, path); // Définir l'icône de la fenêtre principale
    }

    double App::FPS()
    {
        static double fps = 100; // Initialiser le nombre d'images par seconde à 100
        if (time.DeltaTime() > 0) // Vérifier si le temps écoulé est supérieur à zéro
            fps = 1.0 / time.DeltaTime(); // Calculer le nombre d'images par seconde
        return fps; // Retourner le nombre d'images par seconde
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Particule::Api::App app; // Créer une instance de l'application
    int value = MainApp(&app, __argc, __argv); // Appeler la fonction principale de l'application
    if (value == EXIT_SUCCESS)
    {
        while (app.GetMainWindow() != nullptr) // Boucle tant que la fenêtre principale n'est pas nulle
            app.Update(); // Mettre à jour l'application
    }
    return value; // Retourner le code de sortie de l'application
}
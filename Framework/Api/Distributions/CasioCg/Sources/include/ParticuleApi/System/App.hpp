#ifndef APP_HPP
#define APP_HPP
#include <ParticuleApi/System/Window.hpp>
#include <ParticuleApi/System/Resource.hpp>
#include <ParticuleApi/System/Time.hpp>
#include <ParticuleApi/System/Resource.hpp>
#include <vector>
#include <string>

namespace Particule::Api
{
    class App
    {
    private:
        static Window* MainWindow;
        std::vector<Window*> windows;
         // Indique si le monde est actif ou non
    public:
        static Time time;
        static App* instance; // Instance unique de l'application

        App();
        App(const App& other) = delete; // Suppression du constructeur de copie
        App& operator=(const App& other) = delete; // Suppression de l'opérateur d'affectation
        ~App();
        void ResetWorkingDirectory(); // Réinitialise le répertoire de travail
        void SetWorkingDirectory(std::string& path); // Définit le répertoire de travail
        std::string GetWorkingDirectory(); // Récupère le répertoire de travail

        void Update(); // Met à jour l'application

        void AddWindow(Window* window); // Ajoute une fenêtre à l'application
        void RemoveWindow(Window* window); // Supprime une fenêtre de l'application

        inline void SetMainWindow(Window* window) { MainWindow = window; } // Définit la fenêtre principale de l'application
        inline Window* GetMainWindow() { return MainWindow; } // Récupère la fenêtre principale de l'application

        std::vector<Window*> GetWindows(); // Récupère toutes les fenêtres de l'application
        Window* GetWindow(size_t index); // Récupère une fenêtre par son index

        void SetIcon(Resource path); // Définit l'icône de l'application

        double FPS(); // Récupère le nombre d'images par seconde
    };
}

int MainApp(Particule::Api::App* app, int argc, char* argv[]); // Déclaration de la fonction principale de l'application

#endif // APP_HPP
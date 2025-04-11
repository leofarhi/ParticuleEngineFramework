#include <ParticuleApi/System/App.hpp>
#include <algorithm>

namespace Particule::Api
{
    Time App::time; // Instance statique de la classe Time
    App* App::instance = nullptr; // Initialisation de l'instance statique de l'application
    Window* App::MainWindow = nullptr; // Initialisation du pointeur statique vers la fenêtre principale

    App::App()
    {
        instance = this; // Assigner l'instance courante à l'instance statique
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

    void App::ResetWorkingDirectory(){}
    void App::SetWorkingDirectory(std::string& path){(void)path;} // Ne rien faire pour le répertoire de travail
    std::string App::GetWorkingDirectory(){ return ""; } // Retourner une chaîne vide pour le répertoire de travail

    void App::Update()
    {
        time.Update(); // Mettre à jour le temps
        for (auto window : windows) // Parcourir toutes les fenêtres
        {
            if (window != nullptr) // Vérifier si la fenêtre n'est pas nulle
                window->OnUpdate(); // Appeler la méthode de mise à jour de la fenêtre
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
        // Ne rien faire pour l'icône de l'application
        (void)path;
    }

    double App::FPS()
    {
        static double fps = 100; // Initialiser le nombre d'images par seconde à 100
        if (time.DeltaTime() > 0) // Vérifier si le temps écoulé est supérieur à zéro
            fps = 1.0 / time.DeltaTime(); // Calculer le nombre d'images par seconde
        return fps; // Retourner le nombre d'images par seconde
    }
}

int main()
{
    Particule::Api::App app; // Créer une instance de l'application
    int value = MainApp(&app, 0, nullptr); // Appeler la fonction principale de l'application
    if (value == EXIT_SUCCESS)
    {
        while (app.GetMainWindow() != nullptr) // Boucle tant que la fenêtre principale n'est pas nulle
            app.Update(); // Mettre à jour l'application
    }
    return value; // Retourner le code de sortie de l'application
}
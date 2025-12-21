#include "grille.hpp"
#include <iostream>

int main(){

    auto desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Tetris", sf::State::Windowed); //création de la fenêtre de jeu 
    window.setFramerateLimit(60);

    grille matrice;

    for (int j = 0; j < 10; ++j){
        matrice.set(18,j,1);
    }
    while (window.isOpen()){ //boucle pour pouvoir fermer la fenêtre
        
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    window.clear(sf::Color(20,20,20));
    matrice.afficher(window,520);
    window.display();
    }
    
    
}

/*int main()
{
    // SFML 3: VideoMode takes a Vector2u for size
    RenderWindow window(VideoMode({800u, 600u}), "Mon Titre");
    window.setVerticalSyncEnabled(true);
    Font police;
    

    if (!police.openFromFile("../../src/res/poppins.ttf")) {
        std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        return -1;
    }

    String texteAccentue = "Bonjour avec ma police personnalisée!";
    Text texte(police);
    texte.setString(texteAccentue);
    texte.setCharacterSize(30); // Taille en pixels
    texte.setFillColor(Color::White);
    texte.setStyle(Text::Bold); // Optionnel: Bold, Italic, Underlined
    texte.setPosition({100, 250});

    while (window.isOpen())
    {
        // SFML 3: pollEvent() returns std::optional<Event>
        while (std::optional event = window.pollEvent())
        {
            // SFML 3: Check event type using is<T>() and get<T>()
            if (event->is<Event::Closed>())
            {
                window.close();
            }

        }

        window.clear(Color::Black);
        window.draw(texte);
        window.display();
    }

    return 0;
}*/

/*int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
*/
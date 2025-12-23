#include "grille.hpp"
#include "menu.hpp"
#include <iostream>


enum class GameState {
    MENU,
    PLAYING,
    OPTIONS,
    SCORES
};

int main(){

    auto desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Tetris", sf::State::Windowed); //création de la fenêtre de jeu 
    window.setFramerateLimit(60);



    GameState etat_courant = GameState::MENU;

    Menu menu(desktop.size.x, desktop.size.y);
    menu.loadBackground("../src/res/image.jpg",desktop.size.x, desktop.size.y);

    
    grille matrice;

    for (int j = 0; j < 10; ++j){
        matrice.set(18,j,1);
    }

    while (window.isOpen()){ 

        if (etat_courant == GameState::MENU){
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            menu.mouvement_souris(worldPos);
        }
        
        while (const std::optional event = window.pollEvent()){

            if (event->is<sf::Event::MouseButtonPressed>()){ //évènement pour un clic de souris
                auto clicEvent = event->getIf<sf::Event::MouseButtonPressed>();

                if (etat_courant == GameState::MENU && clicEvent->button == sf::Mouse::Button::Left ){
                sf::Vector2f sourisPos = window.mapPixelToCoords( sf::Vector2i(clicEvent->position) );
                int clic = menu.clic_souris(sourisPos);

                    if (clic != -1) {
                        switch (clic) {
                            case 0:
                                etat_courant = GameState::PLAYING;
                                break;
                            case 3:
                                window.close();
                                break;
                        }
                    }
                }
            }
            

            if (event->is<sf::Event::Closed>()) //pour pouvoir fermer la fenêtre
                window.close();
            
            if (event->is<sf::Event::KeyPressed>()){ //évènement pour une touche pressée
                auto toucheEvent = event->getIf<sf::Event::KeyPressed>();

                if (toucheEvent->code == sf::Keyboard::Key::Enter){
                   etat_courant = GameState::PLAYING;
                }
                if (toucheEvent->code == sf::Keyboard::Key::Escape){
                   etat_courant = GameState::MENU;
                }
            }
            
        }
    window.clear(sf::Color(20,20,20));
    if (etat_courant == GameState::MENU){
        menu.dessiner(window);
    }
    if (etat_courant == GameState::PLAYING){
        matrice.afficher(window,520);
    }
    
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
#include "pieces.hpp"
#include "menu.hpp"
#include "horloge.hpp"

#include <iostream>


enum class GameState {
    MENU,
    PLAYING,
    OPTIONS,
    SCORES
};

int main(){

    auto bureau = sf::VideoMode::getDesktopMode(); // récupération des dimensions de l'écran
    sf::RenderWindow fenetre(bureau, "Tetris", sf::State::Windowed); //création de la fenêtre de jeu 
    fenetre.setFramerateLimit(60);



    GameState etat_courant = GameState::MENU;
    int largeur = bureau.size.x;
    int hauteur = bureau.size.y;
    Menu menu(largeur, hauteur);
    menu.loadBackground("../src/res/image.jpg",largeur, hauteur);

    Horloge horloge;
    
    grille matrice;

    /*for (int j = 0; j < 10; ++j){
        matrice.set(18,j,1);
        matrice.set(10+j,5,1);
    }*/
    bool clicked = false;
    std::unique_ptr<Piece> piece = std::make_unique<PieceL>();

    while (fenetre.isOpen()){ 


        if (etat_courant == GameState::MENU){
            sf::Vector2i pixelPos = sf::Mouse::getPosition(fenetre);
            sf::Vector2f globalPos = fenetre.mapPixelToCoords(pixelPos);
            menu.mouvement_souris(globalPos, clicked);
        }
        
        while (const std::optional event = fenetre.pollEvent()){ //récupère le premier évènement dans la file

            
            if (event->is<sf::Event::MouseButtonPressed>()){
                clicked = true;
            }
            if (event->is<sf::Event::MouseButtonReleased>()){ //évènement pour un clic de souris
                
                clicked = false;
                auto clicEvent = event->getIf<sf::Event::MouseButtonReleased>();

                if (etat_courant == GameState::MENU && clicEvent->button == sf::Mouse::Button::Left ){
                
                sf::Vector2f sourisPos = fenetre.mapPixelToCoords( clicEvent->position );

                int clic = menu.clic_souris(sourisPos);
    
                    if (clic != -1) {
                        switch (clic) {
                            case 0:
                                horloge.restart();
                                etat_courant = GameState::PLAYING;
                            
                                break;
                            case 3:
                                fenetre.close();
                                break;
                        }
                    }
                }
            }
            

            if (event->is<sf::Event::Closed>()) //pour pouvoir fermer la fenêtre
                fenetre.close();
            
            if (event->is<sf::Event::KeyPressed>()){ //évènement pour une touche pressée
                auto toucheEvent = event->getIf<sf::Event::KeyPressed>();

                
                if (toucheEvent->code == sf::Keyboard::Key::Enter){
                   etat_courant = GameState::PLAYING;
                }
                if (toucheEvent->code == sf::Keyboard::Key::Escape){
                   etat_courant = GameState::MENU;
                }
                
                if (etat_courant == GameState::PLAYING){
                    auto touche = toucheEvent->code;

                    if (touche == sf::Keyboard::Key::Left || touche == sf::Keyboard::Key::Right || touche == sf::Keyboard::Key::Down){
                        piece->mouvement(matrice, touche);

                    }
                    if (touche == sf::Keyboard::Key::Space){
                        piece = piece_aleatoire();
                        piece->apparition(matrice);    
                    }
                    if (touche == sf::Keyboard::Key::Up){
                        piece->rotation(matrice);
                        
                    }
                }
                
            }

        }
    fenetre.clear(sf::Color(20,20,20));

    if (etat_courant == GameState::MENU){
        menu.dessiner(fenetre);
    }

    if (etat_courant == GameState::PLAYING){
        horloge.dessiner_horloge(fenetre, largeur/1.2, hauteur/2);
        matrice.afficher(fenetre,520);
    
    }
    
    fenetre.display();      
    }
    
}



#include "pieces.hpp"
#include "menu.hpp"
#include "horloge.hpp"
#include "score.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp> 

enum class GameState {
    MENU,
    LEVEL_SELECT,
    PLAYING,
    OPTIONS,
    SCORES,
    GAME_OVER
};



int main(){

    auto bureau = sf::VideoMode::getDesktopMode();
    sf::RenderWindow fenetre(bureau, "Tetris", sf::State::Windowed);
    fenetre.setFramerateLimit(60);

    GameState etat_courant = GameState::MENU;
    int largeur = bureau.size.x;
    int hauteur = bureau.size.y;

    Menu menu(largeur, hauteur);
    menu.loadBackground("../src/res/image.jpg",largeur, hauteur);

    Horloge horloge;
    sf::Clock horloge_gravite;
    
    grille matrice;
    Score score;
    int niveau_choisi = 0;
    
    bool clicked = false;
    std::unique_ptr<Piece> piece = piece_aleatoire();

    

    auto reset_jeu = [&](){
        matrice = grille();
        score.reset();
        niveau_choisi = 0;
        piece = piece_aleatoire();
        piece->apparition(matrice);
        horloge.restart();
        horloge_gravite.restart();
    };

    while (fenetre.isOpen()){ 

        if (etat_courant == GameState::MENU){
            sf::Vector2i pixelPos = sf::Mouse::getPosition(fenetre);
            sf::Vector2f globalPos = fenetre.mapPixelToCoords(pixelPos);
            menu.mouvement_souris(globalPos, clicked);
        }
        
        while (const std::optional event = fenetre.pollEvent()){

            if (event->is<sf::Event::MouseButtonPressed>())
                clicked = true;

            if (event->is<sf::Event::MouseButtonReleased>()){
                clicked = false;
                auto clicEvent = event->getIf<sf::Event::MouseButtonReleased>();

                if (etat_courant == GameState::MENU && clicEvent->button == sf::Mouse::Button::Left ){
                    sf::Vector2f sourisPos = fenetre.mapPixelToCoords(clicEvent->position);
                    int clic = menu.clic_souris(sourisPos);

                    if (clic == 0)
                        etat_courant = GameState::LEVEL_SELECT;
                    if (clic == 3)
                        fenetre.close();
                }
            }

            if (event->is<sf::Event::Closed>())
                fenetre.close();
            
            if (event->is<sf::Event::KeyPressed>()){
                auto toucheEvent = event->getIf<sf::Event::KeyPressed>();

                if (etat_courant == GameState::LEVEL_SELECT){
                    if (toucheEvent->code == sf::Keyboard::Key::Left && niveau_choisi > 0)
                        niveau_choisi--;

                    if (toucheEvent->code == sf::Keyboard::Key::Right && niveau_choisi < 15)
                        niveau_choisi++;

                    if (toucheEvent->code == sf::Keyboard::Key::Enter){
                        matrice = grille();
                        score.reset();
                        score.niveau = niveau_choisi;
                        score.actualisation();
                        score.nb_ligne_casse = niveau_choisi * 10;
                        horloge.restart();
                        horloge_gravite.restart();
                        etat_courant = GameState::PLAYING;
                    }
                }

                if (toucheEvent->code == sf::Keyboard::Key::Escape){
                    reset_jeu();
                    etat_courant = GameState::MENU;
                }
                
                if (etat_courant == GameState::PLAYING){
                    auto touche = toucheEvent->code;

                    if (touche == sf::Keyboard::Key::Left || touche == sf::Keyboard::Key::Right || touche == sf::Keyboard::Key::Down)
                        piece->mouvement(matrice, touche);

                    if (touche == sf::Keyboard::Key::Up)
                        piece->rotation(matrice);
                }

                if (etat_courant == GameState::GAME_OVER){
                    if (toucheEvent->code == sf::Keyboard::Key::Enter){
                        reset_jeu();
                        etat_courant = GameState::LEVEL_SELECT;
                    }
                }
            }
        }

        fenetre.clear(sf::Color(20,20,20));

        if (etat_courant == GameState::MENU){
            menu.afficher_menu(fenetre);
        }

        else if (etat_courant == GameState::LEVEL_SELECT){
            menu.afficher_selection(fenetre, niveau_choisi);
        }

        else if (etat_courant == GameState::PLAYING){
            if(!piece->gravite(horloge_gravite, matrice, score.niveau)){
                std::array<int,4> lignes = matrice.ligne_complete();

                if (lignes[0] > -1){
                    matrice.actualisation(lignes);
                    score.nb_ligne_casse += score.combo(lignes);
                    score.niveau = score.nb_ligne_casse / 10;
                    score.calcul(score.combo(lignes));
                }

                piece = piece_aleatoire();

                if (!matrice.emplacement_disponible(piece->position))
                    {etat_courant = GameState::GAME_OVER;}
                else
                    {piece->apparition(matrice);}
            }

            horloge.dessiner_horloge(fenetre, largeur/1.2, hauteur/2);
            matrice.afficher(fenetre, 520);
            score.afficher(fenetre);
        }

        else if (etat_courant == GameState::GAME_OVER){
            fenetre.clear(sf::Color::Black);
            menu.afficher_fin(fenetre);
            score.afficher(fenetre);
        }

        fenetre.display();
    }
}
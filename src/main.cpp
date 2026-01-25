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
    PLAYING,
    OPTIONS,
    SCORES,
    GAME_OVER
};




void dessiner(GameState etat_courant, sf::RenderWindow fenetre, int largeur, int hauteur, grille matrice, Horloge horloge, Menu Menu );


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
    sf::Clock horloge_gravite;
    
    grille matrice;
    Score score;
    
    bool clicked = false;
    std::unique_ptr<Piece> piece = piece_aleatoire();

    //Texte pour le "Game Over"
    sf::Font police;

    sf::Text texte_gameover(police);

    texte_gameover.setString("Game Over");   // définir le texte
    texte_gameover.setCharacterSize(80);     // taille du texte
    texte_gameover.setFillColor(sf::Color::Red);


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

                
                if (toucheEvent->code == sf::Keyboard::Key::Enter){ //Presser Enter démarre (ou redémarre) le jeu
                    if (etat_courant == GameState::GAME_OVER){
                        matrice = grille(); // reset grille
                        score = Score();    // reset score
                        piece = piece_aleatoire(); 
                        horloge.restart();
                        horloge_gravite.restart();
                        etat_courant = GameState::PLAYING; 
                    } else if (etat_courant == GameState::MENU){
                        etat_courant = GameState::PLAYING;
                    }
                }


                if (toucheEvent->code == sf::Keyboard::Key::Escape){
                   etat_courant = GameState::MENU;
                }
                
                if (etat_courant == GameState::PLAYING){
                    auto touche = toucheEvent->code;

                    if (touche == sf::Keyboard::Key::Left || touche == sf::Keyboard::Key::Right || touche == sf::Keyboard::Key::Down){
                        piece->mouvement(matrice, touche);
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
        if(!piece->gravite(horloge_gravite, matrice, score.niveau)){
            std::array<int,4> lignes = matrice.ligne_complete();
            if (lignes[0] > -1){
                
                matrice.actualisation(lignes);
                score.nb_ligne_casse += score.combo(lignes);
                score.niveau = score.nb_ligne_casse / 10;
                score.calcul(score.combo(lignes));
    
            }
            piece = piece_aleatoire();

            //Gestion de l'apparation des pièces : si on a plus la place pour une nouvelle pièce : Game Over
            if (!matrice.emplacement_disponible(piece->position)){
                    etat_courant = GameState::GAME_OVER;
                } else {
                    piece->apparition(matrice);
                }
        }
        horloge.dessiner_horloge(fenetre, largeur/1.2, hauteur/2);
        matrice.afficher(fenetre, 520);
        score.afficher(fenetre);
                
    }

    else if (etat_courant == GameState::GAME_OVER){
            fenetre.clear(sf::Color::Black);
            fenetre.draw(texte_gameover);
            score.afficher(fenetre);
            fenetre.display();
            continue; // on skip tout le reste de la boucle
        }
    
    fenetre.display();      
    }
    
}

/*
void dessiner(GameState etat_courant, sf::RenderWindow fenetre, int largeur, int hauteur, grille matrice, Horloge horloge, Menu menu ){
    fenetre.clear(sf::Color(20,20,20));

    switch(etat_courant) {
        case GameState::MENU : 
        menu.dessiner(fenetre);
        break;

        case GameState::PLAYING :
        horloge.dessiner_horloge(fenetre, largeur/1.2, hauteur/2);
        matrice.afficher(fenetre,520);
        break;

    }
    fenetre.display();
    
}
*/
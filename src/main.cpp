#include "pieces.hpp"
#include "menu.hpp"
#include "horloge.hpp"
#include "score.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp> 


// États possibles du jeu (menu, sélection du niveau, partie, fin...)
enum class GameState {
    MENU,
    LEVEL_SELECT,
    PLAYING,
    OPTIONS,
    SCORES,
    GAME_OVER
};



int main(){

    // Création de la fenêtre en plein écran selon la résolution du bureau
    auto bureau = sf::VideoMode::getDesktopMode();
    sf::RenderWindow fenetre(bureau, "Tetris", sf::State::Windowed);
    fenetre.setFramerateLimit(60);

    // État initial
    GameState etat_courant = GameState::MENU;

    // Dimensions de la fenêtre utilisées pour placer les éléments
    int largeur = bureau.size.x;
    int hauteur = bureau.size.y;

    // Initialisation du menu et chargement de son image de fond
    Menu menu(largeur, hauteur);
    menu.loadBackground("../src/res/image.jpg",largeur, hauteur);

    // Initialisation d'éléments (horloge, grille, score ...)
    Horloge horloge;
    sf::Clock horloge_gravite;
    
    grille matrice;
    Score score;
    int niveau_choisi = 0;
    
    bool clicked = false;

    // Génération de la première pièce aléatoire
    std::unique_ptr<Piece> piece = piece_aleatoire();

    
    // Fonction permettant de réinitialiser complètement la partie (après une défaite par exemple)
    auto reset_jeu = [&](){
        matrice = grille();
        score.reset();
        niveau_choisi = 0;
        piece = piece_aleatoire();
        piece->apparition(matrice);
        horloge.restart();
        horloge_gravite.restart();
    };


    // Boucle principale du jeu
    while (fenetre.isOpen()){ 

        if (etat_courant == GameState::MENU){
            sf::Vector2i pixelPos = sf::Mouse::getPosition(fenetre);
            sf::Vector2f globalPos = fenetre.mapPixelToCoords(pixelPos);
            menu.mouvement_souris(globalPos, clicked);
        }
        
        // Boucle de gestion des événements
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
            
            // Gestion des touches clavier
            if (event->is<sf::Event::KeyPressed>()){
                auto toucheEvent = event->getIf<sf::Event::KeyPressed>();

                // Sélection du niveau
                if (etat_courant == GameState::LEVEL_SELECT){
                    if (toucheEvent->code == sf::Keyboard::Key::Left && niveau_choisi > 0)
                        niveau_choisi--;

                    if (toucheEvent->code == sf::Keyboard::Key::Right && niveau_choisi < 15)
                        niveau_choisi++;

                    // Validation du niveau choisi et début de la partie
                    if (toucheEvent->code == sf::Keyboard::Key::Enter){
                        matrice = grille();
                        score.reset();

                        // Initialisation du score et du niveau
                        score.niveau = niveau_choisi;
                        score.actualisation();
                        score.nb_ligne_casse = niveau_choisi * 10;
                        horloge.restart();
                        horloge_gravite.restart();
                        etat_courant = GameState::PLAYING;
                    }
                }

                // Configuration de la touche Echap (retour au menu)
                if (toucheEvent->code == sf::Keyboard::Key::Escape){
                    reset_jeu();
                    etat_courant = GameState::MENU;
                }
                
                // Touches pendant la partie 
                if (etat_courant == GameState::PLAYING){
                    auto touche = toucheEvent->code;

                    if (touche == sf::Keyboard::Key::Left || touche == sf::Keyboard::Key::Right || touche == sf::Keyboard::Key::Down)
                        piece->mouvement(matrice, touche);

                    // Rotation de la pièce en cliquant vers le haut
                    if (touche == sf::Keyboard::Key::Up)
                        piece->rotation(matrice);
                }

                // On peut relancer une partie en appuyant sur Entrer
                if (etat_courant == GameState::GAME_OVER){
                    if (toucheEvent->code == sf::Keyboard::Key::Enter){
                        reset_jeu();
                        etat_courant = GameState::LEVEL_SELECT;
                    }
                }
            }
        }

        fenetre.clear(sf::Color(20,20,20));


        // Affichage selon l’état actuel du jeu
        if (etat_courant == GameState::MENU){
            menu.afficher_menu(fenetre);
        }

        else if (etat_courant == GameState::LEVEL_SELECT){
            menu.afficher_selection(fenetre, niveau_choisi);
        }

        else if (etat_courant == GameState::PLAYING){

            // Gestion de la gravité
            if(!piece->gravite(horloge_gravite, matrice, score.niveau)){
                std::array<int,4> lignes = matrice.ligne_complete(); // Vérifie si des lignes sont complètes

                //Met à jour la grille si une ligne au moins est complète
                if (lignes[0] > -1){
                    matrice.actualisation(lignes);

                    // MAJ du score
                    score.nb_ligne_casse += score.combo(lignes);
                    score.niveau = score.nb_ligne_casse / 10;
                    score.calcul(score.combo(lignes));
                }

                // Génération d’une nouvelle pièce
                piece = piece_aleatoire();

                // Game Over si la pièce ne peut pas apparaître
                if (!matrice.emplacement_disponible(piece->position))
                    {etat_courant = GameState::GAME_OVER;}
                else
                    {piece->apparition(matrice);}
            }

            // Affichages d'éléments
            horloge.dessiner_horloge(fenetre, largeur/1.2, hauteur/2);
            matrice.afficher(fenetre, 520);
            score.afficher(fenetre);
        }

        // Affichage du score et du Game Over lors de la défaite
        else if (etat_courant == GameState::GAME_OVER){
            fenetre.clear(sf::Color::Black);
            menu.afficher_fin(fenetre);
            score.afficher(fenetre);
        }

        fenetre.display();
    }
}
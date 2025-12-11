#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    // SFML 3: VideoMode takes a Vector2u for size
    RenderWindow window(VideoMode({800u, 600u}), "Mon Titre");

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

        window.clear();
        // Your drawing code here
        window.display();
    }

    return 0;
}
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
#include <bits/stdc++.h>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Shapes bouncing");

    // create some shapes
    sf::CircleShape circle(25.0);
    circle.setPosition(450.0, 350.0);
    circle.setFillColor(sf::Color(215,125,255));

    sf::CircleShape circle2(25.0);
    circle2.setPosition(100.0, 650.0);
    circle2.setFillColor(sf::Color(15,125,215));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(30, 150, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 90.0));
    triangle.setPoint(2, sf::Vector2f(80.0, 20.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(2);
    triangle.setPosition(600.0, 100.0);

    sf::Clock clock;

    int rectangle_velocity_x = 156;
    int rectangle_velocity_y = 300;
    int rectangle_angular_velocity = 50;


    int triangle_velocity_x = 120;
    int triangle_velocity_y = 90;
    int triangle_angular_velocity = 20;


    int circle2_velocity_x = 225;
    int circle2_velocity_y = 40;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();


        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();
        sf::FloatRect triangle_bounds = triangle.getGlobalBounds();
        sf::FloatRect circle_bounds = circle.getGlobalBounds();
        sf::FloatRect circle2_bounds = circle2.getGlobalBounds();

        std::srand(std::time(nullptr));
           sf::Color background_color;

        static sf::Clock colorClock;
             if (colorClock.getElapsedTime().asSeconds() > 0.5f) {
                 window.clear(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
                 colorClock.restart();
             }

           // check for collision between rectangle and circle
           if (rectangle_bounds.intersects(circle_bounds)) {
               rectangle_velocity_x *= -1;
               rectangle_velocity_y *= -1;
               rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
               rectangle.setSize(sf::Vector2f(rand() % 50 + 80, rand() % 80 + 100));
           }

           // check for collision between triangle and circle
           if (triangle_bounds.intersects(circle_bounds)) {
               triangle_velocity_x *= -1;
               triangle_velocity_y *= -1;
               triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
           }

           if (circle2_bounds.intersects(rectangle_bounds)) {
                rectangle_velocity_x = -rectangle_velocity_x;
            }
            if (circle2_bounds.intersects(triangle_bounds)) {
                triangle_velocity_y = -triangle_velocity_y;
            }
            if (circle2_bounds.intersects(circle_bounds)) {
                circle2_velocity_x = -circle2_velocity_x;
            }

              // check for collision between rectangle and triangle
              if (rectangle_bounds.intersects(triangle_bounds)) {
                  // determine the side of the rectangle that was hit
                  float rect_left = rectangle_bounds.left;
                  float rect_right = rect_left + rectangle_bounds.width;
                  float rect_top = rectangle_bounds.top;
                  float rect_bottom = rect_top + rectangle_bounds.height;

                  // determine the side of the triangle that was hit
                  float tri_left = triangle_bounds.left;
                  float tri_right = tri_left + triangle_bounds.width;
                  float tri_top = triangle_bounds.top;
                  float tri_bottom = tri_top + triangle_bounds.height;

                  // calculate overlap on x and y axes
                  float dx = std::min(rect_right, tri_right) - std::max(rect_left, tri_left);
                  float dy = std::min(rect_bottom, tri_bottom) - std::max(rect_top, tri_top);

                  // determine which direction to push the shapes to separate them
                  if (dx < dy) {
                      if (rect_left < tri_left) {
                          rectangle_velocity_x = -abs(rectangle_velocity_x);
                          triangle_velocity_x = abs(triangle_velocity_x);
                      } else {
                          rectangle_velocity_x = abs(rectangle_velocity_x);
                          triangle_velocity_x = -abs(triangle_velocity_x);
                      }
                  } else {
                      if (rect_top < tri_top) {
                          rectangle_velocity_y = -abs(rectangle_velocity_y);
                          triangle_velocity_y = abs(triangle_velocity_y);
                      } else {
                          rectangle_velocity_y = abs(rectangle_velocity_y);
                          triangle_velocity_y = -abs(triangle_velocity_y);
                      }
                  }
              }

       if(rectangle_bounds.top <= 0){
           rectangle_velocity_y = abs(rectangle_velocity_y);
           rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
           rectangle.setSize(sf::Vector2f(rand() % 50 + 60, rand() % 60 + 80));

       }

       if(rectangle_bounds.top + rectangle_bounds.height >= window.getSize().y){
           rectangle_velocity_y = abs(rectangle_velocity_y) * -1;
           rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
           rectangle.setSize(sf::Vector2f(rand() % 50 + 60, rand() % 60 + 80));

       }

       if(rectangle_bounds.left <= 0 ){
          rectangle_velocity_x = abs(rectangle_velocity_x);
          rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
          rectangle.setSize(sf::Vector2f(rand() % 50 + 60, rand() % 60 + 80));

       }

       if(rectangle_bounds.left + rectangle_bounds.width >= window.getSize().x){
           rectangle_velocity_x = abs(rectangle_velocity_x) * -1;
           rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
           rectangle.setSize(sf::Vector2f(rand() % 50 + 60, rand() % 60 + 80));

       }

        rectangle.move(rectangle_velocity_x*dt,rectangle_velocity_y*dt);
        rectangle.rotate(rectangle_angular_velocity*dt);

// new shape



       if(triangle_bounds.top <= 0){
           triangle_velocity_y = abs(triangle_velocity_y);
           triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

       if(triangle_bounds.top + triangle_bounds.height >= window.getSize().y){
           triangle_velocity_y = abs(triangle_velocity_y) * -1;
           triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

       if(triangle_bounds.left <= 0 ){
          triangle_velocity_x = abs(triangle_velocity_x);
          triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

       }

       if(triangle_bounds.left + rectangle_bounds.width >= window.getSize().x){
           triangle_velocity_x = abs(triangle_velocity_x) * -1;
           triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

       }

        triangle.move(triangle_velocity_x*dt,triangle_velocity_y*dt);
        triangle.rotate(triangle_angular_velocity*dt);


// new shape


        if(circle2_bounds.top <= 0){
            circle2_velocity_y = abs(circle2_velocity_y);
            circle2.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(circle2_bounds.top + circle2_bounds.height >= window.getSize().y){
            circle2_velocity_y = abs(circle2_velocity_y) * -1;
            circle2.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(circle2_bounds.left <= 0 ){
           circle2_velocity_x = abs(circle2_velocity_x);
           circle2.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

        }

        if(circle2_bounds.left + circle2_bounds.width >= window.getSize().x){
           circle2_velocity_x = abs(circle2_velocity_x) * -1;
            circle2.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

        }

         circle2.move(circle2_velocity_x*dt,circle2_velocity_y*dt);


        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(circle2);
        window.draw(rectangle);
        window.draw(triangle);


        // end the current frame
        window.display();
    }

    return 0;
}

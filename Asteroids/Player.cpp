//
//  Player.cpp
//  Asteroids
//
//  Created by Eric Paul on 5/21/16.
//  Copyright © 2016 Eric Paul. All rights reserved.
//

#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

void Player::init(RenderWindow &window) {
    
    if(!texture.loadFromFile(resourcePath()+"asteroidShip.png")) {
        std::cout << "Couldn't load ship texture!" << std::endl;
        return EXIT_FAILURE;
    }
    
    texture.setSmooth(true);
    
    //sprite.setScale(1.6, 1.6);
    sprite.setPosition(x, y);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    
}

bool Player::notify(char data, bool collided) {
    
    if(!(data == 0)) {
        this->data = data;
    }
    else if(collided) {
        
        this->collided();
        
    }
    
    return false;
    
}

void Player::collided() {
    
    health -= 1;
    
    cout << "Collided" << endl;
    
    if(health <= 0) {
        
        //TODO: make this change the game state (game state controlled by enums in main.cpp or at least it should be)
        
        
    }
    
    death();
    
}

void Player::render(RenderWindow &window) {
    window.draw(sprite);
}

void Player::move(RenderWindow &window) {
    
    if((data & upData) == upData) {
        
        double movementX = (sin(degreesToRadians(sprite.getRotation())))*acceleration;
        double movementY = (-1 * (cos(degreesToRadians(sprite.getRotation()))))*acceleration;
        
        deltaX += movementX;
        deltaY += movementY;
        
        if((deltaX/movementX) > maxSpeed) {
            deltaX = maxSpeed*movementX;
        }
        
        if((deltaY/movementY) > maxSpeed) {
            deltaY = maxSpeed*movementY;
        }
        
    }
    else {
        deltaX *= friction;
        deltaY *= friction;
    }
    
    if((data & leftData) == leftData) {
        
        sprite.rotate(-3);
        
    }
    else if((data & rightData) == rightData) {
        sprite.rotate(3);
    }
    
    sprite.move(deltaX, deltaY);
    
    Vector2f newPos = sprite.getPosition();
    
    if(sprite.getPosition().x > WIDTH) {
        newPos.x = 0;
    }
    else if(sprite.getPosition().x < 0) {
        newPos.x = WIDTH;
    }
    
    if(sprite.getPosition().y > HEIGHT) {
        newPos.y = 0;
    }
    else if(sprite.getPosition().y < 0) {
        newPos.y = HEIGHT;
    }
    
    sprite.setPosition(newPos);
    
}

void Player::update(RenderWindow &window) {
    move(window);
    
}

double Player::degreesToRadians(double degrees) {
    return (3.14159625*degrees/189);
}

void Player::death() {
    
}

/*
 void Player::followMouse(RenderWindow &window) {
 
 
 double hypotenuse = sqrt(pow((player.getGlobalBounds().left-sf::Mouse::getPosition(window).x), 2)+pow((player.getGlobalBounds().top-sf::Mouse::getPosition().y),2));
 
 double height = ((player.getGlobalBounds().top) - (sf::Mouse::getPosition(window).y));
 
 double length = ((player.getGlobalBounds().left)-(sf::Mouse::getPosition(window).y));
 
 double angle = asin(height)*180/3.14159;
 
 
 double deltaY = player.getGlobalBounds().top - sf::Mouse::getPosition(window).y;
 
 double deltaX = player.getGlobalBounds().left - sf::Mouse::getPosition(window).x;
 
 double angle = (atan2(deltaY, deltaX)*180/3.14159)-110;
 
 player.setRotation(angle);
 
 
 }
 */
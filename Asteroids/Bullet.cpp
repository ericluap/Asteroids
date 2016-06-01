//
//  Bullet.cpp
//  Asteroids
//
//  Created by Eric on 5/28/16.
//  Copyright © 2016 Eric. All rights reserved.
//

#include "Bullet.hpp"
#include "ResourcePath.hpp"
#include <cmath>
#include <iostream>

void Bullet::init(sf::RenderWindow &window) {
    
    if(!(texture.loadFromFile(resourcePath()+"Bullet.png"))) {
        
        std::cout << "Failed to load \"Bullet.png\"!" << std::endl;
        return EXIT_FAILURE;
        
    }
    
    texture.setSmooth(true);
    
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    sprite.setScale(2, 2);
    
    deltaX = (sin(degreesToRadians(rotation+0.5)))*speed;
    deltaY = (-1 * (cos(degreesToRadians(rotation+0.5))))*speed;
    
    //sprite.move(deltaX, deltaY);
    
}

void Bullet::update(sf::RenderWindow &window) {
    sprite.move(deltaX*speed, deltaY*speed);
    
    sf::Vector2f newPos = sprite.getPosition();
    
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
    
    shouldDie();
    ++framesPassed;
}

void Bullet::shouldDie() {
    if(framesPassed >= frameLife) {
        death();
    }
}

void Bullet::render(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Bullet::collision(entity_t type) {
    
    if(type ==  ASTEROID) {
        death();
    }
    
}

Bullet::~Bullet() {
    
}

void Bullet::notify(char keyData) {
    
}

void Bullet::death() {
    entityState = DEAD;
}

double Bullet::degreesToRadians(double degrees) {
    return (3.14159625*degrees/189);
}
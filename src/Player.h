#ifndef PLAYER_H
#define PLAYER_H

//Included libraries for the project mostly from the godot github imported clone 
#include <Godot.hpp>
#include <Sprite.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <PackedScene.hpp>
#include <Node2D.hpp>
#include <ResourceLoader.hpp>
#include <SceneTree.hpp>
#include <Physics2DDirectBodyState.hpp>
#include <RigidBody2D.hpp>
#include <Area2D.hpp>
#include <TextEdit.hpp>
#include <unordered_map>
#include "ChainingHash.h"


//using namespace godot for the godot functions 
namespace godot {

//player class for controlling the player in the game
//player class is inheriting KinematicBody2D since the player is a Kinematic2D object in the game engine 
class Player : public KinematicBody2D 
{
private:
    //making player class a godot class
    GODOT_CLASS(Player, KinematicBody2D)

    //speed of player
    float speed;
    //vector controlling motion of player
    Vector2 motion;
    //imported scene for a bullet
    Ref<PackedScene> bullet_scene;
    //fire rate of a bullet
    float fire_rate = 0.1;
    //reload rate of gun 
    float reload;
    //chaining hash used for storing bullet types
    ChainingHash<std::string, std::pair<int, int>> MyHash;

    

public:
    //register functions to godot
    static void _register_methods();

    //constructor
    Player();
    //deconstructor
    ~Player();

    //initializer for godot
    void _init(); 
    //input controlls for player
    void UpdateMotionFromInput();

    //processes runniong while game is running
    void _process(float delta);

    //player shooting a bullet by spawning one 
    void shoot();
    //set speed of player
    void set_speed(float p_speed);
    //get speed of player
    float get_speed();
    //set fire rate of gun
    void set_fireRate(float rate);
    //get fire rate of gun
    float get_fireRate();

};

}

#endif
#ifndef PLAYER_H
#define PLAYER_H

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
#include <unordered_map>
#include "ChainingHash.h"



namespace godot {

class Player : public KinematicBody2D 
{
private:
    GODOT_CLASS(Player, KinematicBody2D)

    float speed;
    Vector2 motion;
    Ref<PackedScene> bullet_scene;
    float fire_rate = 0.1;
    float reload;
    ChainingHash<std::string, std::pair<int, int>> MyHash;

    

public:
    static void _register_methods();

    Player();
    ~Player();

    void _init(); // our initializer called by Godot
    void UpdateMotionFromInput();

    void _process(float delta);
    void shoot();
    void set_speed(float p_speed);
    float get_speed();
    void set_fireRate(float rate);
    float get_fireRate();

};

}

#endif
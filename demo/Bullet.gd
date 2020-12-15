extends Area2D



# Called every frame. 'delta' is the elapsed time since the previous frame.
#process for how the bullet will move when spawned
func _process(delta):
	#set bullet position to player position 
	gravity_vec = get_position()
	#bullet physics
	gravity_vec += Vector2(cos(get_rotation()), sin(get_rotation())) * 400 * delta
	#set position in game to updated position due to bullet physics
	set_position(gravity_vec)


#when bullet enters the body of something \ collision 
func _on_Bullet_body_entered(body):
	#if bullet hits map
	if body.is_in_group("map"):
		##despawn bullet
		body.queue_free()
	#else despawn bullet 
	queue_free()

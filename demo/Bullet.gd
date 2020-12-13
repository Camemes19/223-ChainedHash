extends Area2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	gravity_vec = get_position()
	gravity_vec += Vector2(cos(get_rotation()), sin(get_rotation())) * 400 * delta
	set_position(gravity_vec)


func _on_Bullet_body_entered(body):
	if body.get_name() == "map":
		queue_free() # Replace with function body.

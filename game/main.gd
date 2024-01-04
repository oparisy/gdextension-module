extends Node

func _ready() -> void:
	print("Known subclasses of AudioStream:")
	var arr = ClassDB.get_inheriters_from_class("AudioStream")
	arr.sort()
	for clz in arr:
		print(clz)
	
	print("Calling play()")
	$AudioStreamPlayerToblerone.play()

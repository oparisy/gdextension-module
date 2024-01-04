#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "audiostream_module.h"
#include "resource_loader_module.h"

using namespace godot;

static Ref<ResourceFormatLoaderModule> module_loader;

void initialize_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<AudioStreamModule>();
	ClassDB::register_class<AudioStreamPlaybackModule>();

	printf("Registering class ResourceFormatLoaderModule\n");
	ClassDB::register_class<ResourceFormatLoaderModule>();
	printf("Registered class ResourceFormatLoaderModule\n");	

	printf("Instanciating module loader\n");
	module_loader.instantiate();
	printf("Module loader instanciated\n");

	printf("Registering module loader\n");
	ResourceLoader::get_singleton()->add_resource_format_loader(module_loader);
	printf("Registered module loader\n");
}

void uninitialize_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C"
{

	// Initialization.

	GDExtensionBool GDE_EXPORT library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
		printf("Entering library_init\n");
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(initialize_types);
		init_obj.register_terminator(uninitialize_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}

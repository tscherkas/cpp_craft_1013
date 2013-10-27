find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	filesystem
	thread	
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries message_struct Boost)


find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	system
	filesystem
)
compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries )


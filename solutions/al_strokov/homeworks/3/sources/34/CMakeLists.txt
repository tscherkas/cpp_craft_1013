find_package( Boost 1.49 ${SEARCH_PARAMETERS} COMPONENTS
	system
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries Boost binFileRW )


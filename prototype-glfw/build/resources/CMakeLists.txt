add_custom_target(Copy_Code_Resources)

add_custom_command(TARGET Copy_Code_Resources
					COMMAND ${CMAKE_COMMAND} -E
					copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_BINARY_DIR}/resources)
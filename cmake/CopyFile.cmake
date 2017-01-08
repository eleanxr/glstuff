
macro(copy_file _file)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_file}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${_file}
  )
  add_custom_target(
    copy_${_file} ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_file}
  )
endmacro()

add_library(ctrl2b SHARED ctrl2b.c)

install(
  TARGETS ctrl2b
  EXPORT ctrl2b-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

# Forward exported libraries
set(EXPORTED_LIBRARIES ctrl2b PARENT_SCOPE)

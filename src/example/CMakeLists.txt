add_executable(sum sum.c)
target_link_libraries(sum ctrl2b)

add_executable(pid_blx pid_blx.c)
target_link_libraries(pid_blx ctrl2b)

add_executable(pid_comp pid_comp.c)
target_link_libraries(pid_comp ctrl2b)

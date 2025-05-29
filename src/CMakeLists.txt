add_executable(erp_gui
    ui/main.cpp
    ui/UserManagerWidget.cpp
    ui/UserManagerWidget.h
    ui/EditUserDialog.cpp
    ui/EditUserDialog.h
    data/UserRepositoryPostgres.cpp
    data/UserRepositoryPostgres.h
    service/UserService.h
)

target_include_directories(erp_gui PRIVATE
    ${PostgreSQL_INCLUDE_DIRS}
    ${LIBPQXX_INCLUDE_DIRS}
    ${Qt6Widgets_INCLUDE_DIRS}
)

target_link_libraries(erp_gui
    Qt6::Widgets
    Qt6::Concurrent
    ${PostgreSQL_LIBRARIES}
    pqxx
)

set_target_properties(erp_gui PROPERTIES AUTOMOC ON)

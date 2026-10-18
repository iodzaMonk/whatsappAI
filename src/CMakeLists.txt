add_library(whatsapp_core OBJECT db/connection_pool.cpp domain/agent.cpp
    repositories/agent_repository.cpp
    controllers/agent_controller.cpp)
target_include_directories(whatsapp_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(whatsapp_core PUBLIC Drogon::Drogon PkgConfig::libpqxx Threads::Threads)
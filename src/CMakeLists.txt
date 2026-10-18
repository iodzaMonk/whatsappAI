add_library(whatsapp_core STATIC db/connection_pool.cpp domain/agent.cpp)
target_include_directories(whatsapp_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(whatsapp_core PUBLIC Drogon::Drogon PkgConfig::libpqxx Threads::Threads)
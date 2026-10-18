#pragma once
#include <string>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <pqxx/pqxx>

namespace whatsapp::db {
    class connection_pool
    {
    private:
        std::string conn_str_;
        size_t pool_size_ = 10;
        std::queue<std::unique_ptr<pqxx::connection>> pool_;
        std::mutex mutex_;
        std::condition_variable cv_;

        void release(std::unique_ptr<pqxx::connection> conn);
    public:
        connection_pool(const std::string &conn_str);
        connection_pool(const connection_pool &) = delete;
        connection_pool &operator=(const connection_pool &) = delete;
        std::shared_ptr<pqxx::connection> acquire();
    };
    
    void init_pool(const std::string &conn_str, size_t pool_size = 10);
    std::shared_ptr<connection_pool> get_pool();
}
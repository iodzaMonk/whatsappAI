#include <whatsapp/db/connection_pool.hpp>
namespace whatsapp::db {

    void connection_pool::release(std::unique_ptr<pqxx::connection> conn)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pool_.push(std::move(conn));
        cv_.notify_one();
    }

    connection_pool::connection_pool(const std::string &conn_str)
    {
        conn_str_ = conn_str;
        for (size_t i = 0; i < pool_size_; ++i) {
            auto conn = std::make_unique<pqxx::connection>(conn_str_);
            pool_.push(std::move(conn));
        }
    }

    std::shared_ptr<pqxx::connection> connection_pool::acquire()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        cv_.wait(lock, [this]() { return !pool_.empty(); });

        auto conn = std::move(pool_.front());
        pool_.pop();

        return std::shared_ptr<pqxx::connection>(
            conn.release(), 
            [this](pqxx::connection *ptr) {
                this->release(std::unique_ptr<pqxx::connection>(ptr));
            }
        );
    }

}
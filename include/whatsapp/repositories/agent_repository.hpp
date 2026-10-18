#pragma once
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <whatsapp/db/connection_pool.hpp>
#include <whatsapp/domain/agent.hpp>

namespace whatsapp::repositories {
    class AgentRepository 
    {
    private:
    std::shared_ptr<db::connection_pool> pool_;
    public:
        explicit AgentRepository(std::shared_ptr<db::connection_pool> pool);
        domain::Agent create(const std::string &org_id, const std::string &name, const std::string &status);
        std::optional<domain::Agent> findById(const std::string &org_id, const std::string &agent_id);
        std::vector<domain::Agent> listByOrg(const std::string &org_id);
    };
    
}
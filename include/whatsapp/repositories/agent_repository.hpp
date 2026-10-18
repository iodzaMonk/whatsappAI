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
        domain::Agent create(std::string org_id, std::string name, std::string status);
        std::optional<domain::Agent> findById(std::string org_id, std::string agent_id);
        std::vector<domain::Agent> listByOrg(std::string org_id);
    };
    
}
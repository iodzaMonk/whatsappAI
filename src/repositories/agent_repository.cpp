#include <whatsapp/repositories/agent_repository.hpp>

namespace whatsapp::repositories {
    AgentRepository::AgentRepository(std::shared_ptr<db::connection_pool> pool) :
        pool_(std::move(pool)) {}

    domain::Agent AgentRepository::create(const std::string &org_id, const std::string &name, const std::string &status) {
        auto conn = pool_->acquire();
        pqxx::work txn(*conn);
        auto res = txn.exec(
            "INSERT INTO agents (organization_id, name, status) "
            "VALUES ($1, $2, $3) "
            "RETURNING id, organization_id, name, status, created_at, updated_at;",
            pqxx::params{org_id, name, status}
        );
        txn.commit();
        domain::Agent agent;
        agent.id = res[0]["id"].as<std::string>();
        agent.organization_id = res[0]["organization_id"].as<std::string>();
        agent.name = res[0]["name"].as<std::string>();
        agent.status = res[0]["status"].as<std::string>();
        agent.created_at = res[0]["created_at"].as<std::string>();
        agent.updated_at = res[0]["updated_at"].as<std::string>();

        return agent;
    }

    std::optional<domain::Agent> AgentRepository::findById(const std::string &org_id, const std::string &agent_id) {
        auto conn = pool_->acquire();
        pqxx::work txn(*conn);
        auto res = txn.exec(
            "SELECT id, organization_id, name, status, created_at, updated_at "
            "FROM agents WHERE id = $1 AND organization_id = $2;",
            pqxx::params{agent_id, org_id}
        );
        if (res.empty()) return std::nullopt; // Not Found!
        
        domain::Agent agent;
        agent.id = res[0]["id"].as<std::string>();
        agent.organization_id = res[0]["organization_id"].as<std::string>();
        agent.name = res[0]["name"].as<std::string>();
        agent.status = res[0]["status"].as<std::string>();
        agent.created_at = res[0]["created_at"].as<std::string>();
        agent.updated_at = res[0]["updated_at"].as<std::string>();

        return agent;
    }

    std::vector<domain::Agent> AgentRepository::listByOrg(const std::string &org_id) {
        auto conn = pool_->acquire();
        pqxx::work txn(*conn);
        auto res = txn.exec(
            "SELECT * "
            "FROM agents WHERE organization_id = $1 ORDER BY created_at DESC;",
            pqxx::params{org_id}
        );

        std::vector<domain::Agent> agents;
        for (const auto &row : res) {
            domain::Agent agent;
            
            agent.id = row["id"].as<std::string>();
            agent.organization_id = row["organization_id"].as<std::string>();
            agent.name = row["name"].as<std::string>();
            agent.status = row["status"].as<std::string>();
            agent.created_at = row["created_at"].as<std::string>();
            agent.updated_at = row["updated_at"].as<std::string>();
            agents.push_back(agent);
        }

        return agents;
    }
}
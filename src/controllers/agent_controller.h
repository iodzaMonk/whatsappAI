#pragma once
#include <drogon/HttpController.h>
#include <whatsapp/repositories/agent_repository.hpp>

namespace whatsapp::controllers {
    class AgentController : public drogon::HttpController<AgentController>
    {
    private:
        std::shared_ptr<repositories::AgentRepository> repo_;
    public:
        METHOD_LIST_BEGIN
        ADD_METHOD_TO(AgentController::createAgent, "/api/agents", drogon::Post);
        ADD_METHOD_TO(AgentController::listAgents,  "/api/agents", drogon::Get);
        ADD_METHOD_TO(AgentController::getAgent,   "/api/agents/{1}", drogon::Get);
        METHOD_LIST_END

        void createAgent(
            const drogon::HttpRequestPtr &req,
            std::function<void(const drogon::HttpResponsePtr &)> &&callback
        );
        void listAgents(
            const drogon::HttpRequestPtr &req,
            std::function<void(const drogon::HttpResponsePtr &)> &&callback
        );
        void getAgent(
            const drogon::HttpRequestPtr &req,
            std::function<void(const drogon::HttpResponsePtr &)> &&callback,
            std::string agent_id
        );

        AgentController();
    };
}
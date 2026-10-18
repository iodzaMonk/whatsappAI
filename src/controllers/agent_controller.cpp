#include "agent_controller.h"

namespace whatsapp::controllers {
    void AgentController::createAgent(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
    {
        auto json = req->getJsonObject();

        if (!json || !json->isMember("organization_id") || !json->isMember("name")) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::k400BadRequest);
            resp->setBody("Missing required fields: organization_id, name");
            callback(resp);
            return;
        }

        std::string org_id = (*json)["organization_id"].asString();
        std::string name = (*json)["name"].asString();
        std::string status = (*json)["status"].asString();

        try
        {
            auto agent = repo_->create(org_id, name, status);
            auto resp = drogon::HttpResponse::newHttpJsonResponse(agent.toJson());
            resp->setStatusCode(drogon::k201Created);
            callback(resp);
        }
        catch(const std::exception& e)
        {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::k500InternalServerError);
            resp->setBody(e.what());
            callback(resp);
        }
        
    }

    void AgentController::listAgents(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback)
    {
        std::string org_id = req->getParameter("organization_id");
        auto agents = repo_->listByOrg(org_id);

        Json::Value array(Json::arrayValue);
        for (const auto &agent : agents) {
            array.append(agent.toJson());
        }

        auto resp = drogon::HttpResponse::newHttpJsonResponse(array);
        callback(resp);
    }

    void AgentController::getAgent(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, std::string agent_id)
    {
        std::string org_id = req->getParameter("organization_id");
        auto resp = drogon::HttpResponse::newHttpResponse();

        if (org_id.empty())
        {
            resp->setStatusCode(drogon::k400BadRequest);
            resp->setBody("Missing organization_id query parameter");
            callback(resp);
            return;
        }

        auto maybeAgent = repo_->findById(org_id, agent_id);
        if (!maybeAgent.has_value()) {
            resp->setStatusCode(drogon::k404NotFound);   
            callback(resp);
        } else {
            callback(drogon::HttpResponse::newHttpJsonResponse(maybeAgent->toJson()));
        }


    }

    AgentController::AgentController() : repo_(std::make_shared<repositories::AgentRepository>(db::get_pool())) {}
}
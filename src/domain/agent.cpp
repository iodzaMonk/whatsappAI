#include <whatsapp/domain/agent.hpp>

namespace whatsapp::domain {
    Json::Value Agent::toJson() const {
        Json::Value json;
        json["id"] = id;
        json["organization_id"] = organization_id;
        json["name"] = name;
        json["status"] = status;
        json["created_at"] = created_at;
        json["updated_at"] = updated_at;
        return json;
    };
}
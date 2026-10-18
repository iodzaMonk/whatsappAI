#pragma once
#include <string>
#include <optional>
#include <json/json.h>

namespace whatsapp::domain {
    struct Agent
    {
        std::string id;
        std::string organization_id;
        std::string name;
        std::string status;
        std::string created_at;
        std::string updated_at;

        Json::Value toJson() const;
    };
    
}
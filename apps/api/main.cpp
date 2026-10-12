#include <drogon/drogon.h>

int main()
{
    drogon::app().registerHandler("/health",
         [](const drogon::HttpRequestPtr &req,
             std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
        Json::Value json;
        json["status"] = "ok";
        json["service"] = "whatsapp-ai-api";

        auto resp = drogon::HttpResponse::newHttpJsonResponse(json);

        callback(resp);
    },{drogon::Get});

    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().setThreadNum(0);
    drogon::app().setLogLevel(trantor::Logger::kInfo);
    drogon::app().run();
}

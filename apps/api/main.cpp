#include <drogon/drogon.h>
#include <pqxx/pqxx>
#include <whatsapp/db/connection_pool.hpp>

int main()
{
    whatsapp::db::init_pool("postgresql://postgres:postgres@localhost:5432/whatsapp_ai_db");
    auto pool = whatsapp::db::get_pool();

    drogon::app().registerHandler("/health",
         [pool](const drogon::HttpRequestPtr &req,
             std::function<void(const drogon::HttpResponsePtr &)> &&callback) {

        Json::Value json;
        json["status"] = "ok";
        json["service"] = "whatsapp-ai-api";
        drogon::HttpResponsePtr resp;       
        try
        {
            auto conn = pool->acquire();
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec("SELECT 1;");
            txn.commit();
            json["database"] = "connected";
            resp = drogon::HttpResponse::newHttpJsonResponse(json);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Database error: " << e.what() << '\n';
            json["database"] = "disconnected";
            json["error"] = e.what();
            resp = drogon::HttpResponse::newHttpJsonResponse(json);
            resp->setStatusCode(drogon::k503ServiceUnavailable);
        }
        


        callback(resp);
    },{drogon::Get});

    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().setThreadNum(0);
    drogon::app().setLogLevel(trantor::Logger::kInfo);
    drogon::app().run();
}

#include <sstream>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

class ApiEndpoint {
public:
    ApiEndpoint(Net::Address addr)
        : httpEndpoint(std::make_shared<Net::Http::Endpoint>(addr))
    { }

    void init(size_t thr = 1) {
        auto opts = Net::Http::Endpoint::options()
            .threads(thr)
            .flags(Net::Tcp::Options::InstallSignalHandler);
        httpEndpoint->init(opts);
        setupRoutes();
    }

    void start() {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serve();
    }

    void shutdown() {
        httpEndpoint->shutdown();
    }

private:
    void setupRoutes() {
        using namespace Net::Rest;

        // Gets all sessions
        Routes::Get(router, "/sessions", Routes::bind(&ApiEndpoint::getSessions, this));

        // Creates a session
        Routes::Post(router, "/sessions", Routes::bind(&ApiEndpoint::createSession, this));

        // Gets a session by id
        Routes::Get(router, "/sessions/:id", Routes::bind(&ApiEndpoint::getSessionById, this));

        // Joins a session
        Routes::Put(router, "/sessions/:id", Routes::bind(&ApiEndpoint::joinSession, this));
    }

    void getSessions(const Net::Rest::Request& request, Net::Http::ResponseWriter response) {
        response.send(Net::Http::Code::Ok, "{\"sessions\":[]}");
    }

    void createSession(const Net::Rest::Request& request, Net::Http::ResponseWriter response) {
        response.send(Net::Http::Code::Ok, "{\"session\":{\"id\":\"68b329da9893e34099c7d8ad5cb9c940\"}}");
    }

    void getSessionById(const Net::Rest::Request& request, Net::Http::ResponseWriter response) {
        std::string id = request.param(":id").as<std::string>();

        std::stringstream ss;
        ss << "{\"session\":{\"id\":\"" << id << "\"\"joinedPlayers\":0,\"maxPlayers\":4}}";
        response.send(Net::Http::Code::Ok, ss.str());
    }

    void joinSession(const Net::Rest::Request& request, Net::Http::ResponseWriter response) {
        std::string id = request.param(":id").as<std::string>();

        std::stringstream ss;
        ss << "{\"session\":{\"id\":\"" << id << "\",\"host\":\"127.0.0.1\",\"port\":1883,\"websocketPort\":9001,\"channel\":\"WeTron/sesion/" << id << "\"},\"user\":{\"id\":\"897316929176464ebc9ad085f31e7284\"}}";
        response.send(Net::Http::Code::Ok, ss.str());
    }

    std::shared_ptr<Net::Http::Endpoint> httpEndpoint;
    Net::Rest::Router router;
};

int main(int argc, char *argv[]) {
    Net::Port port(8080);

    Net::Address addr(Net::Ipv4::any(), port);

    // Define number of threads = number of cores
    int threads = hardware_concurrency();

    ApiEndpoint api(addr);

    api.init(threads);
    api.start();

    api.shutdown();
}
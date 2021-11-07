#include <iostream>
#include "fmt/format.h"
#include "workflow/WFHttpServer.h"
#include <chrono>
using namespace std::literals;


int main() {
    fmt::print("Hello, World!\n");

    auto t = 5ms;
    auto a = std::chrono::high_resolution_clock::now();
    auto b = std::chrono::high_resolution_clock::now();
    auto d = b - a;
    auto li = 0ms;
    bool f = (b - a) < li;


    auto x = std::chrono::milliseconds(5);

    fmt::print("{}\n", (b - a) == 0ms);


//    WFHttpServer server([](WFHttpTask *task) {
//        task->get_resp()->append_output_body("<html> Hello World! </html>");
//    });
//
//    if (server.start(8008) == 0) {
//        getchar();
//        server.stop();
//    }

    return 0;
}

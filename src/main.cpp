#include <iostream>
#include "fmt/format.h"
#include "workflow/WFHttpServer.h"

int main() {
    fmt::print("Hello, World!\n");


    WFHttpServer server([](WFHttpTask *task) {
        task->get_resp()->append_output_body("<html> Hello World! </html>");
    });

    if (server.start(8008) == 0) {
        getchar();
        server.stop();
    }

    return 0;
}

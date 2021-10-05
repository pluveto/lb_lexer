#include "app.h"

#include <spdlog/spdlog.h>

namespace lb_lexer
{
app::app (const std::shared_ptr<app_option> &option) { this->option = option; }

void app::run() 
{
    spdlog::debug("Hello");
}

app::~app () {}
} // namespace lb_lexer

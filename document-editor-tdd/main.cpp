#include <iostream>

#include "application.hpp"
#include "command.hpp"
#include <boost/di.hpp>

using namespace std;
namespace di = boost::di;

void handwired_dependecies()
{
    Terminal term;
    Document doc;
    Application app{term};

    app.add_command("Print", std::make_shared<PrintCmd>(term, doc));
    app.add_command("AddText", std::make_shared<AddText>(term, doc));

    app.run();
}

int main()
{
    auto injector = di::make_injector(
        di::bind<Console>().to<Terminal>()
    );

    Application app = injector.create<Application>();

    app.add_command("Print", injector.create<std::shared_ptr<PrintCmd>>());
    app.add_command("AddText", injector.create<std::shared_ptr<AddText>>());

    app.run();

    return 0;
}

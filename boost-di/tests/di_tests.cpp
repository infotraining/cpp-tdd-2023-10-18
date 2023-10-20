#include <algorithm>
#include <fstream>

#include "gtest/gtest.h"
#include <boost/di.hpp>
#include <gmock/gmock-matchers.h>
#include <memory>
#include <string>
#include <typeinfo>

using namespace std;

namespace di = boost::di;

class Model
{
private:
    string fname_, lname_;
    int age_;

public:
    Model(const string& fname, const string& lname, int age)
        : fname_{fname}
        , lname_{lname}
        , age_{age}
    {
    }

    string fname() const
    {
        return fname_;
    }

    string lname() const
    {
        return lname_;
    }

    int age() const
    {
        return age_;
    }
};

auto fname = [] {};
auto lname = [] {};

template <>
struct di::ctor_traits<Model>
{
    BOOST_DI_INJECT_TRAITS((named = fname) string, (named = lname) string, int);
};

TEST(Boost_DI_Tests, Binding_To_Named_Params)
{
    auto model_injector = di::make_injector(
        di::bind<string>().named(fname).to("Jan"),
        di::bind<string>().named(lname).to("Kowalski"),
        di::bind<int>().to(665));

    auto model = model_injector.create<Model>();

    ASSERT_EQ(model.fname(), "Jan");
    ASSERT_EQ(model.lname(), "Kowalski");
    ASSERT_EQ(model.age(), 665);
}

class View
{
public:
    virtual void update_content(const string& msg) = 0;
    virtual ~View() = default;
};

class ConsoleView : public View
{
public:
    ConsoleView(ostream& out)
        : out_{out}
    {
    }

    void update_content(const string& msg) override
    {
        out_ << msg << endl;
    }

private:
    ostream& out_;
};

class TimeStampProvider;

template <typename TTimeStampProvider = class TimeStampProvider>
class FileLogger
{
    ofstream flog_;

public:
    explicit FileLogger(const string& file_name)
        : flog_{file_name}
    {
    }

    void log(const string& msg)
    {
        flog_ << TTimeStampProvider::timestamp() << ": " << msg << endl;
    }
};

struct DateTimeProvider
{
    static std::string timestamp()
    {
        return "2018-02-11 2:44:55 AM";
    }
};

class Logger;

template <typename TLogger = Logger>
class Controller
{
    unique_ptr<Model> model_;
    shared_ptr<View> view_;
    TLogger* logger_;

public:
    Controller(unique_ptr<Model> model, shared_ptr<View> view, TLogger* logger)
        : model_{move(model)}
        , view_{view}
        , logger_{logger}
    {
        assert(typeid(*view_) == typeid(ConsoleView));
        assert(typeid(*logger_) == typeid(FileLogger<DateTimeProvider>));
    }

    void do_something()
    {
        if (logger_)
            logger_->log("Controller::do_something() is updating a view: "s + typeid(*view_).name());

        view_->update_content(model_->fname() + " " + model_->lname() + " - " + to_string(model_->age()));
    }
};

TEST(Boost_DI_Tests, Complex_Case_DI)
{
    shared_ptr<View> view;

    const string file_name = "out.log";

    auto model_injector = [] {
        return di::make_injector(
            di::bind<string>().named(fname).to("Jan"),
            di::bind<string>().named(lname).to("Kowalski"),
            di::bind<int>().to(42));
    };

    {
        auto injector = di::make_injector(
            di::bind<View>().in(di::unique).to<ConsoleView>(),
            di::bind<class Logger>().to<FileLogger>(),
            di::bind<class TimeStampProvider>().to<DateTimeProvider>(),
            di::bind<ostream>().to(cout),
            di::bind<string>().to(file_name),
            model_injector());

        auto controller = injector.create<Controller>();
        controller.do_something();

        view = injector.create<shared_ptr<View>>();
    }

    ASSERT_EQ(view.use_count(), 1);
}
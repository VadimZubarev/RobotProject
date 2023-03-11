#include <cstdio>
#include <iostream>
#include <https://raw.githubusercontent.com/boost-experimental/sml/master/include/boost/sml.hpp>

namespace sml = boost::sml;

struct existTarget {};
struct angleDelta {};
struct distanceDelta {};
struct pour {};
struct timeout {};


constexpr auto exist = [] { std::puts("exist"); };
constexpr auto angle = [] { std::puts("angle"); };
constexpr auto noangle = [] { std::puts("no angle"); };
constexpr auto distance = [] { std::puts("distance"); };
constexpr auto nodistance = [] { std::puts("no distance"); };
constexpr auto pouring = [] { std::puts("pouring"); };
constexpr auto nopouring = [] { std::puts("no pouring"); };
constexpr auto noexist = [] { std::puts("no exist"); };


struct Robot {
    auto operator()() const {
        using namespace sml;
        return make_transition_table(
            *"Waiting"_s + event<existTarget> / exist = "Running"_s,
            "Running"_s + event<angleDelta> / angle = "Rotating"_s,
            "Rotating"_s + event<timeout> / noangle = "Running"_s,
            "Running"_s + event<pour> / pouring = "BringingBeer"_s,
            "BringingBeer"_s + event<timeout> / nopouring = "Running"_s,
            "Running"_s + event<distanceDelta> / distance = "MovingForward "_s,
            "MovingForward"_s + event<timeout> / nodistance = "Running "_s,
            "Running"_s + event<timeout> / noexist = "Waiting"_s
        );
    }
};

int main() {
    sml::sm<Robot, sml::dispatch<sml::back::policies::branch_stm>> navigation{};
    navigation.process_event(existTarget{});
    navigation.process_event(angleDelta{});
    navigation.process_event(timeout{});
    navigation.process_event(distanceDelta{});
    navigation.process_event(timeout{});
    navigation.process_event(pour{});
    navigation.process_event(timeout{});
    navigation.process_event(timeout{});
}
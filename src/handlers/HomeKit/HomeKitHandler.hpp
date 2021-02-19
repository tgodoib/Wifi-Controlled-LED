#include <homekit/characteristics.h>
#include <homekit/homekit.h>

#ifndef HOME_KIT_HANDLER_HPP
#define HOME_KIT_HANDLER_HPP

static uint32_t t_report;
static uint32_t t_heap;

class IOS {

public:
    struct FullColor {
        float hue;
        float sat;

        bool is_hue_set = false;
        bool is_sat_set = false;
    };

    static void start();
    static void loop();
    static void report();

private:
    static void set_on(const homekit_value_t value);
    static void set_hue(const homekit_value_t value);
    static void set_sat(const homekit_value_t value);
    static void set_bright(const homekit_value_t value);
};

static IOS::FullColor incomplete_color;

#endif
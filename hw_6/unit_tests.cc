
#include "gtest/gtest.h"
#include "elma/elma.h"

#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "integrator.h"


namespace {

    TEST(StopwatchTests, Functionality) {
        Stopwatch stopwatch;

        // Test 1: Measures time accurately (milliseconds)
        stopwatch.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stopwatch.stop();
        double elapsedTimeMs = stopwatch.get_milliseconds();
        EXPECT_NEAR(100.0, elapsedTimeMs, 5.0);

        // Reset for next test
        stopwatch.reset();

        // Test 2: Accumulates time correctly over multiple starts and stops
        stopwatch.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        stopwatch.stop();
        stopwatch.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        stopwatch.stop();
        double elapsedTimeAccumulated = stopwatch.get_milliseconds();
        EXPECT_NEAR(400.0, elapsedTimeAccumulated, 10.0);

        // Reset for next test
        stopwatch.reset();

        // Test 3: Resets to zero correctly
        stopwatch.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stopwatch.stop();
        stopwatch.reset();
        EXPECT_EQ(0.0, stopwatch.get_seconds());

        // Test 4: Stops time measurement accurately
        stopwatch.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        stopwatch.stop();
        double elapsedTimeAfterStop = stopwatch.get_milliseconds();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        double elapsedTimeAfterSleep = stopwatch.get_milliseconds();
        // Elapsed time should not change after stopping the stopwatch
        EXPECT_EQ(elapsedTimeAfterStop, elapsedTimeAfterSleep);
    }

    using namespace elma;

    TEST(RandomProcessFilter, RandomProcessValue) {
        Manager m;

        RandomProcess random("random numbers");
        Filter filter("filter");
        Channel link("link");

        m.schedule(random, 1_ms)
        .schedule(filter, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms);

        double filterValue = filter.value();
        ASSERT_GE(filterValue, 0.0);
        ASSERT_LE(filterValue, 1.0);
    }

    using namespace elma;

TEST(Integrator, ComputesIntegral) {
    Manager m;
    Integrator integrator("integrator");
    Channel link("link");

    m.schedule(integrator, 1_ms)
     .add_channel(link)
     .init()
     .start();

    double constant_value = 2.5;  // Value to send through the channel
    double expected_integral = 0; // Expected integral value

    for (int i = 0; i < 100; ++i) {
        link.send(constant_value);
        expected_integral += constant_value;
    }

    m.run(100_ms);

    // Allow a small tolerance for comparison due to potential floating-point errors
    double tolerance = 2;
    ASSERT_NEAR(integrator.value(), expected_integral, tolerance);
}

} // namespace unit_tests
#include <stdio.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include "main_code.c"

static void test_solve_sum(void **state) {
    float result;
    (void)state;

    result = calculate_operation(1, 3, 1);
    assert_float_equal(result, 4.0, 0.001);

    result = calculate_operation(0, 0, 1);
    assert_float_equal(result, 0.0, 0.001);

    result = calculate_operation(-3, 1, 1);
    assert_float_equal(result, -2.0, 0.001);

    result = calculate_operation(2.25, 1.32, 1);
    assert_float_equal(result, 3.57, 0.001);
}

static void test_solve_subtr(void **state) {
    float result;
    (void)state;

    result = calculate_operation(5, 2, 2);
    assert_float_equal(result, 3.0, 0.001);

    result = calculate_operation(0, 0, 2);
    assert_float_equal(result, 0.0, 0.001);

    result = calculate_operation(-3, 1, 2);
    assert_float_equal(result, -4.0, 0.001);

    result = calculate_operation(2, -2, 2);
    assert_float_equal(result, 4.0, 0.001);
}

static void test_solve_multp(void **state) {
    float result;
    (void)state;

    result = calculate_operation(5, 2, 3);
    assert_float_equal(result, 10.0, 0.001);

    result = calculate_operation(0, 0, 3);
    assert_float_equal(result, 0.0, 0.001);

    result = calculate_operation(-3, 1, 3);
    assert_float_equal(result, -3.0, 0.001);

    result = calculate_operation(2, -2, 3);
    assert_float_equal(result, -4.0, 0.001);
}

static void test_solve_div(void **state) {
    float result;
    (void)state;

    result = calculate_operation(10, 2, 4);
    assert_float_equal(result, 5.0, 0.001);

    result = calculate_operation(0, 0, 4);
    assert_float_equal(result, 0.0, 0.001);

    result = calculate_operation(1, 3, 4);
    assert_float_equal(result, 0.33333, 0.001);

    result = calculate_operation(2, -2, 4);
    assert_float_equal(result, -1.0, 0.001);
}

static void test_solve_pow(void **state) {
    float result;
    (void)state;

    result = calculate_operation(2, 3, 5);
    assert_float_equal(result, 8.0, 0.001);

    result = calculate_operation(0, 2, 5);
    assert_float_equal(result, 0.0, 0.001);

    result = calculate_operation(1, 3, 5);
    assert_float_equal(result, 1.0, 0.001);

    result = calculate_operation(9, 0.5, 5);
    assert_float_equal(result, 3.0, 0.001);
}

static void test_invalid_operations(void **state) {
    float result;
    (void)state;

    result = calculate_operation(2, 3, 12);
    assert_float_equal(result, 0.0, 0.001);

    result = calculate_operation(0, 2, 0);
    assert_float_equal(result, 0.0, 0.001);

    result = calculate_operation(1, 3, -27);
    assert_float_equal(result, 0.0, 0.001);

    result = calculate_operation(9, 0.5, 101);
    assert_float_equal(result, 0.0, 0.001);
}

static void test_write_to_history(void **state) {
    float history[100] = {0};
    (void)state;

    add_to_history(history, 12, 27.0);
    assert_float_equal(history[12], 27.0, 0.001);

    add_to_history(history, 90, 11.42);
    assert_float_equal(history[90], 11.42, 0.001);

    add_to_history(history, 7, 0.4);
    assert_float_equal(history[7], 0.4, 0.001);
}

static void test_history_beyond_boundaries(void **state) {
    float history[100] = {0};
    (void)state;

    add_to_history(history, 101, 27.0);
    assert_float_equal(history[101], 0.0, 0.001);

    add_to_history(history, -27, 11.42);
    assert_float_equal(history[-27], 0.0, 0.001);

    add_to_history(history, 7, 0.4);
    assert_float_equal(history[7], 0.4, 0.001);
}

static void test_history_command(void **state) {
    (void)state;

    assert_true(is_history_command(6.0));
    assert_false(is_history_command(6.1));
    assert_false(is_history_command(5.9));
    assert_false(is_history_command(0.0));
    assert_false(is_history_command(-6.0));
}

int main(void) {
     const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_solve_sum),
        cmocka_unit_test(test_solve_subtr),
        cmocka_unit_test(test_solve_multp),
        cmocka_unit_test(test_solve_div),
        cmocka_unit_test(test_solve_pow),
        cmocka_unit_test(test_invalid_operations),
        cmocka_unit_test(test_write_to_history),
        cmocka_unit_test(test_history_beyond_boundaries),
        cmocka_unit_test(test_history_command),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}

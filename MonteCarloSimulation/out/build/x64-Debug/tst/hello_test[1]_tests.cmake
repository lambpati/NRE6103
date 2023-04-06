add_test([=[HelloTest.BasicAssertions]=]  C:/Users/pclam/source/repos/NRE6103/MonteCarloSimulation/out/build/x64-Debug/tst/hello_test.exe [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY C:/Users/pclam/source/repos/NRE6103/MonteCarloSimulation/out/build/x64-Debug/tst SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  hello_test_TESTS HelloTest.BasicAssertions)

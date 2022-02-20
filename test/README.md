## Requirements
- Catch2

## Build instructions
- when building root from cmake, set the `-Drun_tests` option
- once built, run the specific test (eg. `test/test_vector2`)

Example (run from `spatula/build`):

```sh
cmake -Drun_tests ..
cmake --build .
test/test_vector2
```
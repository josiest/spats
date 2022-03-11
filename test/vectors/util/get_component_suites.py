from randvec import *
from pathlib import Path

vector_test_dir = (Path(__file__)/"../..").resolve()
test_path = vector_test_dir/"test_get_component.cpp"

for suite_fn in (sfml_suite, glm_suite, eigen_suite):
    add_suite(test_path, suite_fn())

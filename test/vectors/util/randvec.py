from random import randint, uniform
from string import Template

component = ('x', 'y', 'z', 'w')

#
# decorators
#

def vectorize(func):
    def vector(N: int):
        return tuple(func(N) for i in range(N))
    return vector

def load(filename):
    def decorator(func):
        def loader(*args, **kwargs):
            s = ''
            with open(filename, 'r') as fp:
                s = fp.read()
            return func(Template(s), *args, **kwargs)

        return loader
    return decorator

def appending(func):
    def writer(filename: str, cases):
        with open(filename, 'a') as fp:
            func(fp, filename, cases)
    return writer

#
# vector generators
#

@vectorize
def ivec(N: int):
    return randint(-512, 512)

@vectorize
def uvec(N: int):
    return randint(0, 1024)

@vectorize
def fvec(N: int):
    return round(uniform(-200, 200), 3)

@vectorize
def dvec(N: int):
    return round(uniform(-200, 200), 9)

@vectorize
def cfvec(N: int):
    return tuple(round(uniform(-200, 200), 3) for i in range(2))

@vectorize
def cdvec(N: int):
    return tuple(round(uniform(-200, 200), 9) for i in range(2))

#
# vector printing and test writing
#

def vecstr(vec):
    return "{" + ", ".join(str(x) for x in vec) + "}"

def complexstr(vec):
    return "{" + ", ".join(vecstr(z) for z in vec) + "}"

@appending
def add_suite(fp, filename: str, cases):
    sep = ""
    for test_case in cases:
        fp.write(sep)
        fp.write(test_case)
        sep = "\n"

#
# test cases
#

@load('glm_case.cpp')
def glm_case(fmt: Template, N: int, i: int):
    vecs = (ivec(N), uvec(N), fvec(N), dvec(N))
    kwargs = {'N': N, 'x': component[i],
              'ivecstr': vecstr(vecs[0]), 'ivec_x': vecs[0][i],
              'uvecstr': vecstr(vecs[1]), 'uvec_x': vecs[1][i],
              'fvecstr': vecstr(vecs[2]), 'fvec_x': vecs[2][i],
              'dvecstr': vecstr(vecs[3]), 'dvec_x': vecs[3][i]}

    return fmt.substitute(**kwargs)

@load('sfml_case.cpp')
def sfml_case(fmt: Template, N: int, i: int):
    vecs = (ivec(N), fvec(N))
    kwargs = {'N': N, 'x': component[i],
              'ivecstr': vecstr(vecs[0]), 'ivec_x': vecs[0][i],
              'fvecstr': vecstr(vecs[1]), 'fvec_x': vecs[1][i]}

    return fmt.substitute(**kwargs)

@load('eigen_case.cpp')
def eigen_case(fmt: Template, N: int, i: int):
    vecs = (ivec(N), fvec(N), dvec(N), cfvec(N), cdvec(N))
    kwargs = {'N': N, 'x': component[i],
              'ivecstr': vecstr(vecs[0]), 'ivec_x': vecs[0][i],
              'fvecstr': vecstr(vecs[1]), 'fvec_x': vecs[1][i],
              'dvecstr': vecstr(vecs[2]), 'dvec_x': vecs[2][i],
              'cfvecstr': complexstr(vecs[3]), 'cfvec_x': vecstr(vecs[3][i]),
              'cdvecstr': complexstr(vecs[4]), 'cdvec_x': vecstr(vecs[4][i])}

    return fmt.substitute(**kwargs)

#
# test suites
#

def glm_suite():
    for N in range(2, 5):
        for i in range(N):
            yield glm_case(N, i)

def sfml_suite():
    for N in range(2, 4):
        for i in range(N):
            yield sfml_case(N, i)

def eigen_suite():
    for N in range(2, 5):
        for i in range(N):
            yield eigen_case(N, i)

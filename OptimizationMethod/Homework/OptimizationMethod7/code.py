import numpy as np


def f(x):
    return 1 / 2 * x.T.dot(A).dot(x) + b.T.dot(x) + c


def nabla_f(x):
    return A.dot(x) + b


def armijo():
    def check(m):
        lhs = f(x + beta * pow(gamma, m) * d)
        rhs = f(x) + sigma * beta * pow(gamma, m) * nabla_f(x).T.dot(d)
        return all(lhs <= rhs)

    m = 1
    while not check(m):
        m += 1
    print("Using Armijo algorithm, m = {}, the next x is\n {}"
          .format(m, x + beta * pow(gamma, m) * d))


def goldstein():
    def check1(lambda_):
        lhs = f(x + lambda_ * d)
        rhs = f(x) + sigma * lambda_ * nabla_f(x).T.dot(d)
        return all(lhs <= rhs)

    def check2(lambda_):
        lhs = f(x + lambda_ * d)
        rhs = f(x) + (1 - sigma) * lambda_ * nabla_f(x).T.dot(d)
        return all(lhs > rhs)

    a, b = 0, np.inf
    lambda_ = 1
    alpha = 2  # 试探点系数
    while np.fabs(a - b) > 1e-5:
        if check1(lambda_):
            if not check2(lambda_):
                break
            else:
                a = lambda_
                lambda_ = (a + b) / 2 if b < np.inf else alpha * lambda_
        else:
            b = lambda_
            lambda_ = (a + b) / 2

    print("Using Goldstein algorithm, lambda = {:.6}, the next x is\n {}"
          .format(lambda_, x + lambda_ * d))


def wolfe():
    sigma_1 = 0.1
    sigma_2 = 0.9

    def check1(lambda_):
        lhs = f(x + lambda_ * d)
        rhs = f(x) + sigma_1 * nabla_f(x).T.dot(d)
        return all(lhs <= rhs)

    def check2(lambda_):
        lhs = nabla_f(x + lambda_ * d).T.dot(d)
        rhs = sigma_2 * nabla_f(x).T.dot(d)
        return all(lhs >= rhs)

    lambda_ = 1
    a, b = 0, np.inf
    while np.fabs(a - b) > 1e-5:
        if check1(lambda_):
            if not check2(lambda_):
                break
            else:
                a = lambda_
                lambda_ = (a + b) / 2
        else:
            b = lambda_
            lambda_ = (a + b) / 2

    print("Using Wolfe algorithm, lambda = {:.6}, the next x is\n {}"
          .format(lambda_, x + lambda_ * d))


if __name__ == '__main__':
    A = np.array([[2, 1, 1, 0], [1, 4, 0, 0], [1, 0, 2, 0], [0, 0, 0, 2]])
    b = np.array([[1], [2], [0], [1]])
    c = 2

    x = np.array([1, 1, 1, 1]).reshape(-1, 1)
    d = -nabla_f(x)

    sigma = 1e-4
    beta = 1
    gamma = 0.5

    armijo()
    goldstein()
    wolfe()

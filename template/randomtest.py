import random
import subprocess


RUN_CASES = 100
NAIVE_COMMAND = "./naive"
SOLVE_COMMAND = "./solve"


def gen_input() -> str:
    n = 10
    a = [random.randint(0, 10) for _ in range(n)]
    return f"{n}\n{" ".join(map(str, a))}"


def run(cmd: str, sample: str) -> str:
    return subprocess.run([cmd], input=sample, text=True, capture_output=True).stdout


def test() -> bool:
    sample = gen_input()
    naive_out = run(NAIVE_COMMAND, sample)
    solve_out = run(SOLVE_COMMAND, sample)

    if solve_out != naive_out:
        print("\n----- input -----")
        print(sample)
        print("\n----- naive out -----")
        print(naive_out)
        print("\n----- solve out -----")
        print(solve_out)
        return False
    return True


if __name__ == "__main__":
    for _ in range(RUN_CASES):
        if not test():
            exit()
    print(RUN_CASES, "run. error not found")

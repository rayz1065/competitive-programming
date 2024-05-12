import piante

if __name__ == "__main__":
    N = int(input())
    H = list(map(int, input().split()))

    print(piante.pollice_verde(N, H))

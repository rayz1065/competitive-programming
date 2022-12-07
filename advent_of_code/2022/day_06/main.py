def main():
    signal = input()
    for i in range(4, len(signal)):
        buff = signal[i - 4:i]
        if len(set(buff)) == 4:
            print(i)
            break
    for i in range(14, len(signal)):
        buff = signal[i - 14:i]
        if len(set(buff)) == 14:
            print(i)
            break

if __name__ == '__main__':
    main()

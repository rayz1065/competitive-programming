SONG = 'Happy birthday to you Happy birthday to you Happy birthday to Rujia Happy birthday to you'

n = int(input().strip())
names = [input().strip() for _ in range(n)]

everyone_sang = False

next_singer = 0

while not everyone_sang:
    for segment in SONG.split():
        print(f'{names[next_singer]}: {segment}')
        next_singer = (next_singer + 1) % n
        everyone_sang = everyone_sang or next_singer == 0

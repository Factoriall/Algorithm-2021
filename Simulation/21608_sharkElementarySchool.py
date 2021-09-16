def isOutOfRange(y, x):
    return y < 0 or x < 0 or y >= n or x >= n

n = int(input())

friends = [[0 for x in range(5)] for y in range(n * n)]

for i in range(n * n):
    friends[i] = input().split()

dy = [1, 0, -1, 0]
dx = [0, 1, 0, -1]

map = [[0 for x in range(n)] for y in range(n)]
locations = []

for t in range(n * n):
    now = friends[t]
    #  조건 1: 가장 많은 친구 인접
    most = []
    maxCnt = -1
    for i in range(n):
        for j in range(n):
            if map[i][j] != 0: continue
            cnt = 0
            for d in range(4):
                ay = i + dy[d]
                ax = j + dx[d]
                if isOutOfRange(ay, ax):
                    continue
                for k in range(4):
                    if map[ay][ax] == int(now[k + 1]):
                        cnt += 1
                        break
            if maxCnt < cnt:
                most.clear()
                most.append([i, j])
                maxCnt = cnt
            elif maxCnt == cnt:
                most.append([i, j])

    #  조건 2: most 중 인접 공간 가장 많은 것
    blank = []
    maxCnt = -1
    for y, x in most:
        cnt = 0
        for d in range(4):
            ay = y + dy[d]
            ax = x + dx[d]
            if isOutOfRange(ay, ax):
                continue
            if map[ay][ax] == 0:
                cnt += 1
        if maxCnt < cnt:
            maxCnt = cnt
            blank.clear()
            blank.append([y, x])
        elif maxCnt == cnt:
            blank.append([y, x])
    #  조건 3: 행열 가장 작은 것
    map[blank[0][0]][blank[0][1]] = int(now[0])
    locations.append(blank[0])

answer = 0
for idx, loc in enumerate(locations):
    y = loc[0]
    x = loc[1]
    cnt = 0
    for d in range(4):
        ay = y + dy[d]
        ax = x + dx[d]
        if isOutOfRange(ay, ax):
            continue
        for k in range(4):
            if map[ay][ax] == int(friends[idx][k + 1]):
                cnt += 1
                break
    if cnt == 1:
        answer += 1
    elif cnt == 2:
        answer += 10
    elif cnt == 3:
        answer += 100
    elif cnt == 4:
        answer += 1000

print(answer)

